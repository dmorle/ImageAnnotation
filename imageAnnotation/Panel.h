#ifndef PANEL_H
#define PANEL_H

#include <windows.h>
#include <windowsx.h>
#include <windef.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include <vector>
#include "Parameters.h"

class Panel
{
public:
	virtual ~Panel();

	// determines if p is in this->rect
	BOOL contains(const POINT& p);

	// determines if the panel if contained within its parent
	BOOL isValid();

	// determines if p is on the border of the panel
	// this function will only work if the paint is contained within the panel
	BOOL onBorder(const POINT& p);

	virtual void MouseMove(const WPARAM& wparam, const POINT& p) = 0;
	virtual void LDown(const WPARAM& wparam, const POINT& p) = 0;
	virtual void LUp(const WPARAM& wparam, const POINT& p) = 0;

	// resizes the panel to the given dimensions
	virtual void resizeX(LONG left, LONG right) = 0;
	virtual void resizeY(LONG top, LONG bottom) = 0;

	// translates the panel along the given dimension
	void transX(LONG dx);
	void transY(LONG dy);

	// displays the panel
	virtual void display() = 0;

	// getter for the components of the containing rectangle
	LONG getLeft();
	LONG getTop();
	LONG getRight();
	LONG getBottom();

	// getters for the minimum dimensions
	LONG getMinWidth();
	LONG getMinHeight();

	// gets the maliability of the panel
	virtual BYTE getPanelMaliability() = 0;

protected:
	// copies the contents of pThis
	Panel(Panel* pThis, PRECT npRc);

	// the panel which contains "this"
	// if NULL, there is no parent component
	Panel* pParent;

	// bounding box for the panel in local coordinates
	PRECT pRc;

	// Maliability of the panel
	// Defines which panel will be deformed before others
	BYTE pMal;

	// the minimum dimensions of the panel
	LONG minWidth;
	LONG minHeight;

	// gets the coordinates of the rectangle in global coordinates
	// initializes npRc with the global coordinates
	void getGlobalRect(PRECT npRc);
};

#endif