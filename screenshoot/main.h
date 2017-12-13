#ifndef __MAIN_H__
#define __MAIN_H__

#include <windows.h>
#pragma comment(lib,"msimg32.lib")
#pragma comment(lib,"winmm.lib")

#ifdef __cplusplus
extern "C"{
#endif

	void
		registe_sreenshoot_window(HINSTANCE);

	void
		show_screenshoot_window(HWND hwnd);

	LRESULT CALLBACK
		WndProc(HWND, UINT, WPARAM, LPARAM);

	LRESULT CALLBACK
		ScreenProc(HWND, UINT, WPARAM, LPARAM);

#ifdef __cplusplus
}
#endif
#endif