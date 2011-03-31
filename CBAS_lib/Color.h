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

#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "dll.h"

typedef struct {
    float x, y, z;
} XYZ, *PXYZ;

typedef struct {
    float hue, sat, lum;
} HSL, *PHSL;

typedef union {
    unsigned int color;
    struct { unsigned char b, g, r, a; };
} RGB, *PRGB;

inline std::ostream& operator<<(std::ostream& anout, RGB rgb) {
    return anout << "R:" << (int)rgb.r << " G:" << (int)rgb.g << " B:" << (int)rgb.b;
}

inline std::ostream& operator<<(std::ostream& anout, HSL hsl) {
    return anout << "H:" << hsl.hue << " S:" << hsl.sat << " L:" << hsl.lum;
}

inline std::ostream& operator<<(std::ostream& anout, XYZ xyz) {
    return anout << "X:" << xyz.x << " Y:" << xyz.y << " Z:" << xyz.z;
}


inline XYZ xyz(float x, float y, float z) {
    XYZ xyz = {x, y, z};
    return xyz;
}

inline HSL hsl(float hue, float sat, float lum) {
    HSL hsl = {hue, sat, lum};
    return hsl;
}

inline RGB rgb(int r, int g, int b) {
    RGB res = { (b & 255) | ((g & 255) << 8) | ((r & 255) << 16) };
    return res;
}

inline RGB rgb(long color) {
    RGB res = {color};
    return res;
}

EXPORT XYZ toXYZ(RGB rgb);

EXPORT HSL toHSL(RGB rgb);

EXPORT RGB toRGB(XYZ xyz);

EXPORT RGB toRGB(HSL hsl);

class Compare {
    
public:
    EXPORT Compare();
    EXPORT ~Compare();
    EXPORT void setCTS(int mode);
    EXPORT bool similarColors(RGB a, RGB b, int tol);
    
    EXPORT float sensitivityXYZ;
    EXPORT float modifierHue;
    EXPORT float modifierSat;
    
protected:
    EXPORT bool (Compare::*cts) (RGB a, RGB b, int tol);
    EXPORT bool cts0(RGB a, RGB b, int tol);
    EXPORT bool cts1(RGB a, RGB b, int tol);
    EXPORT bool cts2(RGB a, RGB b, int tol);
    EXPORT bool cts3(RGB a, RGB b, int tol);
    
};

#endif

