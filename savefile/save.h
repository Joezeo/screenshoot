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
