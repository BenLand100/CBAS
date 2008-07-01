#ifndef INPUT_H
#define	INPUT_H

#include "dll.h"
#include <windows.h>

class Mouse {
public:
    EXPORT Mouse();
    EXPORT Mouse(HWND target);
    EXPORT virtual void getMousePos(int& x, int& y);
    EXPORT virtual void setMousePos(int x, int y);
    EXPORT virtual void holdMouse(bool left);
    EXPORT virtual void releaseMouse(bool left);
    EXPORT void moveMouse(int x, int y);
    EXPORT void clickMouse(int x, int y, bool left);
    EXPORT void dragMouse(int x, int y, bool left);
private:
    HWND target;
};

class Keyboard {
public:
    EXPORT Keyboard();
    EXPORT virtual bool isKeyDown(int key);
    EXPORT virtual void keyDown(int key);
    EXPORT virtual void keyUp(int key);
    EXPORT void sendString(char* str);
};

#endif	/* INPUT_H */

