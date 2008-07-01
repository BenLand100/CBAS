package cbas;

import java.awt.Component;
import java.awt.Font;
import java.awt.event.KeyEvent;
import javax.swing.JTextPane;
import javax.swing.event.CaretEvent;
import javax.swing.event.CaretListener;
import javax.swing.plaf.ComponentUI;
import javax.swing.text.Caret;
import javax.swing.text.Position;

/**
 *  
 * @author Benjamin J. Land
 */
public class CodeArea extends JTextPane implements CaretListener {
    
    /** Creates a new instance of CodeArea */
    public CodeArea() {
        setEditorKit(new CodeEditorKit());
        setFont(new Font("Monospaced", Font.PLAIN, 14));
        addCaretListener(this);
    }
    
    public CodeArea(String ppg) {
        this();
        setText(ppg);
    }
    
    public boolean getScrollableTracksViewportWidth() {
        Component parent = getParent();
        ComponentUI ui = getUI();
        return parent != null ? (ui.getPreferredSize(this).width <= parent.getSize().width) : true;
    }

    public void caretUpdate(CaretEvent e) {
        int loc = e.getDot();
        ((CodeDocument)getStyledDocument()).caretUpdate(e);
    }

    public void backTab() {
        Caret c = getCaret();
        if (c.getDot() == c.getMark()) {
            try {
                int remove = c.getDot() - 4 > -1 ? 4 : c.getDot();
                String text = this.getText(c.getDot() - remove, remove);
                if (text.contains("\n"))
                    remove = text.length() - text.lastIndexOf("\n") - 1;
                getStyledDocument().remove(c.getDot()-remove,remove);
            } catch (Exception e) { }
        } else {
            try {
                String text = getText();
                int start = Math.min(c.getDot(),c.getMark()), end = Math.max(c.getDot(),c.getMark());
                for (; start > -1; start--) {
                    if (text.charAt(start) == '\n') {
                        break;
                    }
                }
                for (; end < text.length(); end++) {
                    if (text.charAt(end) == '\n') break;
                }
                start++;
                Position e = getStyledDocument().createPosition(end);
                getStyledDocument().remove(start,end - start);
                if (text.startsWith("    ",start)) {
                    text = text.substring(start+4,end);
                } else {
                    int temp = start;
                    for (; temp < start + 4; temp++)
                        if (text.charAt(temp) != ' ') break;
                    text = text.substring(temp,end);
                }
                getStyledDocument().insertString(start,text.replaceAll("\n {1,4}","\n"),null);
                select(start,e.getOffset());
            } catch (Exception e) { }
        }
    }
    
    public void forwardTab() {
        Caret c = getCaret();
        if (c.getDot() == c.getMark()) {
            try {
                getStyledDocument().insertString(c.getDot(),"    ",null);
            } catch (Exception e) { }
        } else {
            try {
                String text = getText();
                int start = Math.min(c.getDot(),c.getMark()), end = Math.max(c.getDot(),c.getMark());
                for (; start > -1; start--) {
                    if (text.charAt(start) == '\n') {
                        break;
                    }
                }
                for (; end < text.length(); end++) {
                    if (text.charAt(end) == '\n') break;
                }
                start++;
                Position e = getStyledDocument().createPosition(end);
                getStyledDocument().remove(start,end - start);
                text = "    " + text.substring(start,end);
                getStyledDocument().insertString(start,text.replaceAll("\n","\n    "),null);
                select(start,e.getOffset());
            } catch (Exception e) { }
        }
    }
    
    public void undo() {
        ((CodeDocument)getStyledDocument()).undo();
    }
    
    public void redo() {
        ((CodeDocument)getStyledDocument()).redo();
    }
    
    protected void processKeyEvent(KeyEvent e) {
        if (e.getID() == e.KEY_PRESSED && e.getKeyChar() == '\t') {
            if (e.isShiftDown()) {
                backTab();
            } else {
                forwardTab();
            }
        } else if (e.getID() == e.KEY_TYPED && e.getKeyChar() == 26 && e.isControlDown()) {
            undo();
        } else if (e.getID() == e.KEY_TYPED && e.getKeyChar() == 25 && e.isControlDown()) {
            redo();
        }  else {
            super.processKeyEvent(e);
        }
    }
    
}
