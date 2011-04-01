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
