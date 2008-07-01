#include "Input.h"
int scriptmain() {
    Mouse m;
    m.moveMouse(100,100);
    int x, y;
    m.getMousePos(x,y);
    if (x != 100 || y != 100) return 1;
    return 0;
}
