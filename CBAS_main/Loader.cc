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

#include <iostream>
#include "Loader.h"

using namespace std;

typedef jint (*CreateJVM)(JavaVM**, void**, void*) __attribute__((stdcall));

JavaVM* vm;
JNIEnv* env;

HMODULE jvmdll;

void checkPath(char* path) {
    char* pathenv = getenv("PATH");
    if (!strstr(pathenv, path)) {
        char* newPath = (char*) malloc(strlen(pathenv) + strlen(path) + 2);
        sprintf(newPath, "PATH=%s;%s", pathenv, path);
        putenv(newPath);
        free(newPath);
    }
    free(pathenv);
}

HMODULE findLibrary() {
    HMODULE jvmdll;
    HKEY jrekey;
    HKEY curjrekey;
    char value[512], path[512];
    unsigned long size;
    RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\JavaSoft\\Java Runtime Environment", 0, KEY_QUERY_VALUE, &jrekey);
    size = 512;
    memset(value, 0, 512);
    RegQueryValueEx(jrekey, "CurrentVersion", 0, 0, (unsigned char*)value, &size);
    RegOpenKeyEx(jrekey, value, 0, KEY_QUERY_VALUE, &curjrekey);
    size = 512;
    RegQueryValueEx(curjrekey, "JavaHome", 0, 0, (unsigned char*)value, &size);
    memset(path, 0, 512);
    sprintf(path, "%s\\bin", value);
    memset(path, 0, 512);
    sprintf(path, "%s\\bin\\server\\jvm.dll", value);
    if (!(jvmdll = LoadLibrary(path))) {
        memset(path, 0, 512);
        sprintf(path, "%s\\bin\\client\\jvm.dll", value);
        if (!(jvmdll = LoadLibrary(path))) {
            return 0;
        }
    }
    return jvmdll;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* lpCmdLine, int nCmdShow) {
    jvmdll = findLibrary();
    if (!jvmdll) {
        MessageBox(0, "CBAS Failed to load, Java must not be installed", "CBAS", MB_OK);
        return 1;
    }
    JavaVMInitArgs args;
    JavaVMOption options[3];
    char dir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH,dir);
    char libpath[MAX_PATH];
    sprintf(libpath,"%s\\%s",dir,"Lib");
    checkPath(libpath);
    char classpath[MAX_PATH];
    sprintf(classpath,"%s\\%s",dir,"ClassPath");
    char path[MAX_PATH];
    sprintf(path,"-Xbootclasspath/p:%s",classpath);
    cout << "ClassPath: " << path << "\n";
    args.version = JNI_VERSION_1_6;
    args.nOptions = 3;
    options[0].optionString = path;
    options[1].optionString = "-Dsun.java2d.noddraw";
    options[2].optionString = "-Xcheck:jni";
    args.options = options;
    args.ignoreUnrecognized = JNI_FALSE;

    CreateJVM create = (CreateJVM) GetProcAddress(jvmdll, "JNI_CreateJavaVM");
    
    create(&vm, (void**)&env, &args);
    jclass CodeEditor = env->FindClass("cbas/CodeEditor");
    jmethodID init = env->GetMethodID(CodeEditor,"<init>","()V");
    jfieldID living = env->GetFieldID(CodeEditor,"living","Z");
    jobject cbas = env->NewObject(CodeEditor,init);
    env->DeleteLocalRef(CodeEditor);
    jclass JFrame = env->FindClass("javax/swing/JFrame");
    jmethodID setVisible = env->GetMethodID(JFrame,"setVisible","(Z)V");
    env->CallVoidMethod(cbas,setVisible,JNI_TRUE);
    env->DeleteLocalRef(JFrame);
    while (env->GetBooleanField(cbas,living)) {
        Sleep(5000);
    }
    env->DeleteLocalRef(cbas);
    vm->DetachCurrentThread();
    FreeLibrary(jvmdll);
    return 0;
}

