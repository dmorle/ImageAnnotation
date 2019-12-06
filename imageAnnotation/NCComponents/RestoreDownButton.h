#ifndef RESTOREDOWNBUTTON_H
#define RESTOREDOWNBUTTON_H

#include "NCButton.h"

class RestoreDownButton :
	public NCButton
{
public:
	RestoreDownButton(
		COLORREF back,
		COLORREF back_passive,
		COLORREF back_active,
		COLORREF back_pressed,
		COLORREF comp,
		COLORREF comp_passive,
		COLORREF comp_active,
		COLORREF comp_pressed,
		void (*onClick)(),
		RECT rc
	);
	RestoreDownButton(
		COLORREF back_passive,
		COLORREF back_active,
		COLORREF back_pressed,
		COLORREF comp_passive,
		COLORREF comp_active,
		COLORREF comp_pressed,
		void (*onClick)(),
		RECT rc
	);

	void translate(LONG dx, LONG dy);

	void display(HDC hdc);
};

#endif