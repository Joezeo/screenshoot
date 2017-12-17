#ifndef __BOX_H__
#define __BOX_H__

#include <windows.h>
#include <assert.h>
#include "../screen/screen.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	POINT sta_pos; // 选择框起始点
	BOOL  set_sta; // 是否设置初始点
	UINT  cnt;	   // 鼠标点击次数
}SELECTBOX;


void
init_selectbox(SELECTBOX *);                              // 接口函数，初始化 SELECTBOX 实例

void
draw_selectbox(SELECTBOX *, HWND, POINT, SCREEN);         // 接口函数，画选择框，主控制函数

static void
redraw_image(HWND, SCREEN);                               // 每次画矩形选择框之前都重绘桌面图像

static void
draw_box(SELECTBOX *, HWND, POINT);                       // 静态函数，画出选择框

#ifdef __cplusplus
}
#endif

#endif
