#ifndef BASEWIDGETLAYOUT_H
#define BASEWIDGETLAYOUT_H

#include "../Widget.h"
#include "../Resizable.h"

class BaseWidgetLayout :
	public Widget, public Resizable
{
protected:
	BaseWidgetLayout(PRECT pRc, MainWindow* mw, Resizable* pRB);
};

#endif