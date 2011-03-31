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

#include "Color.h"
#include "Bitmap.h"
#include <math.h>

using namespace std;

XYZ toXYZ(RGB rgb) {
    float r = rgb.r / 255.0;
    float g = rgb.g / 255.0;
    float b = rgb.b / 255.0;
    r = (r > 0.0405) ?  pow(((r + 0.055) / 1.055), 2.4) * 100.0 : r / 7.7399;
    g = (g > 0.0405) ?  pow(((g + 0.055) / 1.055), 2.4) * 100.0 : g / 7.7399;
    b = (b > 0.0405) ?  pow(((b + 0.055) / 1.055), 2.4) * 100.0 : b / 7.7399;
    XYZ res;
    res.x = (r * 0.4124) + (g * 0.3576) + (b * 0.1805);
    res.y = (r * 0.2126) + (g * 0.7152) + (b * 0.0722);
    res.z = (r * 0.0193) + (g * 0.1192) + (b * 0.9505);
    return res;
}

HSL toHSL(RGB rgb) {
    float r, g, b;
    float max, min;
    HSL res;
    r = (float)rgb.r / 255.0;
    g = (float)rgb.g / 255.0;
    b = (float)rgb.b / 255.0;
    max = r > b ? r > g ? r : g : b > g ? b : g;
    min = r < b ? r < g ? r : g : b < g ? b : g;
    res.lum = (max + min) * 50.0;
    if (max == min) {
        res.hue = 0;
    } if (max == r) {
        if (g >= b) {
            res.hue = 16.6667 * ((g - b) / (max - min));
        } else {
            res.hue = 16.6667 * ((g - b) / (max - min)) + 100.0;
        }
    } else if (max == g) {
        res.hue = 16.6667 * ((b - r) / (max - min)) + 33.3333;
    } else {
        res.hue = 16.6667 * ((r - g) / (max - min)) + 66.6667;
    }
    if (res.lum == 0.0 || max == min) {
        res.sat = 0.0;
    } else if (res.lum < 50) {
        res.sat = (max - min) / (max + min) * 100.0;
    } else {
        res.sat = (max - min) / (2.0 - max - min) * 100.0;
    }
    return res;
}


RGB toRGB(XYZ xyz) {
    float x = xyz.x / 100.0;
    float y = xyz.y / 100.0;
    float z = xyz.z / 100.0;
    float r = (x *  3.2406) + (y * -1.5372) + (z * -0.4986);
    float g = (x * -0.9689) + (y *  1.8758) + (z *  0.0415);
    float b = (x *  0.0557) + (y * -0.2040) + (z *  1.0570);
    RGB res;
    res.r = (unsigned char)round(r > 0.003131 ? (1.055 * pow(r, 0.4167) - 0.055) * 255 : 3294.6 * r);
    res.g = (unsigned char)round(g > 0.003131 ? (1.055 * pow(g, 0.4167) - 0.055) * 255 : 3294.6 * g);
    res.b = (unsigned char)round(b > 0.003131 ? (1.055 * pow(b, 0.4167) - 0.055) * 255 : 3294.6 * b);
    return res;
}

RGB toRGB(HSL hsl) {
    float h = hsl.hue / 100.0;
    float s = hsl.sat / 100.0;
    float l = hsl.lum / 100.0;
    cout << h << ' ' << s << ' ' << l << '\n';
    float q = (l < 0.5) ? q = l * (1.0 + s) : l + s - l * s;
    float p = 2.0 * l - q;
    RGB res;
    float r = h + 0.3333;
    if (r > 1.0) r -= 1.0;
    if (r < 0.0) r += 1.0;
    if (r < 0.1667) {
        res.r = (unsigned char)round((p + (q-p) * 6.0 * r) * 255);
    } else if (r < 0.5) {
        res.r = (unsigned char)round(q * 255);
    } else if (r < 0.6667) {
        res.r = (unsigned char)round((p + (q-p) * 6.0 * (0.6667 - r)) * 255);
    } else {
        res.r = (unsigned char)round(p * 255);
    }
    float g = h;
    if (g > 1.0) g -= 1.0;
    if (g < 0.0) g += 1.0;
    if (g < 0.1667) {
        res.g = (unsigned char)round((p + (q-p) * 6.0 * g) * 255);
    } else if (g < 0.5) {
        res.g = (unsigned char)round(q * 255);
    } else if (g < 0.6667) {
        res.g = (unsigned char)round((p + (q-p) * 6.0 * (0.6667 - g)) * 255);
    } else {
        res.g = (unsigned char)round(p * 255);
    }
    float b = h - 0.3333;
    if (b > 1.0) b -= 1.0;
    if (b < 0.0) b += 1.0;
    if (b < 0.1667) {
        res.b = (unsigned char)round((p + (q-p) * 6.0 * b) * 255);
    } else if (b < 0.5) {
        res.b = (unsigned char)round(q * 255);
    } else if (b < 0.6667) {
        res.b = (unsigned char)round((p + (q-p) * 6.0 * (0.6667 - b)) * 255);
    } else {
        res.b = (unsigned char)round(p * 255);
    }
    return res;
}

bool Compare::cts0(RGB a, RGB b, int tol) {
    return abs(a.r - b.r) <= tol && abs(a.g - b.g) <= tol && abs(a.b - b.b) <= tol;
}

bool Compare::cts1(RGB a, RGB b, int tol) {
    return sqrt((a.r - b.r)*(a.r - b.r) + (a.g - b.g)*(a.g - b.g) + (a.b - b.b)*(a.b - b.b)) <= tol;
}

bool Compare::cts2(RGB a, RGB b, int tol) {
    static RGB lA = rgb(0), lB = rgb(0);
    static HSL hslA = toHSL(lA), hslB = toHSL(lB);
    if (lA.color != a.color) {
        lA = a;
        hslA = toHSL(a);
    }
    if (lB.color != b.color) {
        lB = b;
        hslB = toHSL(b);
    }
    return fabs(hslA.hue - hslB.hue) <= tol * modifierHue &&
            fabs(hslA.sat - hslB.sat) <= tol * modifierSat;
}

bool Compare::cts3(RGB a, RGB b, int tol) {
    static RGB lA = rgb(0), lB = rgb(0);
    static XYZ xyzA = toXYZ(lA), xyzB = toXYZ(lB);
    if (lA.color != a.color) {
        lA = a;
        xyzA = toXYZ(a);
    }
    if (lB.color != b.color) {
        lB = b;
        xyzB = toXYZ(b);
    }
    float sum, dnX, dnY, mod = sensitivityXYZ * 125.0;
    sum = xyzA.x + xyzA.y + xyzA.z;
    dnX = (xyzA.x / sum) * mod;
    dnY = (xyzA.y / sum) * mod;
    sum = xyzB.x + xyzB.y + xyzB.z;
    dnX -= (xyzB.x / sum) * mod;
    dnY -= (xyzB.y / sum) * mod;
    return sqrt(dnX*dnX + dnY*dnY) <= tol;
}

Compare::Compare() {
    cts = &Compare::cts1;
    sensitivityXYZ = 4.0;
    modifierHue = 0.2;
    modifierSat = 0.2;
}

Compare::~Compare() {
    
}

bool Compare::similarColors(RGB a, RGB b, int tol) {
    return (this->*Compare::cts)(a, b, tol);
}

void Compare::setCTS(int mode) {
    switch (mode) {
        case 0: cts = &Compare::cts0; break;
        case 1: cts = &Compare::cts1; break;
        case 2: cts = &Compare::cts2; break;
        case 3: cts = &Compare::cts3; break;
    }
}
