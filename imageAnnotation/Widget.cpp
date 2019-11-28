#include "Widget.h"



Widget::Widget(FLOAT left, FLOAT top, FLOAT right, FLOAT bottom, stdBrushes& brushes) : 
	brushes(noBrushes)
{
	this->rect = D2D1_RECT_F { left, top, right, bottom };
	this->brushes = brushes;
}

Widget::Widget(D2D1_RECT_F rect, stdBrushes& brushes) :
	brushes(noBrushes)
{
	this->rect = rect;
	this->brushes = brushes;
}

Widget::~Widget()
{
}

void Widget::resize(FLOAT left, FLOAT top, FLOAT right, FLOAT bottom)
{
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;
}

void Widget::render(ID2D1HwndRenderTarget* pRenderTarget)
{
	pRenderTarget->FillRectangle(this->rect, brushes.widgetBack);

	for (int i = 0; i < 3; i++)
		pRenderTarget->DrawLine(
			{rect.right - 2 * edgeSpace * (i + 2), rect.bottom - edgeSpace},
			{rect.right - edgeSpace, rect.bottom - 2 * edgeSpace * (i + 2)},
			brushes.active
		);
}

void Widget::MouseMove(WPARAM wparam, POINT p)
{
}

BOOL Widget::contains(POINT p)
{
	if (
		p.x > rect.left && p.x < rect.right &&
		p.y > rect.top && p.y < rect.bottom
		)
		return TRUE;
	return FALSE;
}