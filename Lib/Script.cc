#include <windows.h>
#include "Main.h"

extern "C" bool DllMain(HINSTANCE, int, void*) __attribute__((stdcall));

bool DllMain(HINSTANCE instance, int reason, void* checks) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            return true;
        case DLL_THREAD_ATTACH:
            return true;
        case DLL_PROCESS_DETACH:
            return true;
        case DLL_THREAD_DETACH:
            return true;
    }
    return false;
}

extern "C" unsigned long _impl_scriptmain(void *info) __attribute__((stdcall));
int scriptmain();

unsigned long _impl_scriptmain(void *info) {
	staticInfo = (StaticInfo*)info;
	JNIEnv* env;
	staticInfo->vm->AttachCurrentThreadAsDaemon((void**)&env, 0);
	jout.rdbuf(staticInfo->joutbuf);
	int res = scriptmain();
	return res;
    staticInfo->vm->DetachCurrentThread();
}

