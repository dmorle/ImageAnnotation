#include "CmpOverlay.h"



CmpOverlay::CmpOverlay() :
	BaseOverlay()
{}

CmpOverlay::CmpOverlay(const RECT& rc) : 
	BaseOverlay(rc)
{}

CmpOverlay::CmpOverlay(BaseOverlay* pParent) :
	BaseOverlay(pParent)
{}

CmpOverlay::CmpOverlay(const RECT& rc, BaseOverlay* pParent) :
	BaseOverlay(rc, pParent)
{}

CmpOverlay::~CmpOverlay()
{
	for (auto& e : cmp)
		delete e;
}

void CmpOverlay::LDown(const WPARAM& wparam, const POINT& p)
{
	for (auto& e : cmp)
		if (e->contains(p)) {
			if (e->isInteractive())
				((OLCMP::InteractiveComponent*) e)->LDown(wparam, p);
			break;
		}
}

void CmpOverlay::LUp(const WPARAM& wparam, const POINT& p)
{
	for (auto& e : cmp)
		if (e->contains(p)) {
			if (e->isInteractive())
				((OLCMP::InteractiveComponent*) e)->LUp(wparam, p);
			break;
		}
}

void CmpOverlay::MouseMove(const WPARAM& wparam, const POINT& p)
{
	for (auto& e : cmp)
		if (e->contains(p)) {
			if (e->isInteractive())
				((OLCMP::InteractiveComponent*) e)->MouseMove(wparam, p);
			break;
		}
}

void CmpOverlay::display()
{
	for (auto& e : cmp)
		e->display();
}

void CmpOverlay::addComponent(OLCMP::BaseComponent* pCmp)
{
	this->cmp.push_back(pCmp);
	pCmp->pParent = this;
}
