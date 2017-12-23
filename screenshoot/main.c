/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.23 / 21：35
+
-             修改时间：2017.12.23 / 21：35
+
-             文件名称：main.c
+
-             功能：main模块的源文件，main模块函数声明。
+                  main模块主要包括程序的主入口，以及程序逻辑控制，消息队列处理等。
-
+
*/
#include "main.h"


CAPTURE				cap;
HINSTANCE			hInst;
TCHAR				szWndClassName[]	= "FrameWin";
TCHAR				szScreenClassName[]	= "ScreenWin";
TCHAR				szSaveClassName[]	= "SaveWin";
extern TCHAR		strFilename[MAX_PATH];


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
		MessageBox(NULL, "注册失败", "错误", MB_ICONERROR);
		return 0;
	}


	registe_sreenshoot_window(hInstance);

	registe_save_window(hInstance);


	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU));


	hwnd = CreateWindow(
		szWndClassName,                         // windows class name
		"截图工具",                              // windows caption	
		WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX
		^ WS_THICKFRAME,                        // windows style
		CW_USEDEFAULT,                          // intial x position
		CW_USEDEFAULT,                          // intial y position
		WNDWIDTH,                               // intial x size
		WNDHEIGHT,                              // intial y size
		NULL,                                   // parent wnidow handle
		hMenu,                                  // window menu handle
		hInstance,                              // program instance handle
		NULL);                                  // creation paramenter


	ShowWindow(hwnd, nShowCmd); // 全屏化： SW_MAXIMIZE

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

		MessageBox(NULL, "注册失败", "错误", MB_ICONERROR);

		return;
	}

}


void
registe_save_window(HINSTANCE hInstance) {

	WNDCLASS			wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	wndclass.lpfnWndProc = SaveProc;

	wndclass.cbClsExtra = 0;

	wndclass.cbWndExtra = sizeof(HANDLE);

	wndclass.hInstance = hInstance;

	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SAVEICON));

	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);

	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	wndclass.lpszMenuName = "SaveMenu";

	wndclass.lpszClassName = szSaveClassName;


	if (!RegisterClass(&wndclass)) {

		MessageBox(NULL, "注册失败", "错误", MB_ICONERROR);

		return;
	}

}


void
create_screenshot_window(HWND *hwnd, HWND phwnd) {

	*hwnd = CreateWindow(szScreenClassName, TEXT("Child Demo"),
		WS_POPUP,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		phwnd, NULL, hInst, NULL);

}


void
create_save_window(HWND *hwnd) {

	HMENU hmenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENUSAVE));

	*hwnd = CreateWindow(szSaveClassName, TEXT("保存截图"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, SAVEWIDTH, SAVEHEIGHT,
		NULL, hmenu, hInst, NULL);

}


void
show_screenshot_window(HWND hwnd) {

	ShowWindow(hwnd, SW_MAXIMIZE);

	UpdateWindow(hwnd);

}


void
show_save_window(HWND hwnd, CAPTURE cap) {

	RECT				rect;
	SIZE				client_size;

	GetClientRect(hwnd, &rect);

	client_size.cx = rect.right - rect.left;
	client_size.cy = rect.bottom - rect.top;

	if (((cap.picSize).cx >= client_size.cx - 200) || ((cap.picSize).cy >= client_size.cy - 200)) {

		ShowWindow(hwnd, SW_MAXIMIZE);

	} else {

		ShowWindow(hwnd, SW_SHOWNORMAL);

	}

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

		create_screenshot_window(&ChildWnd, hwnd);

		return 0;
	

	case WM_MENUSELECT: 

		switch (LOWORD(wparam)) {

		case IDABORT:

			ShowWindow(hwnd, SW_HIDE);

			// 当点击了"新建"按钮，向ScreenShot窗口传递WM_CAPTION消息，截取桌面图像，保存于hdcMemDc中
			SendMessage(ChildWnd, WM_CAPTION, 0, 0);

			show_screenshot_window(ChildWnd);

			break;

		case ID_40001:

			SendMessage(hwnd, WM_CLOSE, 0, 0);

			break;

		}
		return 0;


	case WM_SHOW:

		ShowWindow(hwnd, SW_SHOWNORMAL);

		return 0;
	

	case WM_PAINT: 

		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);

		SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));

		DrawText(hdc, "点击新建开始截图~（截图过程中按ESC取消截图）", -1, &rect, DT_LEFT);

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
	HWND							fhwnd;
	POINT							mPos;
	PAINTSTRUCT                     ps;
	static HWND						phwnd;
	static HWND						SaveWnd;
	static SELECTBOX				selectbox;
	static SCREEN					screen;

	switch (message) {

	case WM_CREATE:

		phwnd = GetParent(hwnd);

		init_screen(&screen, hwnd);

		init_capture(&cap);

		init_selectbox(&selectbox);

		create_save_window(&SaveWnd);

		return 0;


	case WM_CAPTION:

		screen_caption(hwnd, &screen);

		return 0;


	case WM_LBUTTONDOWN:

		mPos.x = LOWORD(lparam);

		mPos.y = HIWORD(lparam);

		(cap.pos).x = LOWORD(lparam);

		(cap.pos).y = HIWORD(lparam);

		capture_image(&cap, hwnd, SaveWnd);

		(selectbox.cnt)++;

		draw_selectbox(&selectbox, hwnd, mPos, screen);

		if (cap.status) {

			cap.status = FALSE;

			ShowWindow(hwnd, SW_HIDE);

			// 当capture_image截图完毕，显示SaveWin窗口
			show_save_window(SaveWnd, cap);

		}
		return 0;


	case WM_MOUSEMOVE:

		mPos.x = LOWORD(lparam);

		mPos.y = HIWORD(lparam);

		draw_selectbox(&selectbox, hwnd, mPos, screen);

		return 0;


	case WM_PAINT:

		hdc = BeginPaint(hwnd, &ps);

		screen_draw(hdc, screen);

		EndPaint(hwnd, &ps);

		return 0;


	case WM_KEYDOWN:

		switch (wparam) {

		case VK_ESCAPE:

			// 如果用户在截图界面还没开始截图，点击ESC退出截图
			if (selectbox.set_sta == FALSE) {

				init_capture(&cap);

				init_selectbox(&selectbox);

				ShowWindow(hwnd, SW_HIDE);

				SendMessage(phwnd, WM_SHOW, 0, 0);

			} 
			// 如果用户在截图界面已经开始开始截图，点击ESC重新选择
			else {

				init_capture(&cap);

				init_selectbox(&selectbox);

				hdc = GetDC(hwnd);

				BitBlt(hdc, 0, 0,
					screen.screen_size.cx, screen.screen_size.cy,
					screen.hdcMemDC,
					0, 0, SRCCOPY);

				ReleaseDC(hwnd, hdc);

			}

			

			break;

		}

		return 0;


	case WM_RECAP:

		init_selectbox(&selectbox);

		init_capture(&cap);

		fhwnd = FindWindow(szWndClassName, NULL);

		ShowWindow(fhwnd, SW_SHOWNORMAL);

		return 0;


	case WM_DESTROY:

		PostQuitMessage(0);

		return 0;


	}

	return DefWindowProc(hwnd, message, wparam, lparam);

}


