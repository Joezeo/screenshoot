#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>
#pragma comment(lib,"msimg32.lib")
#pragma comment(lib,"winmm.lib")

#ifdef __cplusplus
extern "C"{
#endif

#define		WNDWIDTH				555
#define		WNDHEIGHT				100

#define		WM_CAPTION				(WM_USER + 1)
#define		WM_SHOW					(WM_USER + 2)

void
registe_sreenshoot_window(HINSTANCE);

void
show_screenshoot_window(HWND);

void
create_screenshoot_window(HWND *, HWND);

LRESULT CALLBACK
WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK
ScreenProc(HWND, UINT, WPARAM, LPARAM);


#ifdef __cplusplus
}
#endif
#endif