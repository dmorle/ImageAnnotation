#include "WidgetPanel.h"
#include <cassert>



WidgetPanel::WidgetPanel(Panel* pParent, PRECT npRc, BYTE pMal, LONG minWidth, LONG minHeight)
	: Panel(pParent, npRc, pMal, minWidth, minHeight)
{}

WidgetPanel::~WidgetPanel()
{
	for (auto& e : cmp)
		delete e;
}

WidgetPanel* WidgetPanel::operator>>(WCMP::BaseComponent* npCmp)
{
	cmp.push_back(npCmp);
	return this;
}

void WidgetPanel::MouseMove(const WPARAM& wparam, const POINT& p)
{
	POINT np(p);
	pParent->getLocalPoint(&np);
	// np is now in pParent coordinates

	if (!contains(np, TRUE) || onBorder(np, TRUE)) {
		pAP = pParent;
		pParent->MouseMove(wparam, p);
		return;
	}

	// passing action to components
	np.x -= pRc->left;
	np.y -= pRc->top;
	// np is now in local coordinates

	for (auto& e : cmp) {
		if (e->contains(np))
			e->MouseMove(np);
		else
			e->MouseLeave();
	}
}

void WidgetPanel::LDown(const WPARAM& wparam, const POINT& p)
{
	// passing action to components
	POINT np(p);
	getLocalPoint(&np);

	for (auto& e : cmp)
		if (e->contains(np))
			e->LDown(np);
}

void WidgetPanel::LUp(const WPARAM& wparam, const POINT& p)
{
	// passing action to components
	POINT np(p);
	getLocalPoint(&np);

	for (auto& e : cmp)
		if (e->contains(np))
			e->LUp(np);
}

void WidgetPanel::resizeX(LONG left, LONG right)
{
	pRc->left = left;
	pRc->right = right;

	for (auto& e : cmp)
		e->resize();
}

void WidgetPanel::resizeY(LONG top, LONG bottom)
{
	pRc->top = top;
	pRc->bottom = bottom;

	for (auto& e : cmp)
		e->resize();
}

void WidgetPanel::widgetEdit(WidgetPanel* pWidget)
{
	// this function should never be called
	assert(0);
}

void WidgetPanel::display()
{
	if (!fullPaint) {
		RECT r(*pRc);
		pParent->getGlobalRect(&r);
		pRenderTarget->FillRectangle(TOD2DRECTF(r), pBrushes->background);
	}

	RECT rc
	{
		pRc->left + edgeSpace,
		pRc->top + edgeSpace,
		pRc->right - edgeSpace,
		pRc->bottom - edgeSpace
	};
	pParent->getGlobalRect(&rc);

	pRenderTarget->FillRectangle(TOD2DRECTF(rc), pBrushes->widgetBack);

	for (int i = 0; i < 3; i++)
		pRenderTarget->DrawLine(
			{ (FLOAT)(rc.right - 2 * edgeSpace * (i + 2)), (FLOAT)(rc.bottom - 2 * edgeSpace) },
			{ (FLOAT)(rc.right - 2 * edgeSpace), (FLOAT)(rc.bottom - 2 * edgeSpace * (i + 2)) },
			pBrushes->active
		);

	/*
		Displaying the widget components for a standard widget
	*/
	for (auto& e : cmp)
		e->display(pRenderTarget);
}

BYTE WidgetPanel::getPanelMaliability()
{
	return pMal;
}