#ifndef BITMAP_H
#define BITMAP_H

#include <windows.h>
#include "Color.h"
#include "dll.h"

class Bitmap {
    friend class Finder;
    
private:
    HDC dc;
    HBITMAP bitmap;
    RGB *pixels;
    int width;
    int height;
    void init(int width, int height);
public:
    EXPORT Bitmap(int width, int height);
    EXPORT Bitmap(int width, int height, char* data);
    EXPORT ~Bitmap();
    EXPORT HDC getDC();
    EXPORT PRGB getPixels();
    EXPORT int getWidth();
    EXPORT int getHeight();
    EXPORT void getSize(int& width, int& height);
};

#endif 
