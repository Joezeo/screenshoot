/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.23 / 21：52
+
-             修改时间：2017.12.23 / 21：52
+
-             文件名称：save.h
+
-             功能：save模块的头文件，包括包含文件，宏定义，save模块函数的前向声明。
+                  save模块的主要功能是在截图完毕，画刷画图完毕后，保存图片。
-
+
*/
#ifndef __SAVE_H__
#define __SAVE_H__

#include <windows.h>
#include <assert.h>
#include "../capturer/capturer.h"

#ifdef __cplusplus
extern "C" {
#endif

void
init_save_file(OPENFILENAME *, HWND, HINSTANCE);                 // 初始化保存文件对话框

HBITMAP
GetSrcBit(HDC hDC, DWORD BitWidth, DWORD BitHeight);             // 从capture实例的memDc中取出HBITMAP

void
save_bmp_file(HBITMAP, LPSTR, HDC);                              // 保存 bmp 图片

#ifdef __cplusplus
}
#endif
#endif
