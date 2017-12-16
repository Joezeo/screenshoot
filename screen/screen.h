#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <windows.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

void
screen_caption(HWND);                // 屏幕截取，将截取的图像存入 全局变量hdcMemDc 中

void
screen_draw(HDC);                    // 画出 全局变量hdcMemDc 中存放的屏幕图像

#ifdef __cplusplus
}
#endif
#endif
