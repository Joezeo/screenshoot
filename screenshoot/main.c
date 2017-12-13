/**********************************************
               Editor:Joezeo			                       
          E-mail:joezeo@outlook.com                  
            Date:2017/12/6/18/31     
**********************************************/
#include <windows.h>
#include "resource.h"
#include "screen.h"

#define WNDWIDTH 555
#define WNDHEIGHT 100
HINSTANCE hIns;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance, 
				   LPSTR	 lpCmdLine,
				   int		 nShowCmd)
{
	static char szWndClassName[] = "hellowin";
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = "MyMenu";
	wndclass.lpszClassName = szWndClassName;

	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, "注册失败", "错误", MB_ICONERROR);
		return 0;
	}
	HMENU hMenu = hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU));
	hwnd = CreateWindow(
		szWndClassName,		//windows class name
		"截图工具",			//windows caption	
		WS_OVERLAPPEDWINDOW,//windows style		全屏无按钮： WS_POPUP
		CW_USEDEFAULT,		//intial x position
		CW_USEDEFAULT,		//intial y position
		WNDWIDTH,			//intial x size
		WNDHEIGHT,			//intial y size
		NULL,				//parent wnidow handle
		hMenu,				// window menu handle
		hInstance,			//program instance handle
		NULL);				//creation paramenter

	ShowWindow(hwnd, nShowCmd); // 全屏化： SW_MAXIMIZE
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, 
							WPARAM wparam,LPARAM lparam) {
	HDC hdc;		//设备描述表句柄
	PAINTSTRUCT ps;
	RECT rect;

	switch (message) {
	case WM_CREATE:

		return 0;
	case WM_MENUSELECT:
		create_sreenshoot_window(hIns);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));
		DrawText(hdc, "点击新建开始截图~", -1, &rect, DT_LEFT);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wparam, lparam);
}
