#include "Widget.h"



Widget::Widget(FLOAT left, FLOAT right, FLOAT top, FLOAT bottom, stdBrushes& brushes) : 
	brushes(stdBrushes::none)
{
	this->rect = D2D1_RECT_F { left, right, top, bottom };
	this->brushes = brushes;
}

Widget::Widget(D2D1_RECT_F rect, stdBrushes& brushes) :
	brushes(stdBrushes::none)
{
	this->rect = rect;
	this->brushes = brushes;
}

Widget::~Widget()
{
}

void Widget::render(ID2D1HwndRenderTarget* pRenderTarget)
{
	pRenderTarget->DrawRectangle(this->rect, brushes.widgetBack);
}
