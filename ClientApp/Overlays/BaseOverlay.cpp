#include "BaseOverlay.h"



BaseOverlay::BaseOverlay()
{
	this->pRc = NULL;
	this->pParent = NULL;
}

BaseOverlay::BaseOverlay(const RECT& rc)
{
	this->pRc = new RECT(rc);
	this->pParent = NULL;
}

BaseOverlay::BaseOverlay(BaseOverlay* pParent)
{
	this->pRc = NULL;
	this->pParent = pParent;
}

BaseOverlay::BaseOverlay(const RECT& rc, BaseOverlay* pParent)
{
	this->pRc = new RECT(rc);
	this->pParent = pParent;
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

BOOL BaseOverlay::fitToClient()
{
	RECT rc;
	if (!GetClientRect(hwnd, &rc))
		return FALSE;

	// handling horizontal orientation
	if (pRc->right - pRc->left > rc.right)
	{
		pRc->right -= pRc->left;
		pRc->left = 0;
	}
	else if (pRc->right > rc.right)
	{
		pRc->left -= pRc->right - rc.right;
		pRc->right = rc.right;
	}
	else if (pRc->left < 0)
	{
		pRc->right -= pRc->left;
		pRc->left = 0;
	}

	// handling vertical orientation
	if (pRc->bottom - pRc->top > rc.bottom)
	{
		pRc->bottom -= pRc->top;
		pRc->top = 0;
	}
	else if (pRc->bottom > rc.bottom)
	{
		pRc->top -= pRc->bottom - rc.bottom;
		pRc->bottom = rc.bottom;
	}
	else if (pRc->top < 0)
	{
		pRc->bottom -= pRc->top;
		pRc->top = 0;
	}

	return TRUE;
}