LRESULT CALLBACK
SaveProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {

	HDC							hdc;
	HWND						phwnd;	
	POINT						mPos;
	PAINTSTRUCT					ps;
	static HMENU				hMenu;
	static HMENU				subMenu;
	static BRUSH				brush;
	static OPENFILENAME			sFile;

	switch (message) {

	case WM_CREATE:

		hMenu = GetMenu(hwnd);

		subMenu = GetSubMenu(hMenu, 4);

		init_brush(&brush);

		return 0;
		

	case WM_PAINT:

		hdc = BeginPaint(hwnd, &ps);

		draw_image(&cap, hdc, hwnd);

		EndPaint(hwnd, &ps);

		return 0;


	case WM_LBUTTONDOWN:

		mPos.x = LOWORD(lparam);
		mPos.y = HIWORD(lparam);

		brush_picture(mPos, &cap, &brush, hwnd);

		return 0;


	case WM_LBUTTONUP:

		brush.pre_point.x = 0;
		brush.pre_point.y = 0;

		return 0;


	case WM_MOUSEMOVE:

		//如果鼠标左键被持续按下
		if (MK_LBUTTON & wparam) {

			mPos.x = LOWORD(lparam);
			mPos.y = HIWORD(lparam);

			brush_picture(mPos, &cap, &brush, hwnd);

		}


	case WM_COMMAND:

		if (lparam == 0) {

			switch (LOWORD(wparam)) {

			case ID_SAVE:

				init_save_file(&sFile, hwnd, hInst);

				/*如果用户指定的文件名，并单击确定按钮，返回值不为零。
				指向的 OPENFILENAME 结构的 lpstrFile 成员在缓冲区中包含完整的路径和文件名称。*/
				if (GetSaveFileName(&sFile)) { 

					MessageBox(NULL, sFile.lpstrFile, TEXT("保存到"), 0);

					HBITMAP hbmp;

					hdc = GetDC(hwnd);

					hbmp = GetSrcBit(cap.memDc, cap.picSize.cx, cap.picSize.cy);

					save_bmp_file(hbmp, sFile.lpstrFile, hdc);

					ReleaseDC(hwnd, hdc);

					DeleteObject(hbmp);

				}

				break;


			case ID_RECAP:

				change_menu_checked(&brush, nocolor, 0, subMenu);

				phwnd = FindWindow(szScreenClassName, NULL);

				SendMessage(phwnd, WM_RECAP, 0, 0);

				ShowWindow(hwnd, SW_HIDE);

				break;

			case ID_REDPEN:

				change_menu_checked(&brush, red, ID_REDPEN, subMenu);

				break;

			case ID_BLUEPEN:

				change_menu_checked(&brush, blue, ID_BLUEPEN, subMenu);

				break;

			case ID_GREENPEN:

				change_menu_checked(&brush, green, ID_GREENPEN, subMenu);

				break;

			}

		}

		return 0;
		
	case WM_DESTROY:

		PostQuitMessage(0);

		return 0;

	}

	return DefWindowProc(hwnd, message, wparam, lparam);

}
