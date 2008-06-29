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


