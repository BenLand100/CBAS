package cbas;

import java.io.File;

/**
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
