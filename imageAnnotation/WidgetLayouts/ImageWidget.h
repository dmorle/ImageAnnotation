#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include "BaseWidgetLayout.h"

class ImageWidget :
	public BaseWidgetLayout
{
public:
	ImageWidget(PRECT pRc, MainWindow* mw, Resizable* pRB);
};

#endif