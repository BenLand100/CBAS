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

#include "Utils.h"
#include <windows.h>

#include <iostream>
using namespace std;

unsigned long long timeMills() {
    ULARGE_INTEGER uli;
    GetSystemTimeAsFileTime(reinterpret_cast<FILETIME*>(&uli));
    return uli.QuadPart/10000;
}

Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

PointSort::PointSort(Point relative) {
    this->relative = relative;
}

bool PointSort::operator() (Point i, Point j) {
    return dist(relative, i) < dist(relative, j);
}

bool strCmp::operator()(const char* a, const char* b) {
    return strcmp(a, b) < 0;
};
