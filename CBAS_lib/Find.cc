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

#include "Find.h"

#include <iostream>
using namespace std;

void updateHWND(Finder* find, int sx, int sy, int ex, int ey) {
    RECT rect;
    GetWindowRect(find->hwnd, &rect);
    if (rect.bottom - rect.top != find->height || rect.right - rect.left != find->width) {
        if (find->bmp) delete find->bmp;
        find->bmp = new Bitmap(rect.right - rect.left, rect.bottom - rect.top);
        find->target = find->bmp->getPixels();
        if (find->dc) ReleaseDC(find->hwnd, find->dc);
        find->dc = GetDC(find->hwnd);
        find->bmp->getSize(find->width, find->height);
    }
    BitBlt(find->bmp->getDC(), sx, sy, ex - sx + 1, ey - sy + 1, find->dc, sx, sy, SRCCOPY);
}

void updateScreen(Finder* find, int sx, int sy, int ex, int ey) {
    BitBlt(find->bmp->getDC(), sx, sy, ex - sx + 1, ey - sy + 1, find->dc, sx, sy, SRCCOPY);
}

Finder::Finder() {
    hwnd = 0;
    update = &updateScreen;
    dc = GetDC(0);
    bmp = new Bitmap(GetDeviceCaps(dc,HORZRES),GetDeviceCaps(dc,VERTRES));
    update(this, 0, 0, width-1, height-1);
}

Finder::Finder(Bitmap* target) {
    this->target = target->getPixels();
    target->getSize(width, height);
    update = 0;
    dc = 0;
    hwnd = 0;
}

Finder::Finder(HWND target) {
    hwnd = target;
    update = &updateHWND;
    dc = 0;
    bmp = 0;
    update(this, 0, 0, width-1, height-1);
}

Finder::Finder(PRGB target, int width, int height) {
    this->target = target;
    this->width = width;
    this->height = height;
    update = 0;
    dc = 0;
    hwnd = 0;
    bmp = 0;
}

Finder::~Finder() {
    if (bmp) delete bmp;
    if (dc) ReleaseDC(hwnd, dc);
}

RGB Finder::getColor(int x, int y) {
    if (dc) {
        RGB res = {GetPixel(dc, x, y)};
        return res;
    }
    return target[x+y*width];
}

bool Finder::findColor(int& x, int& y, RGB color, int sx, int sy, int ex, int ey) {
    if (update) update(this, sx, sy, ex, ey);
    sy = reinterpret_cast<int>(sy * width + target);
    ey = reinterpret_cast<int>(ey * width + target);
    for (PRGB hinc = reinterpret_cast<PRGB>(sy); hinc <= reinterpret_cast<PRGB>(ey); hinc += width) {
        PRGB wend = ex + hinc;
        for (PRGB winc = sx + hinc; winc <= wend; winc++) {
            if (winc->color == color.color) {
                int i = winc - target;
                x = i % width;
                y = i / width;
                return true;
            }
        }
    }
    return false;
}

bool Finder::findColorTol(int& x, int& y, RGB color, int tol, int sx, int sy, int ex, int ey) {
    if (update) update(this, sx, sy, ex, ey);
    sy = reinterpret_cast<int>(sy * width + target);
    ey = reinterpret_cast<int>(ey * width + target);
    for (PRGB hinc = reinterpret_cast<PRGB>(sy); hinc <= reinterpret_cast<PRGB>(ey); hinc += width) {
        PRGB wend = ex + hinc;
        for (PRGB winc = sx + hinc; winc <= wend; winc++) {
            if ((this->*Compare::cts)(*winc, color, tol)) {
                int i = winc - target;
                x = i % width;
                y = i / width;
                return true;
            }
        }
    }
    return false;
}

