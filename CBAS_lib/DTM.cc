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

#include "DTM.h"
#include <vector>
#include "zlib.h"

#include <iostream>
using namespace std;

DTMPoint::~DTMPoint() {
    while (children.size() > 0) {
        delete children.back();
        children.pop_back();
    }
}

DTM::DTM(char* data) {
    static char hex[16] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };
    unsigned char* input = (unsigned char*) malloc(strlen(data) / 2 + 1);
    unsigned char* iincr = input;
    unsigned char* output = (unsigned char*) malloc(512);
    unsigned char* oincr = output;
    unsigned char low, high;
    for ( ; ; ) {
        if (*data == 0) break;
        char next = toupper(*data);
        for (high = 0; high < 16 && hex[high] != next; ++high);
        data++;
        if (*data == 0) break;
        next = toupper(*data);
        for (low = 0; low < 16 && hex[low] != next; ++low);
        data++;
        *iincr = (high << 4) | low;
        iincr++;
    }
    z_stream z;
    memset(&z, 0, sizeof(z_stream));
    z.next_in = input;
    z.avail_in = (int)(iincr - input);
    z.next_out = output;
    z.avail_out = 512;
    inflateInit(&z);
    int index;
    vector<unsigned char> bytes;
    while (z.avail_in > 0) {
        inflate(&z, Z_NO_FLUSH);
        int count = 512 - z.avail_out;
        while (count--) {
            bytes.push_back(*oincr++);
        }
        z.next_out = output;
        z.avail_out = 512;
        oincr = output;
    }
    inflateEnd(&z);
    mainPoint = new DTMPoint();
    vector<DTMPoint*> map;
    int count = 0;
    for (int i = 0; i < bytes.size(); ) {
        if (bytes[i++] == 1) {
            int x = bytes[i++] | (bytes[i++] << 8) | (bytes[i++] << 16) | (bytes[i++] << 24);
            int y = bytes[i++] | (bytes[i++] << 8) | (bytes[i++] << 16) | (bytes[i++] << 24);
            i+=3;
            int size = bytes[i++] | (bytes[i++] << 8) | (bytes[i++] << 16) | (bytes[i++] << 24);
            int shape = bytes[i++] | (bytes[i++] << 8) | (bytes[i++] << 16) | (bytes[i++] << 24);
            int color = bytes[i++] | (bytes[i++] << 8) | (bytes[i++] << 16) | (bytes[i++] << 24);
            int tol = bytes[i++] | (bytes[i++] << 8) | (bytes[i++] << 16) | (bytes[i++] << 24);
            int tif = bytes[i++] | (bytes[i++] << 8) | (bytes[i++] << 16) | (bytes[i++] << 24);
            int parent = bytes[i++] | (bytes[i++] << 8) | (bytes[i++] << 16) | (bytes[i++] << 24);
            if (parent == -1) {
                mainPoint->x = x;
                mainPoint->y = y;
                mainPoint->size = size;
                mainPoint->tolerance = tol;
                mainPoint->color = rgb(color);
                map.clear();
                map.push_back(mainPoint);
            } else {
                DTMPoint* point = new DTMPoint();
                point->x = x - map[parent]->x;
                point->y = y - map[parent]->y;
                point->size = size;
                point->tolerance = tol;
                point->color = rgb(color);
                map.push_back(point);
                map[parent]->children.push_back(point);
            }
        }
    }
    free(input);
    free(output);
}

DTM::DTM(DTMPoint* mainPoint) {
    this->mainPoint = mainPoint;
}

DTM::~DTM() {
    delete mainPoint;
}

DTMPoint* DTM::getMainPoint() {
    return mainPoint;
}

ostream& operator<<(ostream& astream, DTMPoint& point) {
    astream << "{X:" << point.x << ";Y:" << point.y << ";Size:" << point.size << ";Color:{" << point.color << "};Tol:" << point.tolerance << ";Children:[";
    int size = point.children.size();
    for (int i = 0; i < size - 1; i++) {
        astream << *(point.children[i]) << ",";
    }
    if (size > 0) {
        astream << *(point.children.back()) << "]}";
    } else {
        astream << "]}";
    }
}

ostream& operator<<(ostream& astream, DTM& dtm) {
    astream << *(dtm.getMainPoint());
}
