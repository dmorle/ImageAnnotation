#include "Panel.h"
#include <cassert>



Panel::Panel()
{
	this->pParent = NULL;
	this->pRc = NULL;
}

Panel::Panel(Panel* pThis, PRECT npRc)
{
	this->pParent = pThis->pParent;
	this->pRc = npRc;
	this->pMal = pThis->pMal;
	this->minHeight = pThis->minHeight;
	this->minWidth = pThis->minWidth;
}

Panel::~Panel()
{
	if (pRc)
		delete pRc;
}

BOOL Panel::contains(const POINT& p, BOOL localCrds)
{
	if (localCrds) {
		if (
			p.x >= pRc->left && p.x < pRc->right &&
			p.y >= pRc->top && p.y < pRc->bottom
			)
			return TRUE;

		return FALSE;
	}
	else {
		POINT np(p);
		getLocalPoint(&np);

		if (
			np.x >= pRc->left && np.x < pRc->right &&
			np.y >= pRc->top && np.y < pRc->bottom
			)
			return TRUE;

		return FALSE;
	}
}

BOOL Panel::isValid()
{
	if (!pParent)
		return TRUE;

	if (
		pRc->left < pRc->right &&
		pRc->top < pRc->bottom &&
		pRc->left >= 0 &&
		pRc->top >= 0 &&
		pRc->right <= pParent->pRc->right - pParent->pRc->left &&
		pRc->bottom <= pParent->pRc->bottom - pParent->pRc->top
		)
		return TRUE;

	return FALSE;
}

BOOL Panel::onBorder(const POINT& p)
{
	if (
		p.x < pRc->left + edgeSpace ||	// check left
		p.y < pRc->top + edgeSpace ||   // check top
		p.x > pRc->right - edgeSpace || // check right
		p.y > pRc->bottom - edgeSpace   // check bottom
		)
		return TRUE;

	return FALSE;
}

void Panel::transX(LONG dx)
{
	pRc->left += dx;
	pRc->right += dx;
}

void Panel::transY(LONG dy)
{
	pRc->top += dy;
	pRc->bottom += dy;
}

LONG Panel::getLeft()
{
	return pRc->left;
}

LONG Panel::getTop()
{
	return pRc->top;
}

LONG Panel::getRight()
{
	return pRc->right;
}

LONG Panel::getBottom()
{
	return pRc->bottom;
}

LONG Panel::getMinWidth()
{
	return minWidth;
}

LONG Panel::getMinHeight()
{
	return minHeight;
}

void Panel::getGlobalRect(PRECT npRc)
{
	assert(npRc);

	npRc->left += pRc->left;
	npRc->top += pRc->top;
	npRc->right += pRc->left;
	npRc->bottom += pRc->top;

	if (pParent)
		pParent->getGlobalRect(npRc);
}

void Panel::getGlobalPoint(PPOINT npP)
{
	assert(npP);

	npP->x += pRc->left;
	npP->y += pRc->top;

	if (pParent)
		pParent->getGlobalPoint(npP);
}

void Panel::getLocalRect(PRECT npRc)
{
	assert(npRc);

	npRc->left -= pRc->left;
	npRc->top -= pRc->top;
	npRc->right -= pRc->left;
	npRc->bottom -= pRc->top;

	if (pParent)
		pParent->getLocalRect(npRc);
}

void Panel::getLocalPoint(PPOINT npP)
{
	assert(npP);

	npP->x -= pRc->left;
	npP->y -= pRc->top;

	if (pParent)
		pParent->getLocalPoint(npP);
}