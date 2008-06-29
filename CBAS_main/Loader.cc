
#include "jni.h"


#include "jni.h"

#include <windows.h>
#include "jni.h"

typedef jint (*CreateJVM)(JavaVM**, void**, void*) __attribute__((stdcall));

JavaVM* vm;
JNIEnv* env;

HMODULE jvmdll;

void checkPath(char* javaBin) {
    HMODULE java = LoadLibrary("java.exe");
    if (!java) {
        char* path = getenv("PATH");
        if (!strstr(path, javaBin)) {
            char* newPath = (char*) malloc(strlen(path) + strlen(javaBin) + 2);
            sprintf(newPath, "PATH=%s;%s", path, javaBin);
            putenv(newPath);
        }
    }
    FreeLibrary(java);
}

HMODULE findLibrary() {
    HKEY jrekey;
    HKEY curjrekey;
    HMODULE jvmdll;
    char value[512], path[512];
    unsigned long size;
    RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\JavaSoft\\Java Runtime Environment", 0, KEY_QUERY_VALUE, &jrekey);
    size = 512;
    memset(value, 0, 512);
    RegQueryValueEx(jrekey, "CurrentVersion", 0, 0, (unsigned char*) value, &size);
    RegOpenKeyEx(jrekey, value, 0, KEY_QUERY_VALUE, &curjrekey);
    size = 512;
    RegQueryValueEx(curjrekey, "JavaHome", 0, 0, (unsigned char*) value, &size);
    memset(path, 0, 512);
    sprintf(path, "%s\\bin", value);
    checkPath(path);
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
        MessageBox(0, "CBAS Failed to load, Java not installed", "CBAS", MB_OK);
        return 1;
    }
    
    JavaVMInitArgs args;
    JavaVMOption options[1];

    char dir[MAX_PATH];
    GetCurrentDirectory(MAX_PATH,dir);
    char classpath[MAX_PATH];
    sprintf(classpath,"%s/%s",dir,"ClassPath");
    char path[MAX_PATH];
    sprintf(path,"-Xbootclasspath/a:%s",classpath);
    
    args.version = JNI_VERSION_1_4;
    args.nOptions = 1;
    options[0].optionString = path;
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

