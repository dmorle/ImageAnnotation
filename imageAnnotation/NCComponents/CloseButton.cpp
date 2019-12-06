#include "CloseButton.h"



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

	LONG height = rc.bottom - rc.top;
	LONG width = rc.right - rc.left;
	LONG size = min(width, height) / 6;
	LONG xMid = (rc.left + rc.right) / 2;
	LONG yMid = (rc.top + rc.bottom) / 2;

	HPEN hpen = CreatePen(PS_SOLID, 1, pAssets->getComp(state));
	SelectObject(hdc, hpen);
	
	MoveToEx(hdc, xMid - size, yMid - size, NULL);
	LineTo(hdc, xMid + size + 1, yMid + size + 1);

	MoveToEx(hdc, xMid - size, yMid + size, NULL);
	LineTo(hdc, xMid + size + 1, yMid - size - 1);
}