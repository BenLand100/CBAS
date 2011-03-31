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

