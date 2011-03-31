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

#include "Bitmap.h"
#include "zlib.h"
#include <iostream>

using namespace std;

Bitmap::Bitmap(int width, int height) {
    init(width, height);
}

Bitmap::Bitmap(int width, int height, char* data) {
    init(width, height);
    static char hex[16] = {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
    };
    static char b64[64] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
        'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1',
        '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'
    };
    switch (*data) {
        case 'b': {
            data++;
            PRGB pincr = pixels;
            unsigned char* input = (unsigned char*) malloc(strlen(data) / 4 * 3);
            unsigned char* iincr = input;
            unsigned char* output = (unsigned char*) malloc(width*height*3);
            unsigned char* oincr = output;
            for ( ; ; ) {
                if (*data == 0) break;
                long accum = 0;
                int quad;
                for (int i = 0; i < 4; i++) {
                    char next = *(data++);
                    if (next == '=') break;
                    for (quad = 0; quad < 64 && b64[quad] != next; ++quad);
                    accum += quad << (18-i*6);
                }
                for (int i = 0; i < 3; i++) {
                    *(iincr++) = (accum >> (16-8*i)) & 255;
                }
            }
            z_stream z;
            memset(&z, 0, sizeof(z_stream));
            z.next_in = input;
            z.avail_in = (int)(iincr - input);
            z.next_out = output;
            z.avail_out = width*height*3*2;
            inflateInit(&z);
            int index;
            while (z.total_in == 0) {
                inflate(&z, Z_NO_FLUSH);
                int count = (width*height*3*2 - z.avail_out) / 3;
                char g = *oincr++;
                char b = *oincr++;
                count--;
                while (count--) {
                    pincr->r = *oincr++;
                    pincr->g = *oincr++;
                    pincr->b = *oincr++;
                    pincr++;
                }
                pincr->r = *oincr;
                pincr->g = g;
                pincr->b = b;
            }
            inflateEnd(&z);
            free(input);
            free(output);
        } break;
        case 'z': {
            data++;
            PRGB pincr = pixels;
            unsigned char* input = (unsigned char*) malloc(strlen(data) / 2 + 1);
            unsigned char* iincr = input;
            unsigned char* output = (unsigned char*) malloc(width*height*3*2);
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
            z.avail_out = width*height*3*2;
            inflateInit(&z);
            int index;
            while (z.total_in == 0) {
                inflate(&z, Z_NO_FLUSH);
                int count = (width*height*3*2 - z.avail_out) / 2 / 3;
                while (count--) {
                    high = *oincr++;
                    high -= 48;
                    if (high > 16) high -= 7;
                    low = *oincr++;
                    low -= 48;
                    if (low > 16) low -= 7;
                    pincr->r = (high << 4)|low;
                    high = *oincr++;
                    high -= 48;
                    if (high > 16) high -= 7;
                    low = *oincr++;
                    low -= 48;
                    if (low > 16) low -= 7;
                    pincr->g = (high << 4)|low;
                    high = *oincr++;
                    high -= 48;
                    if (high > 16) high -= 7;
                    low = *oincr++;
                    low -= 48;
                    if (low > 16) low -= 7;
                    pincr->b = (high << 4)|low;
                    pincr++;
                }
            }
            inflateEnd(&z);
            free(input);
            free(output);
        } break;
        default: {
            PRGB incr = pixels;
            while (true) {
                unsigned char low, high,next;
                if (*data == 0) break;
                next = toupper(*data);
                for (high = 0; high < 16 && hex[high] != next; ++high);
                data++;
                if (*data == 0) break;
                next = toupper(*data);
                for (low = 0; low < 16 && hex[low] != next; ++low);
                data++;
                incr->r = (high << 4) | low;
                if (*data == 0) break;
                next = toupper(*data);
                for (high = 0; high < 16 && hex[high] != next; ++high);
                data++;
                if (*data == 0) break;
                next = toupper(*data);
                for (low = 0; low < 16 && hex[low] != next; ++low);
                data++;
                incr->g = (high << 4) | low;
                if (*data == 0) break;
                next = toupper(*data);
                for (high = 0; high < 16 && hex[high] != next; ++high);
                data++;
                if (*data == 0) break;
                next = toupper(*data);
                for (low = 0; low < 16 && hex[low] != next; ++low);
                data++;
                incr->b = (high << 4) | low;
                cout << *incr++ << '\n';
            }
        }
    }
}

void Bitmap::init(int width, int height) {
    this->width = width;
    this->height = height;
    BITMAPINFO info;
    memset(&info, 0, sizeof(BITMAPINFO));
    info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;
    info.bmiHeader.biWidth = width;
    info.bmiHeader.biHeight = -height;
    dc = CreateCompatibleDC(0);
    bitmap = CreateDIBSection(dc, &info, DIB_RGB_COLORS, (void**)&(this->pixels), 0, 0);
    SelectObject(dc, bitmap);
}

Bitmap::~Bitmap() {
    DeleteDC(dc);
    DeleteObject(bitmap);
}

HDC Bitmap::getDC() {
    return dc;
}

PRGB Bitmap::getPixels() {
    return pixels;
}

int Bitmap::getWidth() {
    return width;
}

int Bitmap::getHeight() {
    return height;
}

void Bitmap::getSize(int& width, int& height) {
    width = this->width;
    height = this->height;
}

