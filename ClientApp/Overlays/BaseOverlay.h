#ifndef BASE_OVERLAY_H
#define BASE_OVERLAY_H

#ifndef OVERLAYS_H
#include "../Parameters.h"
#include "OverlayComponents.h"
#endif

/*
	Overlays have the following characteristics:
		- Created on an as needed basis
		- Override all other client UI actions
		- 
*/

class BaseOverlay :
	public Parameters
{      
public:
	virtual ~BaseOverlay();

	// checks if p is in pRc
	BOOL contains(const POINT& p);

	// user actions

	virtual void MouseMove(const WPARAM& wparam, const POINT& p) = 0;
	virtual void LDown(const WPARAM& wparam, const POINT& p) = 0;
	virtual void LUp(const WPARAM& wparam, const POINT& p) = 0;

	// displays the overlay to the screen
	virtual void display();

	// return pRc->left;
	LONG getLeft();
	// return pRc->top;
	LONG getTop();
	// return pRc->right;
	LONG getRight();
	// return pRc->bottom;
	LONG getBottom();

protected:
	BaseOverlay();
	BaseOverlay(const RECT& rc);
	BaseOverlay(BaseOverlay* pParent);
	BaseOverlay(const RECT& rc, BaseOverlay* pParent);

	// bounding rectangle
	PRECT pRc;

	// checks if the overlay is active
	// returns TRUE if active, FALSE if not
	BOOL update(const POINT& p);

	// adjusts pRc such that it is contained within the client region of the window.
	// If the overlay is unable to fit,
	// the top left of the overlay is fixed to the top left of the client region
	BOOL fitToClient();

private:
	// Overlay's parent overlay, NULL => no parent
	BaseOverlay* pParent;
};

#endif
