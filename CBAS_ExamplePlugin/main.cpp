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

/**
 *Make as many other object files or header files as you need, and only copy
 *the header containing the #warning links [library] and your function 
 *definitions to the CBAS/Includes folder to keep clutter down.
 */

#include "ExamplePlugin.h"
#include <windows.h>

double divide(double a, double b) {
    return a / b;
}

int factorial(int a) {
    int res = 1;
    for (int i = 1; i <= a; i++) {
        res *= i;
    }
    return res;
}

void message(char* title, char* message) {
    MessageBox(0,message,title,MB_OK);
}

