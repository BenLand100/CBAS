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

#ifndef MAIN_H
#define MAIN_H

#include <windows.h>
#include <iostream>
#include "jni.h"
#include "dll.h"

#define CREATE_WINDOW   1000
#define ATTACH_JVM      1001

class JavaOut : public std::streambuf {
private:
    jobject out;
    jmethodID print;
public:
    JavaOut(jobject pthis);
    ~JavaOut();
protected:
    int overflow(int c);
};

typedef struct {
    JavaVM* vm;
    HWND messageGlobalHWND;
    HANDLE messageLoopHandle;
    unsigned long messageLoopID;
    bool active;
    JavaOut* joutbuf;
} StaticInfo;

EXPORT extern std::ostream jout;
EXPORT extern StaticInfo *staticInfo;

long exceptionFilter(EXCEPTION_POINTERS* info) __attribute__((stdcall));

long GlobalProc(HWND hwnd, unsigned int Message, unsigned int wParam, long lParam) __attribute__((stdcall));
unsigned long messageLoop(void* threadData) __attribute__((stdcall));
unsigned long launchMonitor(void* threadData) __attribute__((stdcall));

typedef struct {
    long dwExStyle; 
    char* lpClassName;
    char* lpWindowName;
    long dwStyle;
    int x;
    int y;
    int nWidth;
    int nHeight;
    HWND hWndParent;
    HMENU hMenu;
    HINSTANCE hInstance;
    void* lpParam;
    HWND* hwndRef;
} CreateWindowData;

#endif

