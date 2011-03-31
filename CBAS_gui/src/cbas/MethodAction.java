/**
 *  Copyright 2007 by Benjamin J. Land (a.k.a. BenLand100)
 *
 *  This file is part of the CBAS C-Based Autoing System
 *
 *  CBAS is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  CBAS is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with CBAS. If not, see <http://www.gnu.org/licenses/>.
 */

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

