#include "CmpOverlay.h"



CmpOverlay::CmpOverlay(const RECT& rc) :
	BaseOverlay(rc)
{}

CmpOverlay::~CmpOverlay()
{
	for (auto& e : cmp)
		delete e;
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
