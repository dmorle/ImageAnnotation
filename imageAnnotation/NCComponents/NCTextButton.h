#ifndef NCTEXTBUTTON_H
#define NCTEXTBUTTON_H

#include "NCButton.h"
//#include <gdiplusheaders.h>
//#include <gdiplusbrush.h>
//#include <gdipluscolor.h>
//#include <gdiplusgraphics.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

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
		const PWCHAR msg,
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
		const PWCHAR msg,
		UINT fontSize
	);

	void display(HDC hdc);

protected:
	Font font;
	PWCHAR msg;

	SolidBrush* getCompBrush();
};

#endif