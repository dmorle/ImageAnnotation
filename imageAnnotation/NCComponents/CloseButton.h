#ifndef CLOSEBUTTON_H
#define CLOSEBUTTON_H

#include "NCButton.h"
class CloseButton :
	public NCButton
{
public:
	CloseButton(
		COLORREF back,
		COLORREF back_passive,
		COLORREF back_active,
		COLORREF back_pressed,
		COLORREF comp,
		COLORREF comp_passive,
		COLORREF comp_active,
		COLORREF comp_pressed,
		void (*onClick)()
	);
	CloseButton(
		COLORREF back_passive,
		COLORREF back_active,
		COLORREF back_pressed,
		COLORREF comp_passive,
		COLORREF comp_active,
		COLORREF comp_pressed,
		void (*onClick)()
	);

	void display(HDC hdc);

private:
	Pen* getCompPen();
};

#endif