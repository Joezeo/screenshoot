/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.23 / 21：46
+
-             修改时间：2017.12.23 / 21：46
+
-             文件名称：screen.c
+
-             功能：screen模块的源文件，包括screen模块函数的定义。
+                  screen模块的主要功能为截取桌面图像，画出桌面图像
-
+
*/
#include "screen.h"

// 初始化SCREEN实例
void
init_screen(SCREEN *screen, HWND hwnd) {

	assert(screen != NULL);
	assert(hwnd != NULL);

	HDC hdcWindow = GetDC(hwnd);

	// Create a compatible DC which is used in a BitBlt from the window DC
	screen->hdcMemDC = CreateCompatibleDC(hdcWindow);

	if (!(screen->hdcMemDC))
	{
		MessageBox(hwnd, "CreateCompatibleDC has failed", "Failed", MB_OK);
	}

	(screen->screen_size).cx = GetSystemMetrics(SM_CXSCREEN);

	(screen->screen_size).cy = GetSystemMetrics(SM_CYSCREEN);

}


// 屏幕截取，将截取的图像存入 SCREEN结构体的hdcMemDc 中
void 
screen_caption(HWND hWnd, SCREEN *screen){

	assert(hWnd != NULL);
	assert(screen != NULL);

	HDC hdcScreen;
	HDC hdcWindow;
	HBITMAP hbmScreen = NULL;

	// Retrieve the handle to a display device context for the client 
	// area of the window. 
	hdcScreen = GetDC(NULL); // GetDC(NULL)表示整个屏幕的dc
	hdcWindow = GetDC(hWnd); // 创建当前窗口的hdc

	// Create a compatible bitmap from the Window DC
	hbmScreen = CreateCompatibleBitmap(hdcWindow, (screen->screen_size).cx, (screen->screen_size).cy);

	if (!hbmScreen)
	{
		MessageBox(hWnd, "CreateCompatibleBitmap Failed", "Failed", MB_OK);
		goto done;
	}

	// Select the compatible bitmap into the compatible memory DC.
	SelectObject(screen->hdcMemDC, hbmScreen);

	// Bit block transfer into our compatible memory DC.
	if (!BitBlt(screen->hdcMemDC,
		0, 0,
		(screen->screen_size).cx, (screen->screen_size).cy,
		hdcScreen,
		0, 0,
		SRCCOPY))
	{
		MessageBox(hWnd, "BitBlt has failed", "Failed", MB_OK);
		goto done;
	}

	//Clean up
done:
	DeleteObject(hbmScreen);
	ReleaseDC(NULL, hdcScreen);
	ReleaseDC(hWnd, hdcWindow);

}


// 画出 全局变量hdcMemDc 中存放的屏幕图像
void
screen_draw(HDC hdc, SCREEN screen) {

	assert(hdc != NULL);

	BitBlt(hdc,
		0, 0,
		(screen.screen_size).cx, (screen.screen_size).cy,
		screen.hdcMemDC,
		0, 0,
		SRCCOPY);
}


