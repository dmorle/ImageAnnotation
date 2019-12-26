#include "BaseWidgetLayout.h"



BaseWidgetLayout::BaseWidgetLayout(PRECT pRc, MainWindow* mw, Resizable* pRB)
	: Widget(pRc, mw), Resizable(pRB)
{
	delete pRB;
}