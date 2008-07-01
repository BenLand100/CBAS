#ifndef PLUGINS_H
#define PLUGINS_H

#include "Utils.h"
#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include "dll.h"

class PluginLoader {
    
public:
    EXPORT PluginLoader(const char* pluginDir);
    EXPORT ~PluginLoader();
    EXPORT void* getMethodAddress(const char* name);
    
private:
    std::vector<HINSTANCE> handles;
    std::map<const char*, void*, strCmp> addrs;
    
};

#endif

