package cbas;

import javax.swing.text.Document;
import javax.swing.text.StyledEditorKit;
import javax.swing.text.ViewFactory;

/**
 *
 * @author Benjamin J. Land
 */
public class CodeEditorKit extends StyledEditorKit {
    
    public Document createDefaultDocument() {
        return new CodeDocument();
    }
    
    public ViewFactory getViewFactory() {
        return new NumberedViewFactory();
    }
    
}
