package cbas;

import java.awt.Color;
import java.io.File;
import java.lang.reflect.Field;
import java.util.Arrays;
import java.util.LinkedHashMap;
import java.util.LinkedList;
import java.util.Properties;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;
import javax.swing.text.AttributeSet;
import javax.swing.text.BadLocationException;
import javax.swing.text.DefaultEditorKit;
import javax.swing.text.DefaultStyledDocument;
import javax.swing.text.Element;
import javax.swing.text.MutableAttributeSet;
import javax.swing.text.SimpleAttributeSet;
import javax.swing.text.StyleConstants;
import javax.swing.undo.CannotRedoException;
import javax.swing.undo.CannotUndoException;


public class CodeDocument extends DefaultStyledDocument implements CaretListener {
    
    public static Color GROUPER = Color.GREEN.darker();
    public static Color INTEGER = Color.BLUE.darker();
    public static Color FLOAT = Color.BLUE.darker();
    public static Color OPERATOR = Color.RED;
    public static Color DIRECTIVE = Color.GREEN.darker();
    public static Color RESERVED = Color.BLUE;
    public static Color TYPES = Color.BLUE;
    public static Color GENERIC = new Color(255,100,0);
    public static Color STRING = new Color(255,100,0);
    public static Color CHAR = new Color(255,100,0);
    public static Color COMMENT = Color.GRAY;
    
