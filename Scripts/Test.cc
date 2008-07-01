#include "Main.h"
#include "DebugWnd.h"
#include "Bitmap.h"
#include <windows.h>

int scriptmain() {
     DebugWindow debug(500,500);
     Bitmap bmp(34,27, "beNrNlu0RgyAMhp3FFboCs7BCV2CFrsAszOIKNhKJAUP8AHvN8cPD833uTUJknv8qhhiP69tlPcHi+nz1YtX0+7Lg8/A6oMyhAwVBMiusiPa8gb7AYvrtCBS3w5b/BZT0nXPTNLVQqO7oBR6AY9km4gB0z07RV0ixA8tPIiILTe1ZCpryT1WgunAKBndX+FozUEHYfK2sz7L2FKH3UldcooisrS5cP77lJ4iSIFLeKaqs/OBn+sVACDLFxQCEMUZj2az9BP36WIAdE+Mkq6DIQy8IvQey3vvzLN4MpT5mUrIzjiMoE+iQpelHRM0OB+m+hIld6Kt5Q9ahr4xS0bfqRCWW6AvtbJTr+md8wXNm566+7kuw06Bf84WlocmG/6COF5tsOP/qknYtvt6fqKw=");
     HDC dc = debug.getHDC();
     BitBlt(dc, 50, 50, 50, 50, bmp.getDC(), 0, 0, SRCCOPY);
     debug.freeHDC(dc);
     return 0;
}
