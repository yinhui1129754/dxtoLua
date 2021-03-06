// test1.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "test1.h"


winClass * wcls = NULL;
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (wcls->hWnd == NULL || wcls->public_ismove == FALSE) {
		return CallNextHookEx(0, nCode, wParam, lParam);
	}
	switch (wParam) {
	case WM_MOUSEMOVE:
		if (wcls->public_ismove == TRUE) {
			POINT p;
			GetCursorPos(&p);
			int x = wcls->startMouse.right + (p.x - wcls->startMouse.left);
			int y = wcls->startMouse.bottom + (p.y - wcls->startMouse.top);
			wcls->moveWindow(x,y,wcls->width,wcls->height);
		}
		break;
	case WM_LBUTTONUP:
		wcls->public_ismove = FALSE;
		break;
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
};
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	if (!SUCCEEDED(CoInitializeEx(NULL,0))){
		MessageBox(NULL, "错误", "内容错误", MB_OK);
	};
    // TODO: 在此处放置代码。
	HHOOK hhk = NULL;
	wcls = new winClass(hInstance);
	wcls->Create();
	//hhk = SetWindowsHookExA(WH_MOUSE_LL, (HOOKPROC)MouseProc, GetModuleHandle(0), 0);
	wcls->loop();
	UnregisterClass(wcls->szClassName, hInstance);
	if (hhk != NULL) {
		UnhookWindowsHookEx(hhk);
	}
	CoUninitialize();
    return 0;
}

