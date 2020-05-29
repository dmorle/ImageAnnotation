#ifndef OVERLAY_H
#define OVERLAY_H

#include "../Parameters.h"

class BaseOverlay :
	public Parameters
{      
public:
	BaseOverlay(const RECT& pRc, LONG minWidth, LONG minHeight);

	// checks if p is in pRc
	BOOL contains(const POINT& p);

	// user actions
	virtual void MouseMove(const WPARAM& wparam, const POINT& p);
	virtual void LDown(const WPARAM& wparam, const POINT& p);
	virtual void LUp(const WPARAM& wparam, const POINT& p);

	// displays the overlay to the screen
	virtual void display() = 0;

protected:
	// bounding rectangle
	PRECT pRc;

	// whether or not 'this' is to be deleted
	BOOL active;

	// min width for the overlay
	LONG minWidth;

	// min height for the overlay
	LONG minHeight;

private:
	static USHORT currId;
	USHORT id;

	BOOL equals(const BaseOverlay* pB);

	void update(const POINT& p);
};

#endif