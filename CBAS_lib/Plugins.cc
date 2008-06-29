#include "Plugins.h"
#include <iostream>

using namespace std;

typedef long (*GetFunctionInfo)(int index, void** address, char** def) __attribute__((stdcall));
typedef long (*GetFunctionCount)() __attribute__((stdcall));

void lower(char* str) {
    while (*str != 0) {
        *str = (char) tolower(*str);
        *str++;
    }
}

PluginLoader::PluginLoader(const char* pluginDir) {
    cout << "Loading plugins from " << pluginDir << "\n";
    int dirlen = strlen(pluginDir);
    char search[MAX_PATH];
    char temp[MAX_PATH];
    strcpy(search, pluginDir);
    strcat(search, "/*.dll");
    HANDLE find;
    WIN32_FIND_DATA file;
    find = FindFirstFile(search, &file);
    if (find != INVALID_HANDLE_VALUE) {
        do {
            strcpy(temp, pluginDir);
            strcat(temp, "/");
            strcat(temp, file.cFileName);
            cout << "Loading " << file.cFileName << "\n";
            HINSTANCE inst = LoadLibrary(temp);
            if (inst) {
                handles.push_back(inst);
                GetFunctionCount count = (GetFunctionCount)GetProcAddress(inst,"GetFunctionCount");
                GetFunctionInfo info = (GetFunctionInfo)GetProcAddress(inst,"GetFunctionInfo");
                if (count != 0 && info != 0) {
                    long functions = count();
                    for (int i = 0; i < functions; i++) {
                        try {
                            void* address;
                            char* def = (char*)malloc(512);
                            if (info(i,&address,&def) == -1) break;
                            char* ref = def; 
                            lower(def);
                            while (*def == ' ') def++;
                            while (*def != ' ') def++;
                            while (*def == ' ') def++;
                            char* start = def;
                            while ((*def != ' ') && (*def != '(') && (*def != ':') && (*def != ';')) def++;
                            *def = 0;
                            char* name = (char*)malloc(def - start + 1);
                            strcpy(name, start);
                            addrs[name] = address;
                            cout << "\t" << name << "\n";
                            free(ref);
                        } catch (...) {
                            cout << "Error loading function index " << i << " from " << file.cFileName << "\n";
                        }
                    }
                }
            }
        } while (FindNextFile(find, &file));
        cout << "Done loading plugins!\n";
        FindClose(find);
    } 
}

PluginLoader::~PluginLoader() {
    while (!handles.empty()) {
        FreeLibrary(handles.back());
        handles.pop_back();
    }
    map<const char*, void*>::iterator it;
    for (it = addrs.begin(); it != addrs.end(); it++) {
        free((void*)(it->first));
    }
    addrs.clear();
}

void* PluginLoader::getMethodAddress(const char* name) {
    char* lowerName;
    lowerName = (char*)malloc(strlen(name)+1);
    strcpy(lowerName, name);
    lower(lowerName);
    if (addrs.end() != addrs.find(lowerName))
        return addrs[lowerName];
    return 0;
}
