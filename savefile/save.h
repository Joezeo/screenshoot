#ifndef __SAVE_H__
#define __SAVE_H__

#include <windows.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

void
init_save_file(OPENFILENAME *, HWND, HINSTANCE);          // 初始化保存文件对话框

#ifdef __cplusplus
}
#endif
#endif
