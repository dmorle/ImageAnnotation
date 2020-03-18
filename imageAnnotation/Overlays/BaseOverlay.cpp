#include "BaseOverlay.h"



USHORT BaseOverlay::currId = 0;

BaseOverlay::BaseOverlay(const RECT& rc)
{
	this->id = currId++;
	this->pRc = new RECT(rc);
}

BaseOverlay::~BaseOverlay()
{
	for (auto& e : cmp)
		delete e;

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

void BaseOverlay::MouseMove(const WPARAM& wparam, const POINT& p)
{
}

void BaseOverlay::LDown(const WPARAM& wparam, const POINT& p)
{
	if (!update(p))
		return;
}

void BaseOverlay::LUp(const WPARAM& wparam, const POINT& p)
{
	if (!update(p))
		return;
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

void BaseOverlay::addComponent(OLCMP::BaseComponent* pCmp)
{
	this->cmp.push_back(pCmp);
}

BOOL BaseOverlay::equals(const BaseOverlay* pB)
{
	return this->id == pB->id;
}

BOOL BaseOverlay::update(const POINT& p)
{
	if (!contains(p)) {

		// check if the widget is active, and if so, prep it for deletion
		for (int i = 0; i < inActiveOverlays.size(); i++)
			if (this->equals(inActiveOverlays[i])) {
				// prep activeOverlays[i] for deletion
				inActiveOverlays.erase(inActiveOverlays.begin() + i);
				delete this;
				return FALSE;
			}
	}
	return TRUE;
}