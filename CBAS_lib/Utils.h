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

#ifndef UTILS_H
#define	UTILS_H

#include <math.h>
#include "dll.h"

EXPORT class Point {
public:
    int x;
    int y;
    Point();
    Point(int x, int y);
};

EXPORT unsigned long long timeMills();

inline Point point(int x, int y) {
    Point p(x,y);
    return p;
}

inline double dist(Point& a, Point& b) {
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

EXPORT class PointSort {
    Point relative;
public:
    bool operator() (Point i, Point j);
    PointSort(Point relative);
};

EXPORT class strCmp {
public:
    bool operator()(const char* a, const char* b);
};


#endif


