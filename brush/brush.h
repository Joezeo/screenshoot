#ifndef __BRUSH_H__
#define __BRUSH_H__

#include <windows.h>
#include <assert.h>
#include "../capturer/capturer.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	nocolor = 0,
	red,
	blue,
	green,
}PENCOLOR;

typedef struct {
	PENCOLOR pen_color; // 画笔颜色
}BRUSH;

void
init_brush(BRUSH *);                                 // 接口函数，初始化 BRUSH 实例

void
change_menu_checked(BRUSH *, PENCOLOR, UINT, HMENU); // 接口函数，改变菜单栏的 check 属性的状态

void
brush_picture(POINT, CAPTURE);                       // 接口函数，判断鼠标位置，画笔画图

static BOOL
check_mouse_pos(POINT, CAPTURE);					 // 静态函数，判断鼠标位置是否在图片上

#ifdef __cplusplus
}
#endif
#endif
