#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <windows.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	HDC  hdcMemDC;
	SIZE screen_size;
}SCREEN;

void
init_screen(SCREEN *, HWND);          // 初始化SCREEN实例

void
screen_caption(HWND, SCREEN *);      // 屏幕截取，将截取的图像存入 全局变量hdcMemDc 中

void
screen_draw(HDC, SCREEN);            // 画出 全局变量hdcMemDc 中存放的屏幕图像

#ifdef __cplusplus
}
#endif
#endif
