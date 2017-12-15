#include "capturer.h"

void
init_capture(CAPTURE *cap) {

	cap->bCnt = 0;

	cap->status = FALSE;

	(cap->pos).x = 0;
	(cap->pos).y = 0;

	(cap->rect).left	= 0;
	(cap->rect).bottom	= 0;
	(cap->rect).right	= 0;
	(cap->rect).top		= 0;

	cap->memDc = NULL;

}

void
capture_image(CAPTURE *cap, HWND hwnd) {

	select_image(cap);

	if (cap->bCnt == 2) {

		store_image(cap, hwnd);

	}
		
}

static void
select_image(CAPTURE *cap) {

	(cap->bCnt)++;

	switch (cap->bCnt) {

	case 1:

		(cap->rect).left = (cap->pos).x;

		(cap->rect).top = (cap->pos).y;

		break;


	case 2:

		(cap->rect).right = (cap->pos).x;

		(cap->rect).bottom = (cap->pos).y;

		break;

	}

}

static void
store_image(CAPTURE *cap, HWND hwnd) {

	cap->bCnt = 0;

	HDC					window_dc;
	HBITMAP				window_hbmp;
	SIZE				pic_size;

	pic_size.cx = (cap->rect).left - (cap->rect).right;
	pic_size.cy = (cap->rect).bottom - (cap->rect).top;

	window_dc = GetDC(hwnd);
	window_hbmp = CreateCompatibleBitmap(window_dc, pic_size.cx, pic_size.cy);

	SelectObject(cap->memDc, window_hbmp);

	if (!BitBlt(cap->memDc, 0, 0, pic_size.cx, pic_size.cy,
		window_dc, 0, 0, SRCCOPY)) {

		cap->status = TRUE;

	}

}