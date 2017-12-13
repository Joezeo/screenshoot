/**********************************************
               Editor:Joezeo			                       
          E-mail:joezeo@outlook.com                  
            Date:2017/12/6/18/31     
**********************************************/
#include "main.h"
#include "resource.h"
#include "screen.h"


#define		WNDWIDTH				555
#define		WNDHEIGHT				100


HINSTANCE			hInst;
TCHAR				szWndClassName[]	 =		"FrameWin";
TCHAR				szScreenClassName[]	 =		"ScreenWin";


int WINAPI 
WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance, 
    LPSTR	  lpCmdLine,
	int		  nShowCmd) {

	HACCEL			hAccel;

	HWND			hwnd, screen_hwnd;

	MSG				msg;

	WNDCLASS		wndclass;


	wndclass.style			=		CS_HREDRAW | CS_VREDRAW;

	wndclass.lpfnWndProc	=		WndProc;

	wndclass.cbClsExtra		=		0;

	wndclass.cbWndExtra		=		0;

	wndclass.hInstance		=		hInstance;

	wndclass.hIcon			=	    LoadIcon(NULL, IDI_APPLICATION);

	wndclass.hCursor		=		LoadCursor(NULL, IDC_ARROW);

	wndclass.hbrBackground	=		(HBRUSH)GetStockObject(WHITE_BRUSH);

	wndclass.lpszMenuName	=		"MyMenu";

	wndclass.lpszClassName  =		szWndClassName;


	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, "×¢²áÊ§°Ü", "´íÎó", MB_ICONERROR);
		return 0;
	}


	registe_sreenshoot_window(hInstance);


	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU));


	hAccel = LoadAccelerators(hInstance, szWndClassName);


	hwnd = CreateWindow(
		szWndClassName,		//windows class name
		"½ØÍ¼¹¤¾ß",			//windows caption	
		WS_OVERLAPPEDWINDOW,//windows style		È«ÆÁÎÞ°´Å¥£º WS_POPUP
		CW_USEDEFAULT,		//intial x position
		CW_USEDEFAULT,		//intial y position
		WNDWIDTH,			//intial x size
		WNDHEIGHT,			//intial y size
		NULL,				//parent wnidow handle
		hMenu,				// window menu handle
		hInstance,			//program instance handle
		NULL);				//creation paramenter


	screen_hwnd = GetWindow(hwnd, GW_CHILD);


	ShowWindow(hwnd, nShowCmd); // È«ÆÁ»¯£º SW_MAXIMIZE

	UpdateWindow(hwnd);


	while (GetMessage(&msg, NULL, 0, 0)) {
		if (!TranslateMDISysAccel(screen_hwnd, &msg) &&
			!TranslateAccelerator(hwnd, hAccel, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}


void
registe_sreenshoot_window(HINSTANCE hInstance) {


	WNDCLASS			wndclass;

	wndclass.style			=		CS_HREDRAW | CS_VREDRAW;

	wndclass.lpfnWndProc	=		ScreenProc;

	wndclass.cbClsExtra		=		0;

	wndclass.cbWndExtra		=		sizeof(HANDLE);

	wndclass.hInstance		=		hInstance;

	wndclass.hIcon			=		LoadIcon(NULL, IDI_APPLICATION);

	wndclass.hCursor		=		LoadCursor(NULL, IDC_ARROW);

	wndclass.hbrBackground	=		(HBRUSH)GetStockObject(WHITE_BRUSH);

	wndclass.lpszMenuName	=		NULL;

	wndclass.lpszClassName	=		szScreenClassName;


	if (!RegisterClass(&wndclass)) {

		MessageBox(NULL, "×¢²áÊ§°Ü", "´íÎó", MB_ICONERROR);

		return 0;
	}

}


void
show_screenshoot_window(HWND hwnd) {

	ShowWindow(hwnd, SW_MAXIMIZE);

	UpdateWindow(hwnd);

}


LRESULT CALLBACK 
WndProc(HWND hwnd, UINT message, WPARAM wparam,LPARAM lparam) {

	HDC							hdc;

	PAINTSTRUCT					ps;

	RECT						rect;

	static HWND					ChildWnd;

	switch (message) {
	case WM_CREATE: 

		ChildWnd = CreateWindow(szScreenClassName, TEXT("Child Demo"),
			WS_POPUP,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			hwnd, NULL, hInst, NULL);

		return 0;
	

	case WM_MENUSELECT: 

		switch (LOWORD(wparam)) {

		case IDABORT:

			show_screenshoot_window(ChildWnd);

			break;

		case ID_40003:

			SendMessage(hwnd, WM_DESTROY, 0, 0);

			break;

		}
		return 0;
	

	case WM_PAINT: 

		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);

		SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));

		DrawText(hdc, "µã»÷ÐÂ½¨¿ªÊ¼½ØÍ¼~", -1, &rect, DT_LEFT);

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
	HDC					 hdc;
	PAINTSTRUCT			 ps;
	RECT				 rect;

	switch (message) {

	case WM_PAINT:

		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);

		screen_caption(hdc);

		EndPaint(hwnd, &ps);

		return 0;


	case WM_KEYDOWN:

		switch (wparam) {

		case VK_ESCAPE:

			SendMessage(hwnd, WM_DESTROY, 0, 0);

			break;

		}

		return 0;


	case WM_DESTROY:

		PostQuitMessage(0);

		return 0;

	}

	return DefWindowProc(hwnd, message, wparam, lparam);

}
