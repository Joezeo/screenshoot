#include "save.h"

void
init_save_file(OPENFILENAME *sfile, HWND hwnd, HINSTANCE hInst) {

	TCHAR				strFilenames[MAX_PATH];

	assert(sfile != NULL);

	sfile->lStructSize = sizeof(OPENFILENAME);

	sfile->hwndOwner = hwnd;

	sfile->hInstance = hInst;

	sfile->lpstrFilter = TEXT("*.PNG;*.JPG;*.BMP");

	sfile->nFilterIndex = 1;

	sfile->lpstrFile = strFilenames; 

	sfile->nMaxFile = sizeof(strFilenames);

	sfile->lpstrTitle = TEXT("Áí´æÎª");

	sfile->Flags = OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

	sfile->lpstrDefExt = TEXT("png");

}