#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

void
screen_caption(HWND);

void
screen_draw(HDC);

#ifdef __cplusplus
}
#endif
#endif
