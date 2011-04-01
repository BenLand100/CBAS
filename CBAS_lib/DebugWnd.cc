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

#include "DebugWnd.h"
#include "Bitmap.h"
#include "Main.h"

#include <iostream>
using namespace std;

long  DebugProc(HWND hwnd, unsigned int Message, unsigned int wParam, long lParam) {
    DebugWindow* debug = (DebugWindow*) GetWindowLongPtr(hwnd,GWLP_USERDATA);
    switch(Message) {
        case WM_CREATE:
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_PAINT: {
            PAINTSTRUCT paint;
            HDC dc = BeginPaint(hwnd, &paint);
            BitBlt(dc, 0, 0, debug->width, debug->height, debug->hdc, 0, 0, SRCCOPY);
            EndPaint(hwnd, &paint);               
        }
        
    }
    return DefWindowProc(hwnd, Message, wParam, lParam);
}

DebugWindow::DebugWindow(int w, int h) : width(w), height(h) {
    hdc = CreateCompatibleDC(0);
    hbmp = CreateCompatibleBitmap(hdc,width,height);
    SelectObject(hdc, hbmp);

    WNDCLASSEX wndclass;
    memset(&wndclass, 0, sizeof(WNDCLASSEX));
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.lpfnWndProc = DebugProc;
    wndclass.hCursor = LoadCursor(0, IDC_ARROW);
    wndclass.lpszClassName = "CBAS_DEBUG_BOX";
    wndclass.hIconSm = 0;
    RegisterClassEx(&wndclass);
    
    RECT size;
    size.top = size.left = 0;
    size.right = width;
    size.bottom = height;
    AdjustWindowRectEx(&size, WS_OVERLAPPEDWINDOW, true, WS_EX_OVERLAPPEDWINDOW);
    CreateWindowData data = {WS_EX_OVERLAPPEDWINDOW, "CBAS_DEBUG_BOX", "DebugBox", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, size.right - size.left, size.bottom - size.top, 0, 0, 0, (void*)this, &hwnd};
    SendMessage(staticInfo->messageGlobalHWND,WM_COMMAND,CREATE_WINDOW,reinterpret_cast<long>(&data));
    SetWindowLongPtr(hwnd,GWLP_USERDATA,reinterpret_cast<long>(this));
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);
}

DebugWindow::~DebugWindow() {
    DestroyWindow(hwnd);
    DeleteDC(hdc);
    DeleteObject(hbmp);
}

HDC DebugWindow::getHDC() {
    HDC hdcMem = CreateCompatibleDC(hdc);
    SelectObject(hdcMem, hbmp);
    return hdcMem;
}

void DebugWindow::freeHDC(HDC dc) {
    DeleteDC(dc);
}

void DebugWindow::update() {
    UpdateWindow(hwnd);
}
HWND DebugWindow::getHWND() {
    return hwnd;
}

