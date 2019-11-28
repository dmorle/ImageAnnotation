#ifndef WIDGET_H
#define WIDGET_H

#include "WinMain.h"

class Widget
{
	D2D1_RECT_F rect;
	stdBrushes& brushes;

public:

	Widget(double left, double roght, double top, double bottom, stdBrushes& brushes);
	Widget(D2D1_RECT_F rect, stdBrushes& brushes);

	~Widget();

	void render(ID2D1HwndRenderTarget* pRenderTarget);
};

#endif