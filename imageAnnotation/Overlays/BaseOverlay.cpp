#include "BaseOverlay.h"



BaseOverlay::BaseOverlay(const RECT& rc)
{
	this->pRc = new RECT(rc);
	this->pParent = NULL;
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

void BaseOverlay::display()
{
	if (pParent)
		pParent->display();

	for (auto& e : cmp)
		e->display();
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

BOOL BaseOverlay::update(const POINT& p)
{
	if (!contains(p)) {
		pAO = this->pParent;
		delete this;
		return FALSE;
	}
	return TRUE;
}