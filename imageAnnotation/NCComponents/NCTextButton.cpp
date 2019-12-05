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
	const PWCHAR msg,
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
), font(L"Arial", fontSize)
{
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
	const PWCHAR msg,
	UINT fontSize = 12
) : NCButton(
	back_passive,
	back_active,
	back_pressed,
	comp_passive,
	comp_active,
	comp_pressed,
	onClick
), font(L"Arial", fontSize)
{
	this->rc = rc;
	this->msg = msg;
}

void NCTextButton::display(HDC hdc)
{
	SolidBrush* psbr = getCompBrush();
	assert(psbr != NULL);

	Graphics g(hdc);
	Status st = g.DrawString(msg, -1, &font, PointF(rc.left, rc.top), psbr);
	assert(st == Ok);

	delete psbr;
}

SolidBrush* NCTextButton::getCompBrush()
{
	Color c;
	c.SetFromCOLORREF(pAssets->getComp(state));
	return new SolidBrush(c);
}
