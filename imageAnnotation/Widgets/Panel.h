#ifndef PANEL_H
#define PANEL_H

#ifndef WIDGETS_H
#include "../Parameters.h"
#include "WidgetComponents.h"
#endif

#include <vector>

enum class PANEL_ID {
	WIDGET_PANEL,
	CONTAINER
};

class WidgetPanel;

class Panel :
	public Parameters
{
public:
	virtual ~Panel();

	// allows runtime determination of type
	virtual PANEL_ID getID() = 0;

	// determines if p is in this->rect
	BOOL contains(const POINT& p, BOOL localCrds = FALSE);

	// determines if the panel if contained within its parent
	BOOL isValid();

	// determines if p is on the border of the panel
	// this function will only work if the paint is contained within the panel
	BOOL onBorder(const POINT& p, BOOL localCrds = FALSE);

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
	// creates a Panel from scratch
	Panel(Panel* pParent, PRECT npRc, BYTE pMal, LONG minWidth, LONG minHeight);

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

public:
	// give npRc in panel coordinates
	// initializes npRc with the global coordinates of the rectangle
	void getGlobalRect(PRECT npRc);

	// give npP in panel coordinates
	// initializes npP with the global coordinates of the point
	void getGlobalPoint(PPOINT npP);

	// give npRc in global coordinates
	// initializes npRc with the panel coordinates of the rectangle
	void getLocalRect(PRECT npRc);

	// give npP in global coordinates
	// initializes npP with the panel coordinate of the point
	void getLocalPoint(PPOINT npP);

	friend class Container;
};

#ifndef WIDGETS_H
#include "WidgetPanel.h"
#endif

#endif