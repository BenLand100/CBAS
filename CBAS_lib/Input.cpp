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

#include "Input.h"
#include "MissingWindows.h"
#include <iostream>
using namespace std;

Mouse::Mouse() {
    target = 0;
}

Mouse::Mouse(HWND target) {
    this->target = target;
}

void Mouse::getMousePos(int& x, int& y) {
    POINT pt;
    GetCursorPos(&pt);
    if (target) ScreenToClient(target, &pt);
    x = pt.y;
    y = pt.y;
}
void Mouse::setMousePos(int x, int y) {
    POINT pt;
    pt.x = x;
    pt.y = y;
    if (target) ClientToScreen(target, &pt);
    SetCursorPos(pt.x, pt.y);
}

void Mouse::holdMouse(bool left) {
    MOUSEINPUT mi;
    mi.dx = 0;
    mi.dy = 0;
    mi.mouseData = 0;
    mi.dwFlags = (left ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_RIGHTDOWN);
    mi.time = 0;
    mi.dwExtraInfo = 0;
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi = mi;
    SendInput(1,&input,sizeof(INPUT));
}

void Mouse::releaseMouse(bool left) {
    MOUSEINPUT mi;
    mi.dx = 0;
    mi.dy = 0;
    mi.mouseData = 0;
    mi.dwFlags = (left ? MOUSEEVENTF_LEFTUP : MOUSEEVENTF_RIGHTUP);
    mi.time = 0;
    mi.dwExtraInfo = 0;
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi = mi;
    SendInput(1,&input,sizeof(INPUT));
}

void Mouse::moveMouse(int x, int y) {
    setMousePos(x,y); //Temp...
}

void Mouse::clickMouse(int x, int y, bool left) {
    moveMouse(x,y);
    Sleep(150);
    holdMouse(left);
    Sleep(75);
    releaseMouse(left);
}

void Mouse::dragMouse(int x, int y, bool left) {
    holdMouse(left);
    Sleep(75);
    moveMouse(x,y);
    Sleep(75);
    releaseMouse(left);
}

Keyboard::Keyboard() {
    
}

bool Keyboard::isKeyDown(int key) {
    return (GetAsyncKeyState(key) & 0x8000) != 0;
}

void Keyboard::keyDown(int key) {
    KEYBDINPUT ki;
    ki.wVk = key;
    ki.wScan = 0; //not sure about this
    ki.dwFlags = 0;
    ki.time = 0;
    ki.dwExtraInfo = 0;
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki = ki;
    SendInput(1,&input,sizeof(INPUT));
}

void Keyboard::keyUp(int key) {
    KEYBDINPUT ki;
    ki.wVk = key;
    ki.wScan = 0; //not sure about this
    ki.dwFlags = KEYEVENTF_KEYUP;
    ki.time = 0;
    ki.dwExtraInfo = 0;
    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki = ki;
    SendInput(1,&input,sizeof(INPUT));
}

void Keyboard::sendString(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        short int res = VkKeyScan(str[i]);
        int vk = res & 0xFF;
        if (res & 0x100) { //shift
            keyDown(VK_SHIFT);
            Sleep(30);
            keyDown(vk);
            Sleep(15);
            keyUp(vk);
            Sleep(5);
            keyUp(VK_SHIFT);
        } else {
            keyDown(vk);
            Sleep(15);
            keyUp(vk);
        }
        Sleep(150);
    }
        
}

