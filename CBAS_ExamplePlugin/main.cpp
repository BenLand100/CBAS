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

