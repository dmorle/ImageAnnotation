#include "Widget.h"



Widget::Widget(Panel* pParent, PRECT pRc)
	: Panel(pParent, pRc)
{}

Widget::~Widget()
{
	for (auto& e : cmp)
		delete e;
}

Widget* Widget::operator>>(WCMP::BaseComponent* npCmp)
{
	cmp.push_back(npCmp);
	return this;
}

void Widget::resize(const RECT& rc)
{
	pRc->left = rc.left;
	pRc->top = rc.top;
	pRc->right = rc.right;
	pRc->bottom = rc.bottom;

	// for each component: use parentpRc
	for (auto e : cmp)
		e->resize();
}

void Widget::display()
{
	D2D1_RECT_F r
	{
		pRc->left + edgeSpace,
		pRc->top + edgeSpace,
		pRc->right - edgeSpace,
		pRc->bottom - edgeSpace
	};
	pRenderTarget->FillRectangle(r, brushes.widgetBack);

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
	for (auto& e : cmp)
		e->display(pRenderTarget);
}

void Widget::MouseMove(const WPARAM& wparam, const POINT& p)
{
	if (!contains(p))
		pParent->MouseMove(wparam, p);

	else {
		// passing action to components
		POINT localCrds{ p.x - pRc->left, p.y - pRc->top };

		for (auto& e : cmp) {
			if (e->contains(localCrds))
				e->MouseMove(localCrds);
			else
				e->MouseLeave();
		}
	}
}

WIDGET_RESULT Widget::LUp(WPARAM& wparam, POINT& p)
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
		return WR_RELEASE;
	}

	// passing action to components
	p.x -= pRc->left;
	p.y -= pRc->top;

	for (auto & e : components)
		if (e->contains(p))
			e->LUp(p);

	return WR_KEEP;
}

WIDGET_RESULT Widget::LDown(WPARAM& wparam, POINT& p)
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
		return WR_KEEP;
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
		return WR_KEEP;
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
		return WR_KEEP;
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
		return WR_KEEP;
	}
	if (p.y - pRc->bottom < p.x - pRc->right + 12 * edgeSpace) {
		// merging or splitting widgets
		widgetEdit = TRUE;
		return WR_KEEP;
	}

	// passing action to components
	p.x -= pRc->left;
	p.y -= pRc->top;

	for (auto & e : components)
		if (e->contains(p))
			e->LDown(p);

	return WR_KEEP;
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