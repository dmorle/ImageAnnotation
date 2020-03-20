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
	BaseOverlay(const RECT& pRc);

	virtual ~BaseOverlay();

	// checks if p is in pRc
	BOOL contains(const POINT& p);

	// user actions

	virtual void MouseMove(const WPARAM& wparam, const POINT& p);
	virtual void LDown(const WPARAM& wparam, const POINT& p);
	virtual void LUp(const WPARAM& wparam, const POINT& p);

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

	// only to be used during overlay construction
	// adds any overlay component overlay to the overlay instance
	void addComponent(OLCMP::BaseComponent* pCmp);

protected:
	// bounding rectangle
	PRECT pRc;

	// contains all of the overlays components
	std::vector<OLCMP::BaseComponent*> cmp;

private:
	// Overlay's parent overlay, NULL => no parent
	BaseOverlay* pParent;

	// checks if the overlay is active
	// returns TRUE if active, FALSE if not
	BOOL update(const POINT& p);
};

#endif