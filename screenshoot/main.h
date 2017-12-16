#ifndef __MAIN_H__
#define __MAIN_H__

#include "resource.h"
#include "../screen/screen.h"
#include "../capturer/capturer.h"
#include "../brush/brush.h"
#pragma comment(lib,"msimg32.lib")
#pragma comment(lib,"winmm.lib")

#ifdef __cplusplus
extern "C"{
#endif

#define		WNDWIDTH				555				// 主窗口宽
#define		WNDHEIGHT				100				// 主窗口高
#define		SAVEWIDTH				1000			// Save窗口宽
#define		SAVEHEIGHT				750				// Save窗口高

#define		WM_CAPTION				(WM_USER + 1)	// CAPTION 事件，当用户点击“新建”时触发
#define		WM_SHOW					(WM_USER + 2)	// SHOW    事件，当用户在截图界面点ESC时触发
#define		WM_RECAP				(WM_USER + 3)	// RECAP   事件，保存界面点击“重新截图”时，在 ScreenProc 中触发

void
registe_sreenshoot_window(HINSTANCE);

void
registe_save_window(HINSTANCE);

void
create_screenshot_window(HWND *, HWND);

void
create_save_window(HWND *);

void
show_screenshot_window(HWND);

void
show_save_window(HWND, CAPTURE);

LRESULT CALLBACK
WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK
ScreenProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK
SaveProc(HWND, UINT, WPARAM, LPARAM);


#ifdef __cplusplus
}
#endif
#endif