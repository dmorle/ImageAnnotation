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
public:
	virtual ~SolidCmpOverlay();

	// user actions

	virtual void MouseMove(const WPARAM& wparam, const POINT& p) override;
	virtual void LDown(const WPARAM& wparam, const POINT& p) override;
	virtual void LUp(const WPARAM& wparam, const POINT& p) override;

	// displays the overlay to the screen
	virtual void display() override;

protected:
	SolidCmpOverlay();
	SolidCmpOverlay(const RECT& rc);
	SolidCmpOverlay(BaseOverlay* pParent);
	SolidCmpOverlay(const RECT& rc, BaseOverlay* pParent);
};

#endif
