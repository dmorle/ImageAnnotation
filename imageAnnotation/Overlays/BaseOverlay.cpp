#include "BaseOverlay.h"



BaseOverlay::BaseOverlay(const RECT& rc)
{
	this->pRc = new RECT(rc);
	this->pParent = NULL;
}

BaseOverlay::~BaseOverlay()
{
	if (pRc)
		delete pRc;
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

void BaseOverlay::display()
{
	if (pParent)
		pParent->display();
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

BOOL BaseOverlay::update(const POINT& p)
{
	if (!contains(p)) {
		pAO = this->pParent;
		delete this;
		fullPaint = TRUE;
		InvalidateRect(hwnd, NULL, FALSE);
		return FALSE;
	}
	return TRUE;
}
