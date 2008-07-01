#ifndef MAIN_H
#define MAIN_H

#include <windows.h>
#include <iostream>
#include "jni.h"
#include "dll.h"

#define CREATE_WINDOW   1000
#define ATTACH_JVM      1001
#define PRINT_LN        1002

typedef struct {
    JavaVM* vm;
    HWND messageGlobalHWND;
    HANDLE messageLoopHandle;
    unsigned long messageLoopID;
    bool active;
} StaticInfo;

EXPORT extern StaticInfo *staticInfo;

long exceptionFilter(EXCEPTION_POINTERS* info) __attribute__((stdcall));

long GlobalProc(HWND hwnd, unsigned int Message, unsigned int wParam, long lParam) __attribute__((stdcall));
unsigned long messageLoop(void* threadData) __attribute__((stdcall));
unsigned long launchMonitor(void* threadData) __attribute__((stdcall));

EXPORT void println(char* str);

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