bool Finder::findColorSpiral(int& x, int& y, RGB color, int sx, int sy, int ex, int ey) {
    int cx = x, cy = y;
    char dir = 0; //0-left; 1-down; 2-right; 3-up
    int layer = 0;
    bool ul = false, ur = false, dl = false, dr = false;
    Loop: if (target[cy*width+cx].color == color.color) {
        x = cx;
        y = cy;
        return true;
    }
    if (cx == sx && cy == sy) ul = true;
    if (cx == ex && cy == sy) ur = true;
    if (cx == sx && cy == ey) dl = true;
    if (cx == ex && cy == ey) dr = true;
    if (ul && ur && dl && dr) {
        return false;
    }
    switch (dir) {
        case 0:
            if (cx == x + 1 + layer) {
                layer++;
                dir = 1;
                break;
            } else if (cx == ex && cx != x + layer) {
                goto SkipLoop;
            }
            break;
        case 1:
            if (cy == y + layer) {
                dir = 2;
                break;
            } else if (cy == ey) {
                goto SkipLoop;
            }
            break;
        case 2:
            if (cx == x - layer) {
                dir = 3;
                break;
            } else if (cx == sx) {
                goto SkipLoop;
            }
            break;
        case 3:
            if (cy == y - layer) {
                dir = 0;
                break;
            } else if (cy == sy) {
                goto SkipLoop;
            }
            break;
    }
    switch (dir) {
        case 0: cx++; break;
        case 1: cy++; break;
        case 2: cx--; break;
        case 3: cy--; break;
    }
    goto Loop;
    SkipLoop: if (dir == 3) dir = 0; else dir++;
    switch (dir) { //Its been incremented
        case 1:
            if (dr) {
                goto SkipLoop;
            } else {
                cx = ex;
                cy = y + layer;
            }
            break;
        case 2:
            if (dl) {
                goto SkipLoop;
            } else {
                cx = x - layer;
                cy = ey;
            }
            break;
        case 3:
            if (ul) {
                goto SkipLoop;
            } else {
                cx = sx;
                cy = y - layer;
            }
            break;
        case 0:
            if (ur) {
                layer++;
                goto SkipLoop;
            } else {
                layer++;
                cx = x + layer;
                cy = sy;
            }
            break;
    }
    if (dir == 3) dir = 0; else dir++;
    goto Loop;
}


bool Finder::findColorSpiralTol(int& x, int& y, RGB color, int tol, int sx, int sy, int ex, int ey) {
    int cx = x, cy = y;
    char dir = 0; //0-left; 1-down; 2-right; 3-up
    int layer = 0;
    bool ul = false, ur = false, dl = false, dr = false;
    Loop: if ((this->*Compare::cts)(target[cy*width+cx], color, tol)) {
        x = cx;
        y = cy;
        return true;
    }
    if (cx == sx && cy == sy) ul = true;
    if (cx == ex && cy == sy) ur = true;
    if (cx == sx && cy == ey) dl = true;
    if (cx == ex && cy == ey) dr = true;
    if (ul && ur && dl && dr) {
        return false;
    }
    switch (dir) {
        case 0:
            if (cx == x + 1 + layer) {
                layer++;
                dir = 1;
                break;
            } else if (cx == ex && cx != x + layer) {
                goto SkipLoop;
            }
            break;
        case 1:
            if (cy == y + layer) {
                dir = 2;
                break;
            } else if (cy == ey) {
                goto SkipLoop;
            }
            break;
        case 2:
            if (cx == x - layer) {
                dir = 3;
                break;
            } else if (cx == sx) {
                goto SkipLoop;
            }
            break;
        case 3:
            if (cy == y - layer) {
                dir = 0;
                break;
            } else if (cy == sy) {
                goto SkipLoop;
            }
            break;
    }
    switch (dir) {
        case 0: cx++; break;
        case 1: cy++; break;
        case 2: cx--; break;
        case 3: cy--; break;
    }
    goto Loop;
    SkipLoop: if (dir == 3) dir = 0; else dir++;
    switch (dir) { //Its been incremented
        case 1:
            if (dr) {
                goto SkipLoop;
            } else {
                cx = ex;
                cy = y + layer;
            }
            break;
        case 2:
            if (dl) {
                goto SkipLoop;
            } else {
                cx = x - layer;
                cy = ey;
            }
            break;
        case 3:
            if (ul) {
                goto SkipLoop;
            } else {
                cx = sx;
                cy = y - layer;
            }
            break;
        case 0:
            if (ur) {
                layer++;
                goto SkipLoop;
            } else {
                layer++;
                cx = x + layer;
                cy = sy;
            }
            break;
    }
    if (dir == 3) dir = 0; else dir++;
    goto Loop;
}

