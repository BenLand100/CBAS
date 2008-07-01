#ifndef DEBUGWND_H
#define DEBUGWND_H

#include <windows.h>
#include "dll.h"

#warning links gdi32

long DebugProc(HWND hwnd, unsigned int Message, unsigned int wParam, long lParam) __attribute__((stdcall));

class DebugWindow {
public:
    EXPORT DebugWindow(int width, int height);
    EXPORT ~DebugWindow();
    EXPORT HDC getHDC();
    EXPORT void freeHDC(HDC dc);
    EXPORT HWND getHWND();
private:
    HWND hwnd; 
};

#endif

