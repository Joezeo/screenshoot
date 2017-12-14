#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

HDC *
screen_caption(HWND);

void
draw_caption(HBITMAP, HDC);


#ifdef __cplusplus
}
#endif
#endif
