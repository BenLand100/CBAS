#include "DebugWnd.h"
#include "Bitmap.h"
#include "Main.h"

#include <iostream>
using namespace std;

long  DebugProc(HWND hwnd, unsigned int Message, unsigned int wParam, long lParam) {
    DebugWindow* debug = (DebugWindow*) lParam;
    switch(Message) {
        case WM_CREATE:
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_PAINT: {
            PAINTSTRUCT paint;
            HDC dc = BeginPaint(hwnd, &paint);
            //FillRect(dc, &paint.rcPaint, (HBRUSH)GetStockObject(BLACK_BRUSH));
            EndPaint(hwnd, &paint);               
        }
        
    }
    return DefWindowProc(hwnd, Message, wParam, lParam);
}

DebugWindow::DebugWindow(int width, int height) {
    WNDCLASSEX wndclass;
    memset(&wndclass, 0, sizeof(WNDCLASSEX));
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.lpfnWndProc = DebugProc;
    wndclass.hCursor = LoadCursor(0, IDC_ARROW);
    wndclass.lpszClassName = "CBAS_DEBUG_BOX";
    wndclass.hIconSm = 0;
    RegisterClassEx(&wndclass);
    
    RECT size;
    size.top = size.left = 0;
    size.right = width;
    size.bottom = height;
    AdjustWindowRectEx(&size, WS_OVERLAPPEDWINDOW, true, WS_EX_OVERLAPPEDWINDOW);
    CreateWindowData data = {WS_EX_OVERLAPPEDWINDOW, "CBAS_DEBUG_BOX", "DebugBox", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, size.right - size.left, size.bottom - size.top, 0, 0, 0, (void*)this, &hwnd};
    SendMessage(staticInfo->messageGlobalHWND,WM_COMMAND,CREATE_WINDOW,reinterpret_cast<long>(&data));
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);
    //AttachThreadInput(GetCurrentThreadId(),messageLoopID,true);
}

DebugWindow::~DebugWindow() {
    DestroyWindow(hwnd);
}

HDC DebugWindow::getHDC() {
    return GetDC(hwnd);
}

void DebugWindow::freeHDC(HDC dc) {
    ReleaseDC(hwnd,dc);
}

HWND DebugWindow::getHWND() {
    return hwnd;
}

