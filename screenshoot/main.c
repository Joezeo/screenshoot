/**********************************************
               Editor:Joezeo			                       
          E-mail:joezeo@outlook.com                  
            Date:2017/12/6/18/31     
**********************************************/
#include "main.h"
#include "resource.h"
#include "screen.h"

extern RECT			rcClient;
HINSTANCE			hInst;
TCHAR				szWndClassName[]	= "FrameWin";
TCHAR				szScreenClassName[]	= "ScreenWin";
HDC					hdcScreen;

int WINAPI 
WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance, 
	LPSTR	  lpCmdLine,
	int		  nShowCmd) {

	HWND                    hwnd;

	MSG                     msg;

	WNDCLASS                wndclass;

	hInst = hInstance;

	wndclass.style              = CS_HREDRAW | CS_VREDRAW;

	wndclass.lpfnWndProc        = WndProc;

	wndclass.cbClsExtra         = 0;

	wndclass.cbWndExtra         = 0;

	wndclass.hInstance          = hInstance;

	wndclass.hIcon              = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BIGICON));

	wndclass.hCursor            = LoadCursor(NULL, IDC_ARROW);

	wndclass.hbrBackground      = (HBRUSH)GetStockObject(WHITE_BRUSH);

	wndclass.lpszMenuName       = "MyMenu";

	wndclass.lpszClassName      = szWndClassName;


	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, "ע��ʧ��", "����", MB_ICONERROR);
		return 0;
	}


	registe_sreenshoot_window(hInstance);


	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU));


	hwnd = CreateWindow(
		szWndClassName,                         //windows class name
		"��ͼ����",                              //windows caption	
		WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX
		^ WS_THICKFRAME,                        //windows style
		CW_USEDEFAULT,                          //intial x position
		CW_USEDEFAULT,                          //intial y position
		WNDWIDTH,                               //intial x size
		WNDHEIGHT,                              //intial y size
		NULL,                                   //parent wnidow handle
		hMenu,                                  // window menu handle
		hInstance,                              //program instance handle
		NULL);                                  //creation paramenter


	ShowWindow(hwnd, nShowCmd); // ȫ������ SW_MAXIMIZE

	UpdateWindow(hwnd);


	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);

		DispatchMessage(&msg);

	}

	return msg.wParam;
}


void
registe_sreenshoot_window(HINSTANCE hInstance) {


	WNDCLASS			wndclass;

	wndclass.style              = CS_HREDRAW | CS_VREDRAW;

	wndclass.lpfnWndProc        = ScreenProc;

	wndclass.cbClsExtra         = 0;

	wndclass.cbWndExtra         = sizeof(HANDLE);

	wndclass.hInstance          = hInstance;

	wndclass.hIcon              = LoadIcon(NULL, IDI_APPLICATION);

	wndclass.hCursor            = LoadCursor(NULL, IDC_ARROW);

	wndclass.hbrBackground      = (HBRUSH)GetStockObject(WHITE_BRUSH);

	wndclass.lpszMenuName       = NULL;

	wndclass.lpszClassName      = szScreenClassName;


	if (!RegisterClass(&wndclass)) {

		MessageBox(NULL, "ע��ʧ��", "����", MB_ICONERROR);

		return;
	}

}


void
create_screenshoot_window(HWND *hwnd, HWND phwnd) {

	*hwnd = CreateWindow(szScreenClassName, TEXT("Child Demo"),
		WS_POPUP,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		phwnd, NULL, hInst, NULL);

}


void
show_screenshoot_window(HWND hwnd) {

	ShowWindow(hwnd, SW_MAXIMIZE);

	UpdateWindow(hwnd);

}


LRESULT CALLBACK 
WndProc(HWND hwnd, UINT message, WPARAM wparam,LPARAM lparam) {

	HDC                         hdc;

	PAINTSTRUCT                 ps;

	RECT                        rect;

	static HWND                 ChildWnd;

	switch (message) {
	case WM_CREATE: 

		create_screenshoot_window(&ChildWnd, hwnd);

		return 0;
	

	case WM_MENUSELECT: 

		switch (LOWORD(wparam)) {

		case IDABORT:

			show_screenshoot_window(ChildWnd);

			break;

		case ID_40001:

			SendMessage(hwnd, WM_CLOSE, 0, 0);

			break;

		}
		return 0;
	

	case WM_PAINT: 

		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);

		SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));

		DrawText(hdc, "����½���ʼ��ͼ~����ͼ�����а�ESCȡ����ͼ��", -1, &rect, DT_LEFT);

		EndPaint(hwnd, &ps);

		return 0;
	

	case WM_DESTROY: 

		PostQuitMessage(0);

		return 0;
	
	}


	return DefWindowProc(hwnd, message, wparam, lparam);
}


LRESULT CALLBACK
ScreenProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {

	HDC                             hdc;
	PAINTSTRUCT                     ps;
	RECT                            rect;
	static HDC						memDc;

	switch (message) {

	case WM_CREATE:

		memDc = screen_caption(hwnd);

		return 0;

	case WM_PAINT:

		hdc = BeginPaint(hwnd, &ps);

		draw_caption(hdc);

		EndPaint(hwnd, &ps);

		return 0;


	case WM_KEYDOWN:

		switch (wparam) {

		case VK_ESCAPE:

			ShowWindow(hwnd, SW_HIDE);

			break;

		}

		return 0;


	case WM_DESTROY:

		PostQuitMessage(0);

		return 0;


	}

	return DefWindowProc(hwnd, message, wparam, lparam);

}
