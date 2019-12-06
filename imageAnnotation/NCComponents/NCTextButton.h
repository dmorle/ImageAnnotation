#ifndef NCTEXTBUTTON_H
#define NCTEXTBUTTON_H

#include "NCButton.h"

class NCTextButton :
	public NCButton
{
	NCTextButton(
		COLORREF back,
		COLORREF back_passive,
		COLORREF back_active,
		COLORREF back_pressed,
		COLORREF comp,
		COLORREF comp_passive,
		COLORREF comp_active,
		COLORREF comp_pressed,
		void (*onClick)(),
		RECT rc,
		const LPCSTR msg,
		UINT fontSize
	);
	NCTextButton(
		COLORREF back_passive,
		COLORREF back_active,
		COLORREF back_pressed,
		COLORREF comp_passive,
		COLORREF comp_active,
		COLORREF comp_pressed,
		void (*onClick)(),
		RECT rc,
		const LPCSTR msg,
		UINT fontSize
	);

	void display(HDC hdc);

protected:
	HFONT hfont;
	LPCSTR msg;
};

#endif