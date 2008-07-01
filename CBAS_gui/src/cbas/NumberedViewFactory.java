package cbas;

import java.awt.Graphics;
import java.awt.Rectangle;
import java.awt.Shape;
import javax.swing.text.AbstractDocument;
import javax.swing.text.BoxView;
import javax.swing.text.Element;
import javax.swing.text.LabelView;
import javax.swing.text.View;
import javax.swing.text.ViewFactory;

/**
 *
 * @author Benjamin J. Land
 */
public class NumberedViewFactory implements ViewFactory {
    
    public View create(Element elem) {
        String kind = elem.getName();
        if (kind != null) {
            if (kind.equals(AbstractDocument.ParagraphElementName)) {
                return new NumberedParagraphView(elem);
            } else if (kind.equals(AbstractDocument.SectionElementName)) {
                return new BoxView(elem, View.Y_AXIS);
            } else if (kind.equals(AbstractDocument.ContentElementName)) {
                return new LabelView(elem);
            }
        }
        return new LabelView(elem);
    }
    
}
