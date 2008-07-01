package cbas;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Rectangle;
import javax.swing.text.BoxView;
import javax.swing.text.Element;
import javax.swing.text.ParagraphView;
import javax.swing.text.View;

/**
 *
 * @author Benjamin J. Land
 */
public class NumberedParagraphView extends ParagraphView {
    
    public static short NUMBERS_WIDTH = 35;
    
    public NumberedParagraphView(Element e) {
        super(e);
    }
    
    protected View createRow() {
        return new Row(getElement());
    }
    
    public void paintChild(Graphics g, Rectangle r, int n) {
        super.paintChild(g.create(), r, n);
        int previousLineCount = getPreviousLineCount();
        int numberX = r.x - getLeftInset();
        int numberY = r.y + r.height - 5;
        g.setColor(Color.LIGHT_GRAY);
        g.fillRect(r.x-2,r.y-2,NUMBERS_WIDTH,r.height+2);
        g.setColor(Color.BLACK);
        g.drawString(Integer.toString(previousLineCount + n + 1), numberX, numberY);
    }
    
    public int getPreviousLineCount() {
        int lineCount = 0;
        View parent = this.getParent();
        int count = parent.getViewCount();
        for (int i = 0; i < count; i++) {
            if (parent.getView(i) == this) {
                break;
            } else {
                lineCount += parent.getView(i).getViewCount();
            }
        }
        return lineCount;
    }
    
    public float getPreferredSpan(int axis) {
        return super.getPreferredSpan(axis) + (axis == X_AXIS ? NUMBERS_WIDTH : 0);
    }
    
    public float getMinimumSpan(int axis) {
        return super.getMinimumSpan(axis) + (axis == X_AXIS ? NUMBERS_WIDTH : 0);
    }

    public float getMaximumSpan(int axis) {
        return super.getMaximumSpan(axis) + (axis == X_AXIS ? NUMBERS_WIDTH : 0);
    }
    
    public class Row extends BoxView {
        
        public Row(Element elem) {
            super(elem,View.X_AXIS);
        }
        
        public float getAlignment(int axis) {
            return 0;
        }

        protected void layoutMajorAxis(int targetSpan, int axis, int[] offsets, int[] spans) {
            long preferred = 0;
            int n = getViewCount();
            for (int i = 0; i < n; i++) {
                View v = getView(i);
                spans[i] = (int) v.getPreferredSpan(axis);
                preferred += spans[i];
            }
            long desiredAdjustment = targetSpan - preferred;
            float adjustmentFactor = 0.0f;
            int[] diffs = null;
            if (desiredAdjustment != 0) {
                long totalSpan = 0;
                diffs = new int[n];
                for (int i = 0; i < n; i++) {
                    View v = getView(i);
                    int tmp;
                    if (desiredAdjustment < 0) {
                        tmp = (int)v.getMinimumSpan(axis);
                        diffs[i] = spans[i] - tmp;
                    } else {
                        tmp = (int)v.getMaximumSpan(axis);
                        diffs[i] = tmp - spans[i];
                    }
                    totalSpan += tmp;
                }
                float maximumAdjustment = Math.abs(totalSpan - preferred);
                    adjustmentFactor = desiredAdjustment / maximumAdjustment;
                    adjustmentFactor = Math.min(adjustmentFactor, 1.0f);
                    adjustmentFactor = Math.max(adjustmentFactor, -1.0f);
                }
            int totalOffset = 0;
            for (int i = 0; i < n; i++) {
                offsets[i] = totalOffset;
                if (desiredAdjustment != 0) {
                    float adjF = adjustmentFactor * diffs[i];
                    spans[i] += Math.round(adjF);
                }
                totalOffset = (int) Math.min((long) totalOffset + (long) spans[i], Integer.MAX_VALUE);
            }
        }

         protected void layoutMinorAxis(int targetSpan, int axis, int[] offsets, int[] spans) {
            int n = getViewCount();
            for (int i = 0; i < n; i++) {
                offsets[i] = 0;
                int perf = (int)getView(i).getPreferredSpan(axis);
                spans[i] = Math.min(perf, targetSpan);
            }
        }
         
        public float getMaximumSpan(int axis) {
            return getPreferredSpan(axis);
        }
        
        protected short getLeftInset() {
            return (short)(super.getLeftInset() + NUMBERS_WIDTH);
        }
        
    }
    
}
