#include "Main.h"
#include "Find.h"
 
int scriptmain() {
    jout << "Hello\n";
    int i = 1;
    jout << i << "\n";
    int x, y;
    RGB color = rgb(0, 0, 0);
    Finder f;
    jout << f.getColor(500,500) << "\n";
    return 0;
}
 