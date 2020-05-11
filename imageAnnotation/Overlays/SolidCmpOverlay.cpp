#include "SolidCmpOverlay.h"



SolidCmpOverlay::SolidCmpOverlay(const RECT& rc) :
	SolidOverlay(rc),
	CmpOverlay(rc)
{}

SolidCmpOverlay::~SolidCmpOverlay()
{}

void SolidCmpOverlay::display()
{
	// display parent
	BaseOverlay::display();
	// color the overlay
	SolidOverlay::display();
	// display all of the components
	CmpOverlay::display();
}