bool Finder::findColorsTol(std::vector<Point>& points, RGB color, int tol, int sx, int sy, int ex, int ey) {
    points.clear();
    points.reserve((ex - sx) * (ey - sy));
    if (update) update(this, sx, sy, ex, ey);
    sy = reinterpret_cast<int>(sy * width + target);
    ey = reinterpret_cast<int>(ey * width + target);
    bool res = false;
    Point pt;
    for (PRGB hinc = reinterpret_cast<PRGB>(sy); hinc <= reinterpret_cast<PRGB>(ey); hinc += width) {
        PRGB wend = ex + hinc;
        for (PRGB winc = sx + hinc; winc <= wend; winc++) {
            if ((this->*Compare::cts)(*winc, color, tol)) {
                int i = winc - target;
                pt.x = i % width;
                pt.y = i / width;
                points.push_back(pt);
                res = true;
            }
        }
    }
    return res;
}



bool Finder::findColorsSpiralTol(int x, int y, std::vector<Point>& points, RGB color, int tol, int sx, int sy, int ex, int ey) {
    points.clear();
    points.reserve((ex - sx) * (ey - sy));
    if (update) update(this, sx, sy, ex, ey);
    Point pt;
    bool res = false;
    int cx = x, cy = y;
    char dir = 0; //0-left; 1-down; 2-right; 3-up
    int layer = 0;
    bool ul = false, ur = false, dl = false, dr = false;
    Loop: if ((this->*Compare::cts)(target[cy*width+cx], color, tol)) {
        pt.x = cx;
        pt.y = cy;
        points.push_back(pt);
        res = true;
    }
    if (cx == sx && cy == sy) ul = true;
    if (cx == ex && cy == sy) ur = true;
    if (cx == sx && cy == ey) dl = true;
    if (cx == ex && cy == ey) dr = true;
    if (ul && ur && dl && dr) {
        return res;
    }
    switch (dir) {
        case 0:
            if (cx == x + 1 + layer) {
                layer++;
                dir = 1;
                break;
            } else if (cx == ex && cx != x + layer) {
                goto SkipLoop;
            }
            break;
        case 1:
            if (cy == y + layer) {
                dir = 2;
                break;
            } else if (cy == ey) {
                goto SkipLoop;
            }
            break;
        case 2:
            if (cx == x - layer) {
                dir = 3;
                break;
            } else if (cx == sx) {
                goto SkipLoop;
            }
            break;
        case 3:
            if (cy == y - layer) {
                dir = 0;
                break;
            } else if (cy == sy) {
                goto SkipLoop;
            }
            break;
    }
    switch (dir) {
        case 0: cx++; break;
        case 1: cy++; break;
        case 2: cx--; break;
        case 3: cy--; break;
    }
    goto Loop;
    SkipLoop: if (dir == 3) dir = 0; else dir++;
    switch (dir) { //Its been incremented
        case 1:
            if (dr) {
                goto SkipLoop;
            } else {
                cx = ex;
                cy = y + layer;
            }
            break;
        case 2:
            if (dl) {
                goto SkipLoop;
            } else {
                cx = x - layer;
                cy = ey;
            }
            break;
        case 3:
            if (ul) {
                goto SkipLoop;
            } else {
                cx = sx;
                cy = y - layer;
            }
            break;
        case 0:
            if (ur) {
                layer++;
                goto SkipLoop;
            } else {
                layer++;
                cx = x + layer;
                cy = sy;
            }
            break;
    }
    if (dir == 3) dir = 0; else dir++;
    goto Loop;
}

