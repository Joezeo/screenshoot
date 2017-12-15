#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

HWND
screen_caption(HWND hwnd);

void
draw_caption(HDC);


#ifdef __cplusplus
}
#endif
#endif
