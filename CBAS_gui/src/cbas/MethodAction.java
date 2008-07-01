package cbas;

import java.lang.reflect.Method;
import javax.swing.AbstractAction;

/**
 *
 * @author Benjamin J. Land
 */
public class MethodAction extends AbstractAction {
    
    private Method method;
    private Object parent;
    private Object[] args;
    
    public MethodAction(String name, Class<?> clazz, String method, Object... args) {
        super(name);
        this.args = args;
        Class<?>[] clazzes = new Class<?>[args.length];
        for (int i = 0; i < args.length; i++) {
            clazzes[i] = args[i].getClass();
        }
        try {
            try {
                this.method = clazz.getDeclaredMethod(method,clazzes);
            } catch (Exception e) {
                this.method = clazz.getMethod(method,clazzes);
            }
            this.method.setAccessible(true);
        } catch(Exception e) {
            throw new RuntimeException("Could not init MethodAction",e);
        }
    }
    
    public MethodAction(String name, Object parent, String method, Object... args) {
        this(name, parent.getClass(), method, args);
        this.parent = parent;
    }
    
    public void actionPerformed(java.awt.event.ActionEvent e) {
        try {
            method.invoke(parent,args);
        } catch(java.lang.Exception x) {
            throw new RuntimeException("Could not invoke MethodAction",x);
        }
    }
    
}

