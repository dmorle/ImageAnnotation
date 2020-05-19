#ifndef SOLID_OVERLAY_H
#define SOLID_OVERLAY_H

#include "BaseOverlay.h"

class SolidOverlay :
	public BaseOverlay
{
public:
	SolidOverlay(const RECT& rc);

	virtual ~SolidOverlay();

	// user actions

	virtual void MouseMove(const WPARAM& wparam, const POINT& p) override = 0;
	virtual void LDown(const WPARAM& wparam, const POINT& p) override = 0;
	virtual void LUp(const WPARAM& wparam, const POINT& p) override = 0;

	// displays the overlay to the screen
	virtual void display() override;
};

#endif
