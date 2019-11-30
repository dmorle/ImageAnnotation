#include "Widget.h"



Widget::Widget(HWND hwnd, LONG left, LONG top, LONG right, LONG bottom, stdBrushes& brushes, MainWindow* mw) : 
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

		return;
	}
	if (delWidget) {
		D2D1_RECT_F rDel
		{
			delWidget->rect.left + edgeSpace,
			delWidget->rect.top + edgeSpace,
			delWidget->rect.right - edgeSpace,
			delWidget->rect.bottom - edgeSpace
		};
		pRenderTarget->FillRectangle(rDel, brushes.preDeletion);

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

Widget* Widget::MouseMove(WPARAM& wparam, POINT& p)
{
	RECT updateRect = rect;

	if (widgetEdit) {
		// the widget split was triggered
		if (npWidget) {
			// Splitting widgets
			if (
				minSize > rect.right - p.x &&
				minSize > rect.bottom - p.y
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
		else if (delWidget) {
			// Merging widgets
			if (rect.bottom == delWidget->rect.bottom) {
				// horizontal widget merge
				if (rect.right > p.x) {
					if (minSize < rect.bottom - p.y)
						npWidget = new Widget(hwnd, RECT{ rect.left, p.y, rect.right, rect.bottom }, brushes, mw);

					else if (rect.bottom < p.y)
						for (Widget* e : mw->widgets)
							if (
								e->rect.top == rect.bottom &&
								e->rect.left == rect.left &&
								e->rect.right == rect.right
								) {
								delWidget = e;
								break;
							}

					delWidget = NULL;
				}
			}
			else {
				// vertical widget merge
				if (rect.bottom > p.y) {
					if (minSize < rect.right - p.x)
						npWidget = new Widget(hwnd, RECT{ p.x, rect.top, rect.right, rect.bottom }, brushes, mw);

					else if (rect.right < p.x)
						for (Widget* e : mw->widgets)
							if (
								e->rect.right == rect.left &&
								e->rect.top == rect.top &&
								e->rect.bottom == rect.bottom
								) {
								delWidget = e;
								break;
							}

					delWidget = NULL;
				}
			}
		}
		else {
			// Center Region of Widget Managment
			if (minSize < rect.right - p.x)
				// splitting horizontally
				npWidget = new Widget(hwnd, RECT{ p.x, rect.top, rect.right, rect.bottom }, brushes, mw);

			else if (rect.right < p.x) {
				// merging horizontally
				for (auto& e : mw->widgets)
					if (
						e->rect.left == rect.right &&
						e->rect.top == rect.top &&
						e->rect.bottom == rect.bottom
						) {
						delWidget = e;
						break;
					}

				if (delWidget)
					updateRect.right = delWidget->rect.right;
			}
			else if (minSize < rect.bottom - p.y)
				// splitting vertically
				npWidget = new Widget(hwnd, RECT{ rect.left, p.y, rect.right, rect.bottom }, brushes, mw);

			else if (rect.bottom < p.y) {
				// merging vertically
				for (Widget* e : mw->widgets)
					if (
						e->rect.top == rect.bottom &&
						e->rect.left == rect.left &&
						e->rect.right == rect.right
						) {
						delWidget = e;
						break;
					}

				if (delWidget)
					updateRect.bottom = delWidget->rect.bottom;
			}
		}

		InvalidateRect(hwnd, const_cast<RECT*>(&updateRect), TRUE);
		return this;
	}
	else if (edgeSpace > p.x - rect.left && rect.left != 0) {
		// left resize
	}
	else if (edgeSpace > p.y - rect.top && rect.top != 0) {
		// top resize
	}
	else if (edgeSpace > rect.right - p.x && rect.right != mw->pRenderTarget->GetSize().width) {
		// right resize
	}
	else if (edgeSpace > rect.bottom - p.y && rect.right != mw->pRenderTarget->GetSize().height) {
		// bottom resize
	}

	return NULL;
}

Widget* Widget::LUp(WPARAM& wparam, POINT& p)
{
	if (widgetEdit) {
		if (npWidget) {
			InvalidateRect(hwnd, const_cast<RECT*>(&rect), TRUE);

			if (npWidget->rect.top == rect.top)
				rect.right = npWidget->rect.left;
			else
				rect.bottom = npWidget->rect.top;

			mw->widgets.push_back(npWidget);
			npWidget = NULL;
		}
		if (delWidget) {
			if (rect.bottom == delWidget->rect.bottom)
				// horizontal widget merge
				rect.right = delWidget->rect.right;

			else
				// vertical widget merge
				rect.bottom = delWidget->rect.bottom;
			
			int i = 0;
			for (; i < mw->widgets.size(); i++)
				if (mw->widgets[i] == delWidget)
					break;

			delete delWidget;
			delWidget = NULL;

			mw->widgets.erase(mw->widgets.begin() + i);
		}

		widgetEdit = FALSE;
		InvalidateRect(hwnd, const_cast<RECT*>(&rect), TRUE);
		return NULL;
	}

	return NULL;
}

Widget* Widget::LDown(WPARAM& wparam, POINT& p)
{
	if (p.y - rect.bottom < p.x - rect.right + 12 * edgeSpace) {
		widgetEdit = TRUE;
		return this;
	}
	else if (edgeSpace > p.x - rect.left && rect.left != 0) {
		// left resize
	}
	else if (edgeSpace > p.y - rect.top && rect.top != 0) {
		// top resize
	}
	else if (edgeSpace > rect.right - p.x && rect.right != mw->pRenderTarget->GetSize().width) {
		// right resize
	}
	else if (edgeSpace > rect.bottom - p.y && rect.right != mw->pRenderTarget->GetSize().height) {
		// bottom resize
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