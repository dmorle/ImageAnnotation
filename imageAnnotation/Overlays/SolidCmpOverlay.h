#ifndef SOLID_CMP_OVERLAY_H
#define SOLID_CMP_OVERLAY_H

#ifndef OVERLAYS_H
#include "SolidOverlay.h"
#include "CmpOverlay.h"
#endif

class SolidCmpOverlay : 
	public SolidOverlay,
	public CmpOverlay
{
	SolidCmpOverlay(const RECT& rc);

	virtual ~SolidCmpOverlay();

	// user actions

	virtual void MouseMove(const WPARAM& wparam, const POINT& p) override = 0;
	virtual void LDown(const WPARAM& wparam, const POINT& p) override = 0;
	virtual void LUp(const WPARAM& wparam, const POINT& p) override = 0;

	// displays the overlay to the screen
	virtual void display() override;
};

#endif