bool Finder::findDTMPoint(int& x, int& y, DTMPoint& dtm, int sx, int sy, int ex, int ey, SearchArea& area) {
    sy = reinterpret_cast<int>(sy * width + target);
    ey = reinterpret_cast<int>(ey * width + target);
    for (PRGB hinc = reinterpret_cast<PRGB>(sy); hinc <= reinterpret_cast<PRGB>(ey); hinc += width) {
        PRGB wend = ex + hinc;
        for (PRGB winc = sx + hinc; winc <= wend; winc++) {
            if ((this->*Compare::cts)(*winc, dtm.color, dtm.tolerance)) {
                int i = winc - target;
                x = i % width;
                y = i / width;
                int size = dtm.children.size();
                if (size > 0) {
                    int nx, ny;
                    for (i = 0; i < size; i++) {
                        DTMPoint next = *(dtm.children[i]);
                        int nsx = max(area.sx, x + next.x - next.size);
                        int nsy = max(area.sy, y + next.y - next.size);
                        int nex = min(area.ex, x + next.x + next.size);
                        int ney = min(area.ey, y + next.y + next.size);
                        if (ney < nsy || nex < nsx) return false;
                        if (!findDTMPoint(nx, ny, next, nsx, nsy, nex, ney, area)) return false;
                    }
                }
                return true;
            }
        }
    }
    return false;
}

bool Finder::findDTM(int& x, int& y, DTM& dtm, int sx, int sy, int ex, int ey) {
    if (update) update(this, sx, sy, ex, ey);
    SearchArea area = {sx, sy, ex, ey};
    return findDTMPoint(x,y,*(dtm.mainPoint),sx,sy,ex,ey,area);
}

//Test!!!
bool Finder::findBitmap(int& x, int& y, Bitmap& bitmap, int sx, int sy, int ex, int ey) {
    if (update) update(this, sx, sy, ex, ey);
    PRGB bpx = bitmap.getPixels();
    int bw, bh;
    bitmap.getSize(bw,bh);
    int scan = width - bw;
    int last = bh * bw - 1;
    int scanlast = (bh - 1) * width + bw - 1;
    ey -= bh;
    ex -= bw;
    sy = reinterpret_cast<int>(sy * width + target);
    ey = reinterpret_cast<int>(ey * width + target);
    for (PRGB hinc = reinterpret_cast<PRGB>(sy); hinc <= reinterpret_cast<PRGB>(ey); hinc += width) {
        PRGB wend = ex + hinc;
        for (PRGB winc = sx + hinc; winc <= wend; winc++) {
            if (winc->color == bpx->color && winc[scanlast].color == bpx[last].color) {
                PRGB binc = bpx;
                PRGB ihend = winc + bh * width + bw;
                int i;
                for (PRGB ihinc = winc; ihinc < ihend; ihinc += scan) {
                    PRGB iwend = ihinc + bw;
                    for (PRGB iwinc = ihinc; iwinc < iwend; iwinc++) {
                        if (iwinc->color != (binc++)->color) goto Skip;
                    }
                }
                i = winc - target;
                x = i % width;
                y = i / width;
                return true;
                Skip:			
                continue;
            }
        }
    }
    return false;
}

