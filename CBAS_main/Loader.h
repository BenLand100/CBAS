#ifndef LOADER_H
#define	LOADER_H

#include <windows.h>
#include "jni.h"

extern JNIEnv* env;
extern JavaVM* vm;

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow) __attribute__((stdcall));

#endif

