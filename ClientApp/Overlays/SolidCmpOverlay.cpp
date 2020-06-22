#include "SolidCmpOverlay.h"



SolidCmpOverlay::SolidCmpOverlay() :
	BaseOverlay(),
	SolidOverlay(),
	CmpOverlay()
{}

SolidCmpOverlay::SolidCmpOverlay(const RECT& rc) :
	BaseOverlay(rc),
	SolidOverlay(rc),
	CmpOverlay(rc)
{}

SolidCmpOverlay::SolidCmpOverlay(BaseOverlay* pParent) :
	BaseOverlay(pParent),
	SolidOverlay(pParent),
	CmpOverlay(pParent)
{}

SolidCmpOverlay::SolidCmpOverlay(const RECT& rc, BaseOverlay* pParent) :
	BaseOverlay(rc, pParent),
	SolidOverlay(rc, pParent),
	CmpOverlay(rc, pParent)
{}

SolidCmpOverlay::~SolidCmpOverlay()
{}

void SolidCmpOverlay::LDown(const WPARAM& wparam, const POINT& p)
{
	CmpOverlay::LDown(wparam, p);
}

void SolidCmpOverlay::LUp(const WPARAM& wparam, const POINT& p)
{
	CmpOverlay::LUp(wparam, p);
}

void SolidCmpOverlay::MouseMove(const WPARAM& wparam, const POINT& p)
{
	CmpOverlay::MouseMove(wparam, p);
}

void SolidCmpOverlay::display()
{
	// display parent
	BaseOverlay::display();
	// color the overlay
	SolidOverlay::display();
	// display all of the components
	CmpOverlay::display();
}
