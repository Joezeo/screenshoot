#ifndef __SCREEN__
#define __SCREEN__

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

HDC
screen_caption();

void
create_sreenshoot_window(HINSTANCE);

LRESULT CALLBACK 
ScreenProc(HWND, UINT, WPARAM, LPARAM);


#ifdef __cplusplus
}
#endif
#endif
