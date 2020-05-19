#include "SolidCmpOverlay.h"



SolidCmpOverlay::SolidCmpOverlay(const RECT& rc) :
	SolidOverlay(rc),
	CmpOverlay(rc)
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
