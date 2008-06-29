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
