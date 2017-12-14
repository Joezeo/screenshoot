#include "screen.h"

RECT					rcClient;
HDC						memDc;

void
screen_caption(HWND hwnd) {

	static HBITMAP      hbmScreen;


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

}

void
draw_caption(HDC hdc) {

	SetStretchBltMode(hdc, HALFTONE);

	StretchBlt(hdc,
		0, 0,
		rcClient.right, rcClient.bottom,
		memDc,
		0, 0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		SRCCOPY);

}

