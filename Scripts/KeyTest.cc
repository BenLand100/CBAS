#include "Input.h"
#include <windows.h>
int scriptmain() {
    Keyboard k;
    k.keyDown(VK_UP);
    if (!k.isKeyDown(VK_UP )) return 1;
    k.keyUp(VK_UP );
    //k.sendString("Blablabla\rSecondline!");
    return 0;
}