#include<windows.h>
#include"utils.h"
#include"Scene.h"
LRESULT CALLBACK RTWindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
int WINAPI WinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR lpCmdLine,
    _In_ int nShowCmd) {
    WNDCLASSEX wndclsex = {};
    wndclsex.cbClsExtra = 0;
    wndclsex.cbSize = sizeof(WNDCLASSEX);
    wndclsex.cbWndExtra = 0;
    wndclsex.hbrBackground = NULL;
    wndclsex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclsex.hIcon = NULL;
    wndclsex.hIconSm = NULL;
    wndclsex.hInstance = hInstance;
    wndclsex.lpszClassName = L"RTWindow";
    wndclsex.lpszMenuName = NULL;
    wndclsex.style = CS_VREDRAW | CS_HREDRAW;
    wndclsex.lpfnWndProc = RTWindowProc;
    ATOM atom = RegisterClassEx(&wndclsex);
    if (atom == 0) {
        MessageBox(NULL, L"Register Window Failed", L"Error", MB_OK);
        return -1;
    }
    RECT rect = {0,0,1280,720};
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
    int windowWidth = rect.right - rect.left;
    int windowtHeight = rect.bottom - rect.top;
    HWND hwnd = CreateWindowEx(NULL,L"RTWindow",L"Ray Tracing Window",WS_OVERLAPPEDWINDOW,
        0,0,windowWidth,windowtHeight,NULL,NULL,hInstance,NULL);
    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    HDC dc = GetDC(hwnd);
    InitRenderableBuffer(dc, 1280, 720);
    Init(1280,720);
    MSG msg;
    while (true) {
        if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                break;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        Render();
        ASwapBuffers(dc);
    }
	return 0;
}