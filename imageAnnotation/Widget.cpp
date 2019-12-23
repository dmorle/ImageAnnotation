#include "Widget.h"



Widget::Widget(LONG left, LONG top, LONG right, LONG bottom, MainWindow* mw)
{
	this->mw = mw;
	this->pRc = new RECT { left, top, right, bottom };
	this->delWidget = NULL;
}

Widget::Widget(PRECT pRc, MainWindow* mw)
{
	this->mw = mw;
	this->pRc = pRc;
	this->delWidget = NULL;
}

Widget::~Widget()
{
	if (npWidget)
		delete npWidget;

	/*
		Deleting all widget components
	*/

	for (auto& e : components)
		delete e;
}

void Widget::addComponent(WCMP::BaseComponent* npCmp)
{
	components.push_back(npCmp);
}

void Widget::createSplit(PRECT npRc)
{
	npWidget = new Widget(npRc, mw);

	for (auto e : components)
		npWidget->components.push_back(e->clone(npRc));
}

void Widget::resize(LONG left, LONG top, LONG right, LONG bottom)
{
	pRc->left = left;
	pRc->top = top;
	pRc->right = right;
	pRc->bottom = bottom;

	// for each component: use parentpRc
	for (auto e : components)
		e->resize();
}

void Widget::render(ID2D1HwndRenderTarget* pRenderTarget)
{
	if (npWidget) {
		D2D1_RECT_F r1;
		D2D1_RECT_F r2;

		if (npWidget->pRc->top == pRc->top) {
			// horizontal division
			r1 = {
				pRc->left + edgeSpace,
				pRc->top + edgeSpace,
				npWidget->pRc->left - edgeSpace,
				pRc->bottom - edgeSpace
			};
			r2 = {
				npWidget->pRc->left + edgeSpace,
				npWidget->pRc->top + edgeSpace,
				npWidget->pRc->right - edgeSpace,
				npWidget->pRc->bottom - edgeSpace
			};
		}
		else {
			// vertical division
			r1 = {
				pRc->left + edgeSpace,
				pRc->top + edgeSpace,
				pRc->right - edgeSpace,
				npWidget->pRc->top - edgeSpace
			};
			r2 = {
				npWidget->pRc->left + edgeSpace,
				npWidget->pRc->top + edgeSpace,
				npWidget->pRc->right - edgeSpace,
				npWidget->pRc->bottom - edgeSpace
			};
			
		}

		pRenderTarget->FillRectangle(r1, mw->brushes.widgetBack);
		pRenderTarget->FillRectangle(r2, mw->brushes.widgetBack);

		for (D2D1_RECT_F r : {r1, r2})
			for (int i = 0; i < 3; i++)
				pRenderTarget->DrawLine(
					{ r.right - 2 * edgeSpace * (i + 2), r.bottom - 2 * edgeSpace },
					{ r.right - 2 * edgeSpace, r.bottom - 2 * edgeSpace * (i + 2) },
					mw->brushes.active
				);

		/*
			Not displaying the widget components for a widget while in edit mode
		*/

		return;
	}
	if (delWidget) {
		D2D1_RECT_F rDel
		{
			delWidget->pRc->left + edgeSpace,
			delWidget->pRc->top + edgeSpace,
			delWidget->pRc->right - edgeSpace,
			delWidget->pRc->bottom - edgeSpace
		};
		pRenderTarget->FillRectangle(rDel, mw->brushes.preDeletion);

		D2D1_RECT_F r
		{
			pRc->left + edgeSpace,
			pRc->top + edgeSpace,
			pRc->right - edgeSpace,
			pRc->bottom - edgeSpace
		};
		pRenderTarget->FillRectangle(r, mw->brushes.widgetBack);

		for (int i = 0; i < 3; i++)
			pRenderTarget->DrawLine(
				{ r.right - 2 * edgeSpace * (i + 2), r.bottom - 2 * edgeSpace },
				{ r.right - 2 * edgeSpace, r.bottom - 2 * edgeSpace * (i + 2) },
				mw->brushes.active
			);
	}

	D2D1_RECT_F r
	{
		pRc->left + edgeSpace,
		pRc->top + edgeSpace,
		pRc->right - edgeSpace,
		pRc->bottom - edgeSpace
	};
	pRenderTarget->FillRectangle(r, mw->brushes.widgetBack);

	for (int i = 0; i < 3; i++)
		pRenderTarget->DrawLine(
			{ r.right - 2 * edgeSpace * (i + 2), r.bottom - 2 * edgeSpace },
			{ r.right - 2 * edgeSpace, r.bottom - 2 * edgeSpace * (i + 2) },
			mw->brushes.active
		);

	/*
		Displaying the widget components for a standard widget
	*/
	D2D1_RECT_F rc{
		pRc->left,
		pRc->top,
		pRc->right,
		pRc->bottom
	};
	for (auto& e : components)
		e->display(pRenderTarget);
}

Widget* Widget::MouseMove(WPARAM& wparam, POINT& p)
{
	RECT updateRect = *pRc;

	if (widgetEdit) {
		// the widget split was triggered
		if (neighbors.size() != 0) {
			// resizing widgets
			LONG base;
			BOOL validSize = TRUE;
			switch (side) {
			case LEFT:
				base = pRc->left;
				SetCursor(mw->cursors.sizewe);

				for (auto e : neighbors)
					if (
						(base == e->pRc->left && minSize > e->pRc->right - p.x) ||
						(base == e->pRc->right && minSize > p.x - e->pRc->left)
						) {
						validSize = FALSE;
						break;
					}

				if (!validSize)
					break;

				for (auto e : neighbors) {
					if (base == e->pRc->left) {
						if (updateRect.right < e->pRc->right)
							updateRect.right = e->pRc->right;

						e->pRc->left = p.x;
					}
					else {
						if (updateRect.left > e->pRc->left)
							updateRect.left = e->pRc->left;

						e->pRc->right = p.x;
					}
					if (updateRect.top > e->pRc->top)
						updateRect.top = e->pRc->top;

					if (updateRect.bottom < e->pRc->bottom)
						updateRect.bottom = e->pRc->bottom;
				}
				break;
			case TOP:
				base = pRc->top;
				SetCursor(mw->cursors.sizens);

				for (auto e : neighbors)
					if (
						(base == e->pRc->top && minSize > e->pRc->bottom - p.y) ||
						(base == e->pRc->bottom && minSize > p.y - e->pRc->top)
						) {
						validSize = FALSE;
						break;
					}

				if (!validSize)
					break;

				for (auto e : neighbors) {
					if (base == e->pRc->top) {
						if (updateRect.bottom < e->pRc->bottom)
							updateRect.bottom = e->pRc->bottom;

						e->pRc->top = p.y;
					}
					else {
						if (updateRect.top > e->pRc->top)
							updateRect.top = e->pRc->top;

						e->pRc->bottom = p.y;
					}
					if (updateRect.left > e->pRc->left)
						updateRect.left = e->pRc->left;

					if (updateRect.right < e->pRc->right)
						updateRect.right = e->pRc->right;
				}
				break;
			case RIGHT:
				base = pRc->right;
				SetCursor(mw->cursors.sizewe);

				for (auto e : neighbors)
					if (
						(base == e->pRc->left && minSize > e->pRc->right - p.x) ||
						(base == e->pRc->right && minSize > p.x - e->pRc->left)
						) {
						validSize = FALSE;
						break;
					}

				if (!validSize)
					break;

				for (auto e : neighbors) {
					if (base == e->pRc->right) {
						if (updateRect.left > e->pRc->left)
							updateRect.left = e->pRc->left;

						e->pRc->right = p.x;
					}
					else {
						if (updateRect.right < e->pRc->right)
							updateRect.right = e->pRc->right;

						e->pRc->left = p.x;
					}
					if (updateRect.top > e->pRc->top)
						updateRect.top = e->pRc->top;

					if (updateRect.bottom < e->pRc->bottom)
						updateRect.bottom = e->pRc->bottom;
				}
				break;
			case BOTTOM:
				base = pRc->bottom;
				SetCursor(mw->cursors.sizens);

				for (auto e : neighbors)
					if (
						(base == e->pRc->top && minSize > e->pRc->bottom - p.y) ||
						(base == e->pRc->bottom && minSize > p.y - e->pRc->top)
						) {
						validSize = FALSE;
						break;
					}

				if (!validSize)
					break;

				for (auto e : neighbors) {
					if (base == e->pRc->bottom) {
						if (updateRect.top > e->pRc->top)
							updateRect.top = e->pRc->top;

						e->pRc->bottom = p.y;
					}
					else {
						if (updateRect.bottom < e->pRc->bottom)
							updateRect.bottom = e->pRc->bottom;

						e->pRc->top = p.y;
					}
					if (updateRect.left > e->pRc->left)
						updateRect.left = e->pRc->left;

					if (updateRect.right < e->pRc->right)
						updateRect.right = e->pRc->right;
				}
				break;
			}
		}
		else if (npWidget) {
			// Splitting widgets
			if (
				minSize > pRc->right - p.x &&
				minSize > pRc->bottom - p.y
				) {
				delete npWidget;
				npWidget = NULL;
			}
			else if (npWidget->pRc->top == pRc->top) {
				// horizontal division
				if (
					minSize < pRc->right - p.x &&
					minSize < p.x - pRc->left
					)
					npWidget->pRc->left = p.x;
				else if (minSize < pRc->right - p.x)
					npWidget->pRc->left = pRc->left + minSize;
				else
					npWidget->pRc->left = pRc->right - minSize;
			}
			else {
				// vertical division
				if (
					minSize < pRc->bottom - p.y &&
					minSize < p.y - pRc->top
					)
					npWidget->pRc->top = p.y;
				else if (minSize < pRc->bottom - p.y)
					npWidget->pRc->top = pRc->top + minSize;
				else
					npWidget->pRc->top = pRc->bottom - minSize;
			}
		}
		else if (delWidget) {
			// Merging widgets
			if (pRc->bottom == delWidget->pRc->bottom) {
				// horizontal widget merge
				if (pRc->right > p.x) {
					// stop merge
					if (minSize < pRc->bottom - p.y)
						createSplit(new RECT{ pRc->left, p.y, pRc->right, pRc->bottom });

					else if (pRc->bottom < p.y)
						for (Widget* e : mw->widgets)
							if (
								e->pRc->top == pRc->bottom &&
								e->pRc->left == pRc->left &&
								e->pRc->right == pRc->right
								) {
								delWidget = e;
								break;
							}

					delWidget = NULL;
				}
			}
			else {
				// vertical widget merge
				if (pRc->bottom > p.y) {
					// stop merging
					if (minSize < pRc->right - p.x)
						createSplit(new RECT{ p.x, pRc->top, pRc->right, pRc->bottom });

					else if (pRc->right < p.x)
						for (Widget* e : mw->widgets)
							if (
								e->pRc->right == pRc->left &&
								e->pRc->top == pRc->top &&
								e->pRc->bottom == pRc->bottom
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
			if (minSize < pRc->right - p.x)
				// splitting horizontally
				createSplit(new RECT{ p.x, pRc->top, pRc->right, pRc->bottom });

			else if (pRc->right < p.x) {
				// merging horizontally
				for (auto& e : mw->widgets)
					if (
						e->pRc->left == pRc->right &&
						e->pRc->top == pRc->top &&
						e->pRc->bottom == pRc->bottom
						) {
						delWidget = e;
						break;
					}

				if (delWidget)
					updateRect.right = delWidget->pRc->right;
			}
			else if (minSize < pRc->bottom - p.y)
				// splitting vertically
				createSplit(new RECT{ pRc->left, p.y, pRc->right, pRc->bottom });

			else if (pRc->bottom < p.y) {
				// merging vertically
				for (Widget* e : mw->widgets)
					if (
						e->pRc->top == pRc->bottom &&
						e->pRc->left == pRc->left &&
						e->pRc->right == pRc->right
						) {
						delWidget = e;
						break;
					}

				if (delWidget)
					updateRect.bottom = delWidget->pRc->bottom;
			}
		}

		mw->RepaintRect(&updateRect);
		return this;
	}
	if (edgeSpace >= p.x - pRc->left && pRc->left != 0) {
		// left resize
		SetCursor(mw->cursors.sizewe);
	}
	else if (edgeSpace >= p.y - pRc->top && pRc->top != 0) {
		// top resize
		SetCursor(mw->cursors.sizens);
	}
	else if (edgeSpace >= pRc->right - p.x && pRc->right != mw->pRenderTarget->GetSize().width) {
		// right resize
		SetCursor(mw->cursors.sizewe);
	}
	else if (edgeSpace >= pRc->bottom - p.y && pRc->right != mw->pRenderTarget->GetSize().height) {
		// bottom resize
		SetCursor(mw->cursors.sizens);
	}

	// passing action to components
	p.x -= pRc->left;
	p.y -= pRc->top;

	for (auto & e : components) {
		if (e->contains(p))
			e->MouseMove(p);
		else
			e->MouseLeave();
	}

	return NULL;
}

Widget* Widget::LUp(WPARAM& wparam, POINT& p)
{
	if (widgetEdit) {
		if (neighbors.size() != 0)
			neighbors.clear();

		else if (npWidget) {
			mw->RepaintRect(pRc);

			if (npWidget->pRc->top == pRc->top)
				pRc->right = npWidget->pRc->left;
			else
				pRc->bottom = npWidget->pRc->top;

			mw->widgets.push_back(npWidget);
			npWidget = NULL;
		}
		else if (delWidget) {
			if (pRc->bottom == delWidget->pRc->bottom)
				// horizontal widget merge
				pRc->right = delWidget->pRc->right;

			else
				// vertical widget merge
				pRc->bottom = delWidget->pRc->bottom;
			
			int i = 0;
			for (; i < mw->widgets.size(); i++)
				if (mw->widgets[i] == delWidget)
					break;

			delete delWidget;
			delWidget = NULL;

			mw->widgets.erase(mw->widgets.begin() + i);
		}

		widgetEdit = FALSE;
		mw->RepaintRect(pRc);
		return NULL;
	}

	// passing action to components
	p.x -= pRc->left;
	p.y -= pRc->top;

	for (auto & e : components)
		if (e->contains(p))
			e->LUp(p);

	return NULL;
}

Widget* Widget::LDown(WPARAM& wparam, POINT& p)
{
	if (edgeSpace >= p.x - pRc->left && pRc->left != 0) {
		// left resize
		widgetEdit = TRUE;
		side = LEFT;
		for (auto e : mw->widgets)
			if (
				pRc->left == e->pRc->left ||
				pRc->left == e->pRc->right
				)
				neighbors.push_back(e);
		return this;
	}
	else if (edgeSpace >= p.y - pRc->top && pRc->top != 0) {
		// top resize
		widgetEdit = TRUE;
		side = TOP;
		for (auto e : mw->widgets)
			if (
				pRc->top == e->pRc->top ||
				pRc->top == e->pRc->bottom
				)
				neighbors.push_back(e);
		return this;
	}
	else if (edgeSpace >= pRc->right - p.x && pRc->right != mw->pRenderTarget->GetSize().width) {
		// right resize
		widgetEdit = TRUE;
		side = RIGHT;
		for (auto e : mw->widgets)
			if (
				pRc->right == e->pRc->right ||
				pRc->right == e->pRc->left
				)
				neighbors.push_back(e);
		return this;
	}
	else if (edgeSpace >= pRc->bottom - p.y && pRc->right != mw->pRenderTarget->GetSize().height) {
		// bottom resize
		widgetEdit = TRUE;
		side = BOTTOM;
		for (auto e : mw->widgets)
			if (
				pRc->bottom == e->pRc->bottom ||
				pRc->bottom == e->pRc->top
				)
				neighbors.push_back(e);
		return this;
	}
	if (p.y - pRc->bottom < p.x - pRc->right + 12 * edgeSpace) {
		// merging or splitting widgets
		widgetEdit = TRUE;
		return this;
	}

	// passing action to components
	p.x -= pRc->left;
	p.y -= pRc->top;

	for (auto & e : components)
		if (e->contains(p))
			e->LDown(p);

	return NULL;
}

BOOL Widget::contains(POINT p)
{
	if (
		p.x >= pRc->left && p.x < pRc->right &&
		p.y >= pRc->top && p.y < pRc->bottom
		)
		return TRUE;

	return FALSE;
}

FLOAT Widget::getLeft()
{
	return this->pRc->left;
}

FLOAT Widget::getTop()
{
	return this->pRc->top;
}

FLOAT Widget::getRight()
{
	return this->pRc->right;
}

FLOAT Widget::getBottom()
{
	return this->pRc->bottom;
}