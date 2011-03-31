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

#ifndef FIND_H
#define FIND_H

#include "Color.h"
#include "Bitmap.h"
#include "Utils.h"
#include "DTM.h"
#include <vector>
#include "dll.h"

typedef struct {
    int sx,sy,ex,ey;
} SearchArea;

class Finder: public Compare {
    friend void updateHWND(Finder*, int sx, int sy, int ex, int ey);
    friend void updateScreen(Finder*, int sx, int sy, int ex, int ey);
    
public:
    EXPORT Finder(); //Whole screen as target
    EXPORT Finder(Bitmap* target);
    EXPORT Finder(HWND target);
    EXPORT Finder(PRGB target, int width, int height);
    EXPORT ~Finder();
    
    EXPORT RGB getColor(int x, int y);
    
    EXPORT bool findColor(int& x, int& y, RGB color, int sx, int sy, int ex, int ey);
    EXPORT bool findColorSpiral(int& x, int& y, RGB color, int sx, int sy, int ex, int ey);
    EXPORT bool findColorTol(int& x, int& y, RGB color,  int tol, int sx, int sy, int ex, int ey);
    EXPORT bool findColorSpiralTol(int& x, int& y, RGB color,  int tol, int sx, int sy, int ex, int ey);
    EXPORT bool findColorsTol(std::vector<Point>& points, RGB color,  int tol, int sx, int sy, int ex, int ey);
    EXPORT bool findColorsSpiralTol(int x, int y, std::vector<Point>& points, RGB color,  int tol, int sx, int sy, int ex, int ey);
    
    EXPORT bool findDTM(int& x, int& y, DTM& dtm, int sx, int sy, int ex, int ey);
    
    EXPORT bool findBitmap(int& x, int& y, Bitmap& bitmap, int sx, int sy, int ex, int ey);
    EXPORT bool findBitmapTol(int& x, int& y, Bitmap& bitmap, int tol, int sx, int sy, int ex, int ey);
    EXPORT bool findBitmapSpiral(int& x, int& y, Bitmap& bitmap, int sx, int sy, int ex, int ey);
    EXPORT bool findBitmapSpiralTol(int& x, int& y, Bitmap& bitmap, int tol, int sx, int sy, int ex, int ey);
    
private:
    void (*update) (Finder* find, int sx, int sy, int ex, int ey);
    Bitmap* bmp;
    HWND hwnd;
    HDC dc;
    PRGB target;
    int width, height;
    
    bool findDTMPoint(int& x, int& y, DTMPoint& dtm, int sx, int sy, int ex, int ey, SearchArea& area);
    
};

#endif


