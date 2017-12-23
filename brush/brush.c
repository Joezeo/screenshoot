/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.23 / 21：48
+
-             修改时间：2017.12.23 / 21：48
+
-             文件名称：brush.c
+
-             功能：brush模块的源文件，包括brush模块函数的定义。
+                  brush模块的主要功能为画刷：选择画笔，画笔作图。
-
+
*/
#include "brush.h"

/* 
			接口函数
*/

// 接口函数，初始化 BRUSH 实例
void
init_brush(BRUSH *brush) {

	assert(brush != NULL);

	brush->pen_color = nocolor;

	(brush->pre_point).x = 0;
	(brush->pre_point).y = 0;

}


// 接口函数，改变菜单栏的 check 属性的状态
void
change_menu_checked(BRUSH *brush, PENCOLOR color, UINT menu_id, HMENU hmenu) {

	assert(brush != NULL);
	assert(hmenu != NULL);

	if (brush->pen_color == nocolor) {

		brush->pen_color = color;

		CheckMenuItem(hmenu, menu_id, MF_CHECKED);

		return;

	}

	if (color == brush->pen_color) {

		brush->pen_color = nocolor;

		CheckMenuItem(hmenu, menu_id, MF_UNCHECKED);

		return;

	}

	int tmp_id;

	switch (brush->pen_color) {
	case red:

		tmp_id = 40013;

		break;

	case blue:

		tmp_id = 40014;

		break;

	case green:

		tmp_id = 40015;

		break;

	}

	if (color == nocolor) {

		CheckMenuItem(hmenu, tmp_id, MF_UNCHECKED);

		brush->pen_color = nocolor;

		return;

	}

	CheckMenuItem(hmenu, tmp_id, MF_UNCHECKED);

	CheckMenuItem(hmenu, menu_id, MF_CHECKED);

	brush->pen_color = color;

}


// 接口函数，判断鼠标位置，画笔画图，更新 capture 实例的 memDc
void
brush_picture(POINT mPos, CAPTURE *cap, BRUSH *brush, HWND hwnd) {

	assert(cap != NULL);
	assert(brush != NULL);

	if (!check_mouse_pos(mPos, *cap)) {

		return;

	}

	if (check_brush_color(*brush)) {

		return;

	}

	if (check_brush_prePoint(brush, mPos)) {

		return;

	}

	draw_brush_picture(hwnd, brush, mPos);

	change_capture_memdc(cap, hwnd);

}



/* 
			静态函数 
*/

// 静态函数，判断鼠标位置是否在图片上
static BOOL
check_mouse_pos(POINT mPos, CAPTURE cap) {

	RECT rect;

	rect.left = cap.pos.x;

	rect.top = cap.pos.y;

	rect.right = rect.left + cap.picSize.cx;

	rect.bottom = rect.top + cap.picSize.cy;

	return PtInRect(&rect, mPos);

}


// 静态函数，检查画笔的颜色是否为 nocolor
static BOOL
check_brush_color(BRUSH brush) {

	if (brush.pen_color == nocolor) {

		return TRUE;

	}

	return FALSE;

}


// 静态函数，检查画笔的 pre_point 坐标
static BOOL
check_brush_prePoint(BRUSH *brush, POINT mPos) {

	if (((brush->pre_point).x == 0) || ((brush->pre_point).y) == 0) {

		(brush->pre_point).x = mPos.x;
		(brush->pre_point).y = mPos.y;

		return TRUE;

	}

	return FALSE;

}


// 静态函数，画笔画图
static void
draw_brush_picture(HWND hwnd, BRUSH *brush, POINT mPos) {

	COLORREF color;
	HDC      hdc;

	hdc = GetDC(hwnd);

	switch (brush->pen_color) {

	case red:
		color = RGB(255, 0, 0);
		break;

	case green:
		color = RGB(0, 255, 0);
		break;

	case blue:
		color = RGB(0, 0, 255);
		break;

	}

	HPEN hpen = CreatePen(PS_SOLID, 5, color);

	SelectObject(hdc, hpen);

	MoveToEx(hdc, (brush->pre_point).x, (brush->pre_point).y, NULL);

	LineTo(hdc, mPos.x, mPos.y);

	brush->pre_point = mPos;

	ReleaseDC(hwnd, hdc);

}


// 静态函数，画笔画图的同时改变 capture 实例中的memdc
static void
change_capture_memdc(CAPTURE *cap, HWND hwnd) {

	HDC windowDc = GetDC(hwnd);

	HBITMAP hBmp = CreateCompatibleBitmap(windowDc, (cap->picSize).cx, (cap->picSize).cy);

	SelectObject((cap->memDc), hBmp);

	if (!BitBlt(cap->memDc, 0, 0,
		(cap->picSize).cx, (cap->picSize).cy,
		windowDc,
		(cap->pos).x, (cap->pos).y,
		SRCCOPY)) {

		MessageBox(NULL, "画图失败", "错误", MB_OK);

	}

}
