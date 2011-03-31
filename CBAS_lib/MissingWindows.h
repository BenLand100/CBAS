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

#ifndef MISSINGWINDOWS_H
#define MISSINGWINDOWS_H

#include <windows.h>

#ifdef	__cplusplus
extern "C" {
#endif
    
    #define INPUT_MOUSE 0
    #define INPUT_KEYBOARD 1
    #define INPUT_HARDWARE 2
 
    typedef struct tagHARDWAREINPUT {
        DWORD uMsg;
        WORD wParamL;
        WORD wParamH;
    } HARDWAREINPUT, *PHARDWAREINPUT;

    typedef struct tagKEYBDINPUT {
        WORD wVk;
        WORD wScan;
        DWORD dwFlags;
        DWORD time;
        ULONG_PTR dwExtraInfo;
    } KEYBDINPUT, *PKEYBDINPUT;

    typedef struct tagMOUSEINPUT {
        LONG dx;
        LONG dy;
        DWORD mouseData;
        DWORD dwFlags;
        DWORD time;
        ULONG_PTR dwExtraInfo;
    } MOUSEINPUT, *PMOUSEINPUT;

    typedef struct tagINPUT {
        DWORD type;

        union {
            MOUSEINPUT mi;
            KEYBDINPUT ki;
            HARDWAREINPUT hi;
        };
    } INPUT, *PINPUT;

    UINT SendInput(UINT nInputs, PINPUT pInputs, int cbSize) __attribute__((stdcall));

#ifdef	__cplusplus
}
#endif

#endif	/* MISSINGWINDOWS_H */

