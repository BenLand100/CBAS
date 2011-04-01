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

