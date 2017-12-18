#include "save.h"

TCHAR				strFilename[MAX_PATH];

// 初始化保存文件对话框
void
init_save_file(OPENFILENAME *sfile, HWND hwnd, HINSTANCE hInst) {

	assert(sfile != NULL);

	sfile->lStructSize = sizeof(OPENFILENAME);

	sfile->hwndOwner = hwnd;

	sfile->hInstance = hInst;

	sfile->lpstrFilter = TEXT("*.PNG;*.JPG;*.BMP");

	sfile->nFilterIndex = 1;

	sfile->lpstrFile = strFilename; 

	sfile->nMaxFile = sizeof(strFilename);

	sfile->lpstrTitle = TEXT("另存为");

	sfile->Flags = OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

	sfile->lpstrDefExt = TEXT("bmp");

}


// 从capture实例的memDc中取出HBITMAP
HBITMAP 
GetSrcBit(HDC hDC, DWORD BitWidth, DWORD BitHeight)
{

	//cap.memDc 是与SaveWin窗口hwnd相兼容的hdc

	HDC hBufDC;

	HBITMAP hBitmap, hBitTemp;

	//创建设备上下文(HDC)
	hBufDC = CreateCompatibleDC(hDC);

	//创建HBITMAP
	hBitmap = CreateCompatibleBitmap(hDC, BitWidth, BitHeight);

	hBitTemp = (HBITMAP)SelectObject(hBufDC, hBitmap);

	//得到位图缓冲区
	StretchBlt(hBufDC, 0, 0, BitWidth, BitHeight,
		hDC, 0, 0, BitWidth, BitHeight, SRCCOPY);

	//得到最终的位图信息
	hBitmap = (HBITMAP)SelectObject(hBufDC, hBitTemp);

	//释放内存
	DeleteObject(hBitTemp);

	DeleteDC(hBufDC);

	return hBitmap;

}


// 保存 bmp 图片
void
save_bmp_file(HBITMAP hbmScreen, LPSTR strFilename, HDC hdc) {

	BITMAP bmpScreen;

	GetObject(hbmScreen, sizeof(BITMAP), &bmpScreen);

	BITMAPFILEHEADER   bmfHeader;
	BITMAPINFOHEADER   bi;

	bi.biSize = sizeof(BITMAPINFOHEADER);
	bi.biWidth = bmpScreen.bmWidth;
	bi.biHeight = bmpScreen.bmHeight;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	DWORD dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

	// Starting with 32-bit Windows, GlobalAlloc and LocalAlloc are implemented as wrapper functions that 
	// call HeapAlloc using a handle to the process's default heap. Therefore, GlobalAlloc and LocalAlloc 
	// have greater overhead than HeapAlloc.
	HANDLE hDIB = GlobalAlloc(GHND, dwBmpSize);
	char *lpbitmap = (char *)GlobalLock(hDIB);

	// Gets the "bits" from the bitmap and copies them into a buffer 
	// which is pointed to by lpbitmap.
	GetDIBits(hdc, hbmScreen, 0,
		(UINT)bmpScreen.bmHeight,
		lpbitmap,
		(BITMAPINFO *)&bi, DIB_RGB_COLORS);

	// A file is created, this is where we will save the screen capture.
	HANDLE hFile = CreateFile(strFilename,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	// Add the size of the headers to the size of the bitmap to get the total file size
	DWORD dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	//Offset to where the actual bitmap bits start.
	bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

	//Size of the file
	bmfHeader.bfSize = dwSizeofDIB;

	//bfType must always be BM for Bitmaps
	bmfHeader.bfType = 0x4D42; //BM   

	DWORD dwBytesWritten = 0;

	WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
	WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);

	//Unlock and Free the DIB from the heap
	GlobalUnlock(hDIB);
	GlobalFree(hDIB);

	//Close the handle for the file that was created
	CloseHandle(hFile);

	//Clean up

}