package cbas;

import java.io.IOException;
import java.io.OutputStream;
import javax.swing.JTextArea;

/**
 *
 * @author Benjamin J. Land
 */
public class TextAreaOutputStream extends OutputStream {
    
    private JTextArea textControl;

    public TextAreaOutputStream( JTextArea control ) {
        textControl = control;
    }
    
    public void write( int b ) throws IOException {
        textControl.append(String.valueOf((char)b));
        if ((char)b == '\n') {
            textControl.setCaretPosition(textControl.getText().length());
        }
    }
    
}
