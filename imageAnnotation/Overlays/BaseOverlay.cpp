#include "BaseOverlay.h"



USHORT BaseOverlay::currId = 0;

BaseOverlay::BaseOverlay(const RECT& rc, LONG minWidth, LONG minHeight)
{
	this->id = currId++;
	this->active = TRUE;
	this->pRc = new RECT(rc);
	this->minWidth = minWidth;
	this->minHeight = minHeight;
}

BOOL BaseOverlay::contains(const POINT& p)
{
	if (
		p.x >= pRc->left && p.x < pRc->right &&
		p.y >= pRc->top && p.y < pRc->bottom
		)
		return TRUE;

	return FALSE;
}

void BaseOverlay::MouseMove(const WPARAM& wparam, const POINT& p)
{
	update(p);
}

void BaseOverlay::LDown(const WPARAM& wparam, const POINT& p)
{
	update(p);
}

void BaseOverlay::LUp(const WPARAM& wparam, const POINT& p)
{
	update(p);
}

LONG BaseOverlay::getLeft()
{
	return pRc->left;
}

LONG BaseOverlay::getTop()
{
	return pRc->top;
}

LONG BaseOverlay::getRight()
{
	return pRc->right;
}

LONG BaseOverlay::getBottom()
{
	return pRc->bottom;
}

BOOL BaseOverlay::equals(const BaseOverlay* pB)
{
	return this->id == pB->id;
}

void BaseOverlay::update(const POINT& p)
{
	if (!contains(p)) {
		active = FALSE;

		// check if the widget is active, and if so, prep it for deletion
		for (int i = 0; i < activeOverlays.size(); i++)
			if (this->equals(activeOverlays[i])) {
				// prep activeOverlays[i] for deletion
				activeOverlays.erase(activeOverlays.begin() + i);
				inActiveOverlays.push_back(this);
				return;
			}
	}
	return;
}