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

import java.io.File;

/**
 * Bad encapsulation, but its more like a hackish c struct
 * 
 * @author benland100
 */
public class TabData {
    
    public int lastHash;
    public CodeArea codeArea;
    
    public boolean running;
    public boolean compiling;
    public boolean paused;
    
    public boolean compile;
    public boolean run;
    public boolean stop;
    public boolean pause;
    
    public File file;
    public File dll;
    
    public String name;
    
    public TabData() {
    }
    
}
