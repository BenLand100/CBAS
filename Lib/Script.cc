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

//This file is require by the CBAS build process. It basically defines the entry
//points for scripts.

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
    staticInfo->vm->DetachCurrentThread();
	return res;
}

