/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.23 / 21：43
+
-             修改时间：2017.12.23 / 21：43
+
-             文件名称：screen.h
+
-             功能：screen模块的头文件，包括包含文件，宏定义，screen模块函数的前向声明。
+                  screen模块的主要功能为截取桌面图像，画出桌面图像
-
+
*/
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
screen_caption(HWND, SCREEN *);      // 屏幕截取，将截取的图像存入 SCREEN结构体的hdcMemDc 中

void
screen_draw(HDC, SCREEN);            // 画出 全局变量hdcMemDc 中存放的屏幕图像

#ifdef __cplusplus
}
#endif
#endif
