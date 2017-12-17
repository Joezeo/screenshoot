#include "save.h"

TCHAR				strFilename[MAX_PATH];

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

	sfile->lpstrTitle = TEXT("Áí´æÎª");

	sfile->Flags = OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

	sfile->lpstrDefExt = TEXT("png");

}