//Test!!!
bool Finder::findBitmapTol(int& x, int& y, Bitmap& bitmap, int tol, int sx, int sy, int ex, int ey) {
    if (update) update(this, sx, sy, ex, ey);
    PRGB bpx = bitmap.getPixels();
    int bw, bh;
    bitmap.getSize(bw,bh);
    int scan = width - bw;
    int last = bh * bw - 1;
    int scanlast = (bh - 1) * width + bw - 1;
    ey -= bh;
    ex -= bw;
    sy = reinterpret_cast<int>(sy * width + target);
    ey = reinterpret_cast<int>(ey * width + target);
    for (PRGB hinc = reinterpret_cast<PRGB>(sy); hinc <= reinterpret_cast<PRGB>(ey); hinc += width) {
        PRGB wend = ex + hinc;
        for (PRGB winc = sx + hinc; winc <= wend; winc++) {
            if ((this->*Compare::cts)(*winc, *bpx, tol) && (this->*Compare::cts)(winc[scanlast],bpx[last],tol)) {
                PRGB binc = bpx;
                PRGB ihend = winc + bh * width + bw;
                int i;
                for (PRGB ihinc = winc; ihinc < ihend; ihinc += scan) {
                    PRGB iwend = ihinc + bw;
                    for (PRGB iwinc = ihinc; iwinc < iwend; iwinc++) {
                        if ((this->*Compare::cts)(*iwinc, *binc++, tol)) goto Skip;
                    }
                }
                i = winc - target;
                x = i % width;
                y = i / width;
                return true;
                Skip:			
                continue;
            }
        }
    }
    return false;
}

//Test!!!
bool Finder::findBitmapSpiral(int& x, int& y, Bitmap& bitmap, int sx, int sy, int ex, int ey) {
    int cx = x, cy = y;
    PRGB bpx = bitmap.getPixels();
    int bw, bh;
    bitmap.getSize(bw,bh);
    int scan = width - bw;
    int last = bh * bw - 1;
    int scanlast = (bh - 1) * width + bw - 1;
    ey -= bh;
    ex -= bw;
    char dir = 0; //0-left; 1-down; 2-right; 3-up
    int layer = 0;
    bool ul = false, ur = false, dl = false, dr = false;
    Loop: if (target[cy*width+cx].color == bpx->color) {
        x = cx;
        y = cy;
        return true;
    }
    if (cx == sx && cy == sy) ul = true;
    if (cx == ex && cy == sy) ur = true;
    if (cx == sx && cy == ey) dl = true;
    if (cx == ex && cy == ey) dr = true;
    if (ul && ur && dl && dr) {
        return false;
    }
    switch (dir) {
        case 0:
            if (cx == x + 1 + layer) {
                layer++;
                dir = 1;
                break;
            } else if (cx == ex && cx != x + layer) {
                goto SkipLoop;
            }
            break;
        case 1:
            if (cy == y + layer) {
                dir = 2;
                break;
            } else if (cy == ey) {
                goto SkipLoop;
            }
            break;
        case 2:
            if (cx == x - layer) {
                dir = 3;
                break;
            } else if (cx == sx) {
                goto SkipLoop;
            }
            break;
        case 3:
            if (cy == y - layer) {
                dir = 0;
                break;
            } else if (cy == sy) {
                goto SkipLoop;
            }
            break;
    }
    switch (dir) {
        case 0: cx++; break;
        case 1: cy++; break;
        case 2: cx--; break;
        case 3: cy--; break;
    }
    goto Loop;
    SkipLoop: if (dir == 3) dir = 0; else dir++;
    switch (dir) { //Its been incremented
        case 1:
            if (dr) {
                goto SkipLoop;
            } else {
                cx = ex;
                cy = y + layer;
            }
            break;
        case 2:
            if (dl) {
                goto SkipLoop;
            } else {
                cx = x - layer;
                cy = ey;
            }
            break;
        case 3:
            if (ul) {
                goto SkipLoop;
            } else {
                cx = sx;
                cy = y - layer;
            }
            break;
        case 0:
            if (ur) {
                layer++;
                goto SkipLoop;
            } else {
                layer++;
                cx = x + layer;
                cy = sy;
            }
            break;
    }
    if (dir == 3) dir = 0; else dir++;
    goto Loop;
}

