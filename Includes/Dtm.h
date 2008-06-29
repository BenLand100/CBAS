#ifndef DTM_H
#define	DTM_H

#include "Color.h"
#include <vector>
#include <iostream>
#include "dll.h"

class DTMPoint {
    friend class Finder;
    
public:
    EXPORT int x;
    EXPORT int y;
    EXPORT int size;
    EXPORT RGB color;
    EXPORT int tolerance;
    EXPORT std::vector<DTMPoint*> children;
    EXPORT ~DTMPoint();
};

class DTM {
    friend class Finder;
    
public:
    EXPORT DTM(char* data);
    EXPORT DTM(DTMPoint* mainPoint);
    EXPORT ~DTM();
    EXPORT DTMPoint* getMainPoint();
private:
    DTMPoint* mainPoint;
};

EXPORT std::ostream& operator<<(std::ostream& astream, DTMPoint& point);

EXPORT std::ostream& operator<<(std::ostream& astream, DTM& dtm);

#endif

