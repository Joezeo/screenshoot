#include "brush.h"

void
init_brush(BRUSH *brush) {

	assert(brush != NULL);

	brush->pen_color = nocolor;

}

void
change_menu_checked(BRUSH *brush, PENCOLOR color, UINT menu_id, HMENU hmenu) {

	assert(brush != NULL);
	assert(hmenu != NULL);

	if (brush->pen_color == nocolor) {

		brush->pen_color = color;

		CheckMenuItem(hmenu, menu_id, MF_CHECKED);

		return;

	}

	if (color == brush->pen_color) {

		brush->pen_color = nocolor;

		CheckMenuItem(hmenu, menu_id, MF_UNCHECKED);

		return;

	}

	int tmp_id;

	switch (brush->pen_color) {
	case red:

		tmp_id = 40013;

		break;

	case blue:

		tmp_id = 40014;

		break;

	case green:

		tmp_id = 40015;

		break;

	}

	if (color == nocolor) {

		CheckMenuItem(hmenu, tmp_id, MF_UNCHECKED);

		brush->pen_color = nocolor;

		return;

	}

	CheckMenuItem(hmenu, tmp_id, MF_UNCHECKED);

	CheckMenuItem(hmenu, menu_id, MF_CHECKED);

	brush->pen_color = color;

}

void
brush_picture() {

}