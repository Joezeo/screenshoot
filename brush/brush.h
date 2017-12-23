/*
+
-             作者：Joezeo < joezeo@outlook.com >
+
-             创建时间：2017.12.23 / 21：47
+
-             修改时间：2017.12.23 / 21：47
+
-             文件名称：brush.h
+
-             功能：brush模块的头文件，包括包含文件，宏定义，brush模块函数的前向声明。
+                  brush模块的主要功能为画刷：选择画笔，画笔作图。
-
+
*/
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
	POINT    pre_point; // 前一个点坐标
}BRUSH;

void
init_brush(BRUSH *);                                 // 接口函数，初始化 BRUSH 实例

void
change_menu_checked(BRUSH *, PENCOLOR, UINT, HMENU); // 接口函数，改变菜单栏的 check 属性的状态

void
brush_picture(POINT, CAPTURE *, BRUSH *, HWND);		 // 接口函数，判断鼠标位置，画笔画图

static BOOL
check_mouse_pos(POINT, CAPTURE);					 // 静态函数，判断鼠标位置是否在图片上

static BOOL
check_brush_color(BRUSH);                            // 静态函数，检查画笔的颜色是否为 nocolor

static BOOL
check_brush_prePoint(BRUSH *, POINT);                // 静态函数，检查画笔的 pre_point 坐标

static void
draw_brush_picture(HWND, BRUSH *, POINT);            // 静态函数，画笔画图

static void
change_capture_memdc(CAPTURE *, HWND);               // 静态函数，画笔画图的同时改变 capture 实例中的memdc


#ifdef __cplusplus
}
#endif
#endif
