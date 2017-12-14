#include "screen.h"

RECT					rcClient;

HDC *
screen_caption(HWND hwnd){

	static HBITMAP      hbmScreen;
	static HDC			memDc;

	HDC screenDc = GetDC(NULL);
	HDC windowDc = GetDC(hwnd);

	memDc = CreateCompatibleDC(screenDc);
	
	GetClientRect(hwnd, &rcClient);

	hbmScreen = CreateCompatibleBitmap(screenDc, rcClient.left - rcClient.right, rcClient.bottom - rcClient.top);

	SelectObject(memDc, hbmScreen);

	SetStretchBltMode(memDc, HALFTONE);

	StretchBlt(memDc,
		0, 0,
		rcClient.right, rcClient.bottom,
		screenDc,
		0, 0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		SRCCOPY);

	return &memDc;
}

void
draw_caption(HDC memDC, HDC hdc) {

	SetStretchBltMode(hdc, HALFTONE);

	StretchBlt(hdc,
		0, 0,
		rcClient.right, rcClient.bottom,
		memDC,
		0, 0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		SRCCOPY);

	DeleteDC(memDC);
}

