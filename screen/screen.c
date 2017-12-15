#include "screen.h"
HDC					hdcMemDC;
SIZE				screen_size;

void 
screen_caption(HWND hWnd){
	HDC hdcScreen;
	HDC hdcWindow;
	HBITMAP hbmScreen = NULL;

	// Retrieve the handle to a display device context for the client 
	// area of the window. 
	hdcScreen = GetDC(NULL); // GetDC(NULL)表示整个屏幕的dc
	hdcWindow = GetDC(hWnd); // 创建当前窗口的hdc

	screen_size.cx = GetSystemMetrics(SM_CXSCREEN);
	screen_size.cy = GetSystemMetrics(SM_CYSCREEN);

	// Create a compatible DC which is used in a BitBlt from the window DC
	hdcMemDC = CreateCompatibleDC(hdcWindow);

	if (!hdcMemDC)
	{
		MessageBox(hWnd, "CreateCompatibleDC has failed", "Failed", MB_OK);
		goto done;
	}

	// Create a compatible bitmap from the Window DC
	hbmScreen = CreateCompatibleBitmap(hdcWindow, screen_size.cx, screen_size.cy);

	if (!hbmScreen)
	{
		MessageBox(hWnd, "CreateCompatibleBitmap Failed", "Failed", MB_OK);
		goto done;
	}

	// Select the compatible bitmap into the compatible memory DC.
	SelectObject(hdcMemDC, hbmScreen);

	// Bit block transfer into our compatible memory DC.
	if (!BitBlt(hdcMemDC,
		0, 0,
		screen_size.cx, screen_size.cy,
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

void
screen_draw(HDC hdc) {
	BitBlt(hdc,
		0, 0,
		screen_size.cx, screen_size.cy,
		hdcMemDC,
		0, 0,
		SRCCOPY);
}


