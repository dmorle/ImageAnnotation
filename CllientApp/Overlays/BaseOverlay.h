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
	BaseOverlay(const RECT& rc);

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
	// bounding rectangle
	PRECT pRc;

	// checks if the overlay is active
	// returns TRUE if active, FALSE if not
	BOOL update(const POINT& p);

private:
	// Overlay's parent overlay, NULL => no parent
	BaseOverlay* pParent;
};

#endif
