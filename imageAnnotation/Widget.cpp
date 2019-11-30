#include "Widget.h"



Widget::Widget(HWND hwnd, LONG left, LONG top, LONG right, LONG bottom, stdBrushes& brushe, MainWindow* mw) : 
	brushes(noBrushes)
{
	this->mw = mw;
	this->hwnd = hwnd;
	this->rect = RECT { left, top, right, bottom };
	this->brushes = brushes;
}

Widget::Widget(HWND hwnd, RECT rect, stdBrushes& brushes, MainWindow* mw) :
	brushes(noBrushes)
{
	this->mw = mw;
	this->hwnd = hwnd;
	this->rect = rect;
	this->brushes = brushes;
}

Widget::~Widget()
{
	if (npWidget)
		delete npWidget;
}

void Widget::resize(LONG left, LONG top, LONG right, LONG bottom)
{
	rect.left = left;
	rect.top = top;
	rect.right = right;
	rect.bottom = bottom;
}

void Widget::render(ID2D1HwndRenderTarget* pRenderTarget)
{
	if (npWidget) {
		D2D1_RECT_F r1;
		D2D1_RECT_F r2;

		if (npWidget->rect.top == rect.top) {
			// horizontal division
			r1 = {
				rect.left + edgeSpace,
				rect.top + edgeSpace,
				npWidget->rect.left - edgeSpace,
				rect.bottom - edgeSpace
			};
			r2 = {
				npWidget->rect.left + edgeSpace,
				npWidget->rect.top + edgeSpace,
				npWidget->rect.right - edgeSpace,
				npWidget->rect.bottom - edgeSpace
			};
		}
		else {
			// vertical division
			r1 = {
				rect.left + edgeSpace,
				rect.top + edgeSpace,
				rect.right - edgeSpace,
				npWidget->rect.top - edgeSpace
			};
			r2 = {
				npWidget->rect.left + edgeSpace,
				npWidget->rect.top + edgeSpace,
				npWidget->rect.right - edgeSpace,
				npWidget->rect.bottom - edgeSpace
			};
			
		}

		pRenderTarget->FillRectangle(r1, brushes.widgetBack);
		pRenderTarget->FillRectangle(r2, brushes.widgetBack);

		for (D2D1_RECT_F r : {r1, r2})
			for (int i = 0; i < 3; i++)
				pRenderTarget->DrawLine(
					{ r.right - 2 * edgeSpace * (i + 2), r.bottom - 2 * edgeSpace },
					{ r.right - 2 * edgeSpace, r.bottom - 2 * edgeSpace * (i + 2) },
					brushes.active
				);
	}
	else {
		D2D1_RECT_F r
		{
			rect.left + edgeSpace,
			rect.top + edgeSpace,
			rect.right - edgeSpace,
			rect.bottom - edgeSpace
		};
		pRenderTarget->FillRectangle(r, brushes.widgetBack);

		for (int i = 0; i < 3; i++)
			pRenderTarget->DrawLine(
				{ r.right - 2 * edgeSpace * (i + 2), r.bottom - 2 * edgeSpace },
				{ r.right - 2 * edgeSpace, r.bottom - 2 * edgeSpace * (i + 2) },
				brushes.active
			);
	}
}

Widget* Widget::MouseMove(WPARAM& wparam, POINT& p)
{
	if (dupStart) {
		// the widget split was triggered
		if (npWidget) {
			// a widget is being created
			if (
				minSize > rect.right - p.x &&
				minSize > rect.right - p.y
				) {
				delete npWidget;
				npWidget = NULL;
			}
			else if (npWidget->rect.top == rect.top) {
				// horizontal division
				if (
					minSize < rect.right - p.x &&
					minSize < p.x - rect.left
					)
					npWidget->rect.left = p.x;
				else if (minSize < rect.right - p.x)
					npWidget->rect.left = rect.left + minSize;
				else
					npWidget->rect.left = rect.right - minSize;
			}
			else {
				// vertical division
				if (
					minSize < rect.bottom - p.y &&
					minSize < p.y - rect.top
					)
					npWidget->rect.top = p.y;
				else if (minSize < rect.bottom - p.y)
					npWidget->rect.top = rect.top + minSize;
				else
					npWidget->rect.top = rect.bottom - minSize;
			}
		}
		else {
			// either merging widgets, or has just started
			if (minSize < rect.right - p.x)
				npWidget = new Widget(hwnd, RECT{ p.x, rect.top, rect.right, rect.bottom }, brushes, mw);
			else if (minSize < p.x - rect.right) {
				// not sure yet.  Some type of merge
			}
			else if (minSize < rect.bottom - p.y)
				npWidget = new Widget(hwnd, RECT{ rect.left, p.y, rect.right, rect.bottom }, brushes, mw);
			else if (minSize < p.y - rect.bottom) {
				// not sure yet.  Some type of merge
			}
		}

		InvalidateRect(hwnd, const_cast<RECT*>(&rect), TRUE);
		return this;
	}

	return NULL;
}

Widget* Widget::LUp(WPARAM& wparam, POINT& p)
{
	if (dupStart) {
		if (npWidget) {
			InvalidateRect(hwnd, const_cast<RECT*>(&rect), TRUE);

			if (npWidget->rect.top == rect.top)
				rect.right = npWidget->rect.left;
			else
				rect.bottom = npWidget->rect.top;

			mw->widgets.push_back(npWidget);
			npWidget = NULL;
		}
		dupStart = FALSE;

		return NULL;
	}

	return NULL;
}

Widget* Widget::LDown(WPARAM& wparam, POINT& p)
{
	if (p.y - rect.bottom < p.x - rect.right + 12 * edgeSpace) {
		dupStart = TRUE;
		return this;
	}

	return NULL;
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