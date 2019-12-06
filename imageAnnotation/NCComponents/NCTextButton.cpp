#include "NCTextButton.h"
#include <assert.h>



NCTextButton::NCTextButton(
	COLORREF back,
	COLORREF back_passive,
	COLORREF back_active,
	COLORREF back_pressed,
	COLORREF comp,
	COLORREF comp_passive,
	COLORREF comp_active,
	COLORREF comp_pressed,
	void(*onClick)(),
	RECT rc,
	const LPCSTR msg,
	UINT fontSize = 12
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
	hfont = CreateFont(fontSize, 0, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	this->rc = rc;
	this->msg = msg;
}

NCTextButton::NCTextButton(
	COLORREF back_passive,
	COLORREF back_active,
	COLORREF back_pressed,
	COLORREF comp_passive,
	COLORREF comp_active,
	COLORREF comp_pressed,
	void(*onClick)(),
	RECT rc,
	const LPCSTR msg,
	UINT fontSize = 12
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
	hfont = CreateFont(fontSize, 0, 0, 0, FW_DONTCARE, FALSE, TRUE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	this->rc = rc;
	this->msg = msg;
}

void NCTextButton::display(HDC hdc)
{
	NCButton::display(hdc);

	SetTextColor(hdc, pAssets->getComp(state));
	SelectObject(hdc, hfont);
	DrawText(hdc, msg, -1, &rc, DT_VCENTER | DT_CENTER);
}