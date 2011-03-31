#include "ExamplePlugin.h"
#include "Main.h"

int scriptmain() {
    jout << divide(6,4) << "\n";
    jout << factorial(5) << "\n";
    message("Example","It works!");
    return 0;
}