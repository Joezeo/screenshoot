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
	POINT	pos;	// 点击时鼠标坐标
	HDC		memDc;	// 存储截图信息的memDc
}CAPTURE;

void
init_capture(CAPTURE *);		// 初始化 capture 实例

void
capture_image(CAPTURE *, HWND);				// 接口函数，返回一个存放有截图信息的memhdc

static void
select_image(CAPTURE *);					// 静态函数，选择图片

static void
store_image(CAPTURE *, HWND);				// 静态函数，保存图片

#ifdef __cplusplus
}
#endif
#endif