    public static void loadColors(Properties props) {
        String[] names = new String[] { "grouper", "integer", "float", "operator", "directive", "reserved", "types", "generic", "string", "char", "comment" };
        for (String name : names) {
            try {
                Field color = CodeDocument.class.getField(name.toUpperCase());
                if (!props.containsKey(name)) 
                    props.setProperty(name,Integer.toString(((Color)color.get(null)).getRGB() & 0xFFFFFF,16));
                color.set(null, new Color(Integer.parseInt(props.getProperty(name),16)));
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
                
    }
    
    private Element rootElement;
    private LinkedHashMap<Pattern,Color> elemRegexes;
    private MutableAttributeSet style;
    
    private LinkedList<NormalEdit> undo = new LinkedList<NormalEdit>();
    private LinkedList<NormalEdit> redo = new LinkedList<NormalEdit>();
    
    public static final String redCOMMENT = "//[^\n]*|/\\*[^(?:\\*/)]*(?:\\*/)?";
    public static final String regNAME = "[\\w&&[^\\d]][^\\s\\(\\)]*";
    public static final String regOPERATOR = "\\+|\\-|\\/|\\*|\\&|\\^|\\~|\\!|\\>|\\<|\\=|\\?";
    public static final String regSTRING = "\"(?:[^\"\n\\\\]|\\\\.)*(?:\"|\n)";
    public static final String regCHAR = "'(?:[^'\n\\\\]|\\\\.)*(?:'|\n)";
    public static final String regFLOAT = "[\\+\\-]?\\d+(?:\\.\\d*)"; 
    public static final String regNTEGER = "[\\+\\-]?\\d+"; 
    public static final String regTYPES = "\\b(?:int|long|bool|float|double|char|void|char)(?:\\b|\\*)";
    public static final String regKEYWORDS = "\\b(?:virtual|new|delete|unsigned|extern|while|if|else|for|do|until|sizeof|return|break|case|switch|true|false|static|goto|const|typedef|struct|union|class|public|private|protected|using|namespace)\\b";
    /**
     * Initilizes a new CodeDocument with all defaults set.
     */
    public CodeDocument() {
        putProperty(DefaultEditorKit.EndOfLineStringProperty, "\n" );
        rootElement = getDefaultRootElement();
        elemRegexes = new LinkedHashMap<Pattern, Color>();
        elemRegexes.put(Pattern.compile(".+"), Color.BLACK);
        elemRegexes.put(Pattern.compile("\\s+"),Color.WHITE);
        elemRegexes.put(Pattern.compile("[\\(\\)\\[\\]]"),GROUPER);
        elemRegexes.put(Pattern.compile(regNTEGER),INTEGER);
        elemRegexes.put(Pattern.compile(regFLOAT),FLOAT);
        elemRegexes.put(Pattern.compile(regNAME),Color.BLACK);
        elemRegexes.put(Pattern.compile(regOPERATOR),OPERATOR);
        elemRegexes.put(Pattern.compile("#" + regNAME),DIRECTIVE);
        elemRegexes.put(Pattern.compile(regKEYWORDS), RESERVED);
        elemRegexes.put(Pattern.compile(regTYPES), TYPES);
        elemRegexes.put(Pattern.compile("\\<[^\\>\n\\<]*\\>"),GENERIC);
        elemRegexes.put(Pattern.compile(regSTRING),STRING);
        elemRegexes.put(Pattern.compile(regCHAR),CHAR);
        elemRegexes.put(Pattern.compile(redCOMMENT),COMMENT);
        style = new SimpleAttributeSet();
    }
    
    /**
     * Enables the document to use "SmartTabs" and mantain an indention uppon
     * inserting new lines.
     * @param str String to be inserted
     * @param offset Position to insert at
     * @return The possibly modified string to be inserted instead
     * @throws javax.swing.text.BadLocationException
     */
    public String processInsert(String str, int offset) throws BadLocationException {
        if (str.length() > 1) return str;
        switch (str.charAt(0)) {
            case '\n':
            case '\r':
                try {
                    String src = getText(0,offset+1);
                    for (int i = offset - 1; i > 0; i--) {
                        if (src.charAt(i) == '\n') {
                            for (int c = i + 1; c <= offset; c++) {
                                if (!Character.isWhitespace(src.charAt(c)) || src.charAt(c) == '\n') {
                                    char[] chars = new char[c-i];
                                    Arrays.fill(chars,' ');
                                    chars[0] = '\n';
                                    str = new String(chars);
                                    break;
                                }
                            }
                            break;
                        }
                    }
                } catch (Exception e) { e.printStackTrace(); }
        }
        return str;
    }
    
    /**
     * Abstracts an edit to the document, only valid in the order in which they 
     * occure in the document, e.g. you can not undo or redo edits out of order.
     */
    public class NormalEdit {
        
        private final String significant = "    |\\(|\\)|\n";
        
        private String value;
        private int offset;
        private boolean removed;
        
        /**
         * Creates a new NormalEdit with the specified data
         * @param value The string inserted or removed
         * @param offset Where the edit occured
         * @param removed If the edit was a remove or not
         */
        public NormalEdit(String value, int offset, boolean removed) {
            this.value = value;
            this.offset = offset;
            this.removed = removed;
        }
        
        /**
         * Returns the String that was modified
         * @return The modified String
         */
        public String toString() {
            return value;
        }

        /**
         * Tests if a new set of edit data can be appended to this NormalEdit.
         * If it can it is appended and no further action is nessessary.
         * @param value The string inserted or removed
         * @param offset Where the edit occured
         * @param removed If the edit was a remove or not
         * @return True if the error was appended
         */
        public boolean addTo(String value, int offset, boolean removed) {
            if (!isSignificant() && value.length() < 2 && !Pattern.matches(significant, value) && this.removed == removed) {
                if (removed && offset + value.length() == this.offset) {
                    this.value = value + this.value;
                    this.offset = offset;
                    return true;
                } else if (this.offset + this.value.length() == offset) {
                    this.value += value;
                    return true;
                }
            }
            return false;
        }
        
        /**
         * Determins if this edit is significant, i.e. it needs to stand alone.
         * @return True if significant
         */
        public boolean isSignificant() {
            return Pattern.matches(significant,value);
        }

        /**
         * Attempts to redo this NormalEdit or throws a CannotRedoException if
         * unsuccessful.
         */
        public void redo() throws CannotRedoException {
            try {
                if (removed) {
                    superRemove(offset, value.length());
                    processChangedLines(offset, value.length());
                } else {
                    superInsert(offset, value, null);
                    processChangedLines(offset, value.length());
                }
            } catch (Exception e) {
                e.printStackTrace();
                throw new CannotUndoException();
            }
        }

        /**
         * Attempts to undi this NormalEdit or throws a CannotUndoException if
         * unsuccessful.
         */
        public void undo() throws CannotUndoException {
            try {
                if (!removed) {
                    superRemove(offset, value.length());
                    processChangedLines(offset, value.length());
                } else {
                    superInsert(offset, value, null);
                    processChangedLines(offset, value.length());
                }
            } catch (Exception e) {
                e.printStackTrace();
                throw new CannotUndoException();
            }
        }
        
    }
    
    /**
     * Preforms an undo on the document if one exists to be undone.
     */
    public void undo() {
        if (undo.size() > 0) {
            NormalEdit edit = undo.removeLast();
            edit.undo();
            redo.add(edit);
        }
    }
    
    /**
     * Preforms an redo on the document if one exists to be undone.
     */
    public void redo() {
        if (redo.size() > 0) {
            NormalEdit edit = redo.removeLast();
            edit.redo();
            undo.add(edit);
        }
    }
    
    /**
     * Controls the undo and redo lists by appending a value to the undo list 
     * and clearing the redo list since it becomes invalid. 
     * @param value The string inserted or removed
     * @param offset Where the edit occured
     * @param removed If the edit was a remove or not
     */
    private void addEdit(String value, int offset, boolean removed) {
        redo.clear();
        if (undo.size() > 0 && undo.getLast().addTo(value,offset,removed)) return;
        undo.add(new NormalEdit(value,offset,removed));
        if (undo.size() > 250) undo.removeFirst();
    }
    
    protected void superInsert(int offset, String str, AttributeSet attr) throws BadLocationException {
        super.insertString(offset,str,attr);
    }
    
    protected void superRemove(int offset, int length) throws BadLocationException {
        super.remove(offset,length);
    }
    
    public void insertString(int offset, String str, AttributeSet attr) throws BadLocationException {
        str = processInsert(str, offset);
        addEdit(str,offset,false);
        superInsert(offset, str, attr);
        processChangedLines(offset, str.length());
    }
    
    public void remove(int offset, int length) throws BadLocationException {
        if (length == 1 && offset - 3 > -1 && getText(offset - 3,4).equals("    ")) {
            offset -= 3;
            length = 4;
        }
        addEdit(getText(offset,length),offset,true);
        superRemove(offset, length);
        processChangedLines(offset, length);
    }
    
    public void processChangedLines(int offset, int length) throws BadLocationException {
        String text = getText(0, getLength());
        for (Pattern p : elemRegexes.keySet()) {
            Color col = elemRegexes.get(p);
            Matcher m = p.matcher(text);
            while(m.find()) {
                colorString(col, m.start(), m.end(), true, false);
            }
        }
    }
    
    public void colorString(Color col, int begin, int end, boolean flag, boolean bold) {
        StyleConstants.setForeground(style, col);
        StyleConstants.setBold(style, bold);
        setCharacterAttributes(begin, end-begin, style, flag);
    }
    
    private int lastOpen = -1, lastClose = -1;
    private CaretEvent last = null;
    
    public void caretUpdate(CaretEvent e) {
        last = e;
        try {
            MutableAttributeSet style = new SimpleAttributeSet();
            if (lastOpen != -1 || lastClose != -1) {
                StyleConstants.setBold(style, false);
                StyleConstants.setBackground(style, Color.WHITE);
                if (lastOpen != -1) setCharacterAttributes(lastOpen, 1, style, false);
                if (lastClose != -1) setCharacterAttributes(lastClose, 1, style, false);
                lastOpen = -1;
                lastClose = -1;
            }
            StyleConstants.setBold(style, true);
            StyleConstants.setBackground(style, Color.YELLOW);
            int incr = 0, index = 0, length = getLength();
            String text = getText(0,length);
            switch (text.charAt(e.getDot()-1)) {
                case '{':
                case '(':
                    lastOpen = e.getDot() - 1;
                    setCharacterAttributes(lastOpen, 1, style, false);
                    for (index = lastOpen + 1; index < length; index++) {
                        char c = text.charAt(index);
                        if (c == '{' || c == '(') {
                            incr++;
                        } else if (c == '}' || c == ')') {
                            incr--;
                            if (incr < 0) {
                                lastClose = index;
                                setCharacterAttributes(lastClose, 1, style, false);
                                break;
                            }
                        }
                    }
                    break;
                case ')':
                case '}':
                    lastClose = e.getDot() - 1;
                    setCharacterAttributes(lastClose, 1, style, false);
                    for (index = lastClose - 1; index > -1; index--) {
                        char c = text.charAt(index);
                        if (c == '}' || c == ')') {
                            incr++;
                        } else if (c == '{' || c == '(') {
                            incr--;
                            if (incr < 0) {
                                lastOpen = index;
                                setCharacterAttributes(lastOpen, 1, style, false);
                                break;
                            }
                        }
                    }
                    break;
            }
        } catch (Exception x) {
        }
    }
    
}

