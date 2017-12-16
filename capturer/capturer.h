#ifndef __CAPTURER_H__
#define __CAPTURER_H__

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {

	UINT	bCnt;	// 记数鼠标点击次数
	BOOL	status;	// 是否截图成功
	RECT	rect;	// 截取图像的矩形区域
	POINT	pos;	// 点击时鼠标坐标，以及截图后图片在客户区的坐标
	HDC		memDc;	// 存储截图信息的memDc
	SIZE	picSize;// 截取图片的大小

}CAPTURE;

void
init_capture(CAPTURE *);					// 接口函数，初始化 CAPTURE 实例

void
capture_image(CAPTURE *, HWND, HWND);		// 接口函数，选择图片，保存图片于 CAPTURE 实例的memDc中

void
draw_image(CAPTURE *, HDC, HWND);			// 接口函数，画出 capture 实例 memDc 中存放的图像

static void
select_image(CAPTURE *);					// 静态函数，选择图片

static void
store_image(CAPTURE *, HWND, HWND);			// 静态函数，保存图片于 CAPTURE 实例的memDc中

#ifdef __cplusplus
}
#endif
#endif
