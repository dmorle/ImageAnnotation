#include "CloseButton.h"
#include <assert.h>



CloseButton::CloseButton(
	COLORREF back,
	COLORREF back_passive,
	COLORREF back_active,
	COLORREF back_pressed,
	COLORREF comp,
	COLORREF comp_passive,
	COLORREF comp_active,
	COLORREF comp_pressed,
	void(*onClick)(),
	RECT rc
) : NCButton(
	back,
	back_passive,
	back_active,
	back_pressed,
	comp,
	comp_passive,
	comp_active,
	comp_pressed,
	onClick
)
{
	this->rc = rc;
}

CloseButton::CloseButton(
	COLORREF back_passive,
	COLORREF back_active,
	COLORREF back_pressed,
	COLORREF comp_passive,
	COLORREF comp_active,
	COLORREF comp_pressed,
	void(*onClick)(),
	RECT rc
) : NCButton(
	back_passive,
	back_active,
	back_pressed,
	comp_passive,
	comp_active,
	comp_pressed,
	onClick
)
{
	this->rc = rc;
}

void CloseButton::display(HDC hdc)
{
	NCButton::display(hdc);

	Pen* ppen = getCompPen();
	assert(ppen != NULL);

	LONG height = rc.bottom - rc.top;
	LONG width = rc.right - rc.left;

	Graphics g(hdc);

	LONG size = min(width, height) / 4;
	LONG xMid = (rc.left + rc.right) / 2;
	LONG yMid = (rc.top + rc.bottom) / 2;
	Status st;

	st = g.DrawLine(ppen, xMid - size, yMid - size, xMid + size, yMid + size);
	assert(st == Ok);

	st = g.DrawLine(ppen, xMid - size, yMid + size, xMid + size, yMid - size);
	assert(st == Ok);

	delete ppen;
}

Pen* CloseButton::getCompPen()
{
	Color c;
	c.SetFromCOLORREF(pAssets->getComp(state));
	return new Pen(c);
}
