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

