#ifndef SOLID_OVERLAY_H
#define SOLID_OVERLAY_H

#include "BaseOverlay.h"

class SolidOverlay :
	virtual public BaseOverlay
{
public:
	virtual ~SolidOverlay();

	// user actions

	virtual void MouseMove(const WPARAM& wparam, const POINT& p) override = 0;
	virtual void LDown(const WPARAM& wparam, const POINT& p) override = 0;
	virtual void LUp(const WPARAM& wparam, const POINT& p) override = 0;

	// displays the overlay to the screen
	virtual void display() override;

protected:
	SolidOverlay();
	SolidOverlay(const RECT& rc);
	SolidOverlay(BaseOverlay* pParent);
	SolidOverlay(const RECT& rc, BaseOverlay* pParent);
};

#endif
