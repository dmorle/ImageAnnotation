#include "Container.h"
#include <stdlib.h>
#include <cassert>



Container::_pResizeInfo Container::pResizingInfo = NULL;
auto Container::f_widgetEdit = FALSE;

Container::~Container()
{
	for (auto& e : cmp)
		if (e)
			delete e;

	if (pResizingInfo)
		delete pResizingInfo;
}

BOOL Container::addPanel(Panel* npPanel)
{
	// TODO : determine an orientation and append the panel components
	// the return state should be whether the function succeeded
}

void Container::MouseMove(const WPARAM& wparam, const POINT& p)
{
	if (pResizingInfo) {
		assert(orientation != PANEL_ORIENTATION::NONE);

		if (orientation == PANEL_ORIENTATION::HORIZONTAL) {
			// horizontal orientation

			if (p.y - pResizingInfo->p1->getLeft() < pResizingInfo->p1->getMinWidth()) {
				// min width for p1
				LONG nloc = pResizingInfo->p1->getLeft() + pResizingInfo->p1->getMinWidth();

				pResizingInfo->p1->resizeX(pResizingInfo->p1->getLeft, nloc);
				pResizingInfo->p2->resizeX(nloc, pResizingInfo->p2->getRight());
			}
			else if (pResizingInfo->p2->getRight() - p.y > pResizingInfo->p2->getMinWidth()) {
				// min width for p2
				LONG nloc = pResizingInfo->p2->getRight() - pResizingInfo->p2->getMinWidth();

				pResizingInfo->p1->resizeX(pResizingInfo->p1->getLeft(), nloc);
				pResizingInfo->p2->resizeX(nloc, pResizingInfo->p2->getRight());
			}
			else {
				// regular resizing
				pResizingInfo->p1->resizeX(pResizingInfo->p1->getLeft(), p.x);
				pResizingInfo->p2->resizeX(p.x, pResizingInfo->p2->getRight());
			}
		}
		else {
			// vertical orientation

			if (p.x - pResizingInfo->p1->getTop() < pResizingInfo->p1->getMinHeight()) {
				// min width for p1
				LONG nloc = pResizingInfo->p1->getTop() + pResizingInfo->p1->getMinHeight();

				pResizingInfo->p1->resizeY(pResizingInfo->p1->getTop(), nloc);
				pResizingInfo->p2->resizeY(nloc, pResizingInfo->p2->getBottom());
			}
			else if (pResizingInfo->p2->getBottom() - p.y > pResizingInfo->p2->getMinHeight()) {
				// min width for p2
				LONG nloc = pResizingInfo->p2->getBottom() - pResizingInfo->p2->getMinHeight();

				pResizingInfo->p1->resizeY(pResizingInfo->p1->getTop(), nloc);
				pResizingInfo->p2->resizeY(nloc, pResizingInfo->p2->getBottom());
			}
			else {
				// regular resizing
				pResizingInfo->p1->resizeY(pResizingInfo->p1->getTop(), p.y);
				pResizingInfo->p2->resizeY(p.y, pResizingInfo->p2->getBottom());
			}
		}
	}
	else if (f_widgetEdit) {
		// TODO: come up with a widget splitting / merging system to work with the new widget system
	}
	else {
		if (!contains(p))
			pParent->MouseMove(wparam, p);

		else {
			for (auto& e : cmp)
				if (e->contains(p))
					e->MouseMove(wparam, p);
		}
	}
}

void Container::LDown(const WPARAM& wparam, const POINT& p)
{
	if (!contains(p) || onBorder(p))
		pParent->LDown(wparam, p);

	// checking for a resize event
	if (orientation == PANEL_ORIENTATION::VERTICAL) {
		Panel* topPanel = NULL;
		Panel* bottomPanel = NULL;
		for (auto& e : cmp) {
			if (
				!topPanel &&
				e->getTop() - edgeSpace < p.y &&
				e->getTop() + edgeSpace > p.y
				)
				topPanel = e;
			else if (bottomPanel)
				break;	// both panels have been found
			if (
				e->getBottom() - edgeSpace < p.y &&
				e->getBottom() + edgeSpace > p.y
				)
				bottomPanel = e;
		}
		if (topPanel) {
			assert(bottomPanel);
			pResizingInfo = new _resizeInfo{ topPanel, bottomPanel };
			return;
		}
	}
	else if (orientation == PANEL_ORIENTATION::HORIZONTAL) {
		Panel* leftPanel;
		Panel* rightPanel;
		for (auto& e : cmp) {
			if (
				!leftPanel &&
				e->getLeft() - edgeSpace < p.x &&
				e->getLeft() + edgeSpace > p.x
				)
				leftPanel = e;
			else if (rightPanel)
				break;
			if (
				e->getRight() - edgeSpace < p.x &&
				e->getRight() + edgeSpace > p.x
				)
				rightPanel = e;
		}
		if (leftPanel) {
			assert(rightPanel);
			pResizingInfo = new _resizeInfo{ leftPanel, rightPanel };
			return;
		}
	}

	for (auto& e : cmp)
		if (e->contains(p))
			e->LDown(wparam, p);
}

void Container::LUp(const WPARAM& wparam, const POINT& p)
{
	if (pResizingInfo) {

	}
	else if (f_widgetEdit) {

	}
	else {
		if (!contains(p))
			pParent->LUp(wparam, p);

		// TODO: check for border or panel resizing

		for (auto& e : cmp)
			if (e->contains(p))
				e->LUp(wparam, p);
	}
}

void Container::resizeX(LONG left, LONG right)
{
	assert(orientation != PANEL_ORIENTATION::NONE);

	if (orientation == PANEL_ORIENTATION::HORIZONTAL) {
		// horizontal orientation
		LONG dWidth = (right - left) - (pRc->right - pRc->left);

		if (dWidth > 0) {
			// increase the size of the panel with the lowest maliability

			// finding the panel with lowest maliability
			Panel* pLowMalPanel = cmp[0];
			for (auto& e : cmp)
				if (e->getPanelMaliability() < pLowMalPanel->getPanelMaliability())
					pLowMalPanel = e;

			// getting all elements right of the above element
			std::vector<Panel*> pPanels;
			for (auto& e : cmp)
				if (e->getLeft() >= pLowMalPanel->getRight())
					pPanels.push_back(e);

			// adjusting all components
			pLowMalPanel->resizeX(pLowMalPanel->getLeft(), pLowMalPanel->getRight() + dWidth);
			for (auto& e : pPanels)
				e->transX(dWidth);
		}
		else if (dWidth < 0) {
			// take size away backwards through the panel maliabilities

			// reading the maliability values from cmp into pMalArr
			BYTE* pMalArr = (BYTE*)_alloca(sizeof(BYTE) * cmp.size());
			for (int i = 0; i < cmp.size(); i++)
				pMalArr[i] = cmp[i]->getPanelMaliability();

			// insertion sort DSU using pMalArr as key (high -> low)
			for (BYTE i = 1; i < cmp.size(); i++)
				for (BYTE j = i; j > 0; j--)
					if (pMalArr[j] > pMalArr[j - 1]) {
						BYTE tempMal = pMalArr[j];
						pMalArr[j] = pMalArr[j - 1];
						pMalArr[j - 1] = tempMal;

						Panel* tempPanel = cmp[j];
						cmp[j] = cmp[j - 1];
						cmp[j - 1] = tempPanel;
					}
					else
						break;

			// resizing the components
			for (auto& e : cmp) {
				// getting all elements right of e
				std::vector<Panel*> pPanels;
				for (auto& e1 : cmp)
					if (e1->getLeft() >= e->getRight())
						pPanels.push_back(e1);

				if (e->getMinWidth() <= e->getRight() - e->getLeft() + dWidth) {
					// last resize needed, resize to dWidth

					// TODO: resize e and translate all pPanels
				}
				else {
					// resize e to the minWidth and update dWidth
				}
			}
		}
	}
	else {
		// vertical orientation => trivial resizing
		for (auto& e : cmp) {
			e->resizeX(left, right);
		}
	}
}

void Container::resizeY(LONG top, LONG bottom)
{
	BYTE* pMalArr = (BYTE*)_alloca(sizeof(BYTE) * cmp.size());
}

void Container::display()
{
	for (auto& e : cmp)
		e->display();
}

BYTE Container::getPanelMaliability()
{
	if (pMal)
		return pMal;

	if (!cmp.size())
		return 0;

	pMal = cmp[0]->getPanelMaliability();
	for (auto& e : cmp) {
		BYTE npMal = e->getPanelMaliability();
		if (npMal > pMal)
			pMal = npMal;
	}
	return pMal;
}

void Container::m_MouseMove(const WPARAM& wparam, const POINT& p)
{
	
}

void Container::m_LDown(const WPARAM& wparam, const POINT& p)
{
	
}

void Container::m_LUp(const WPARAM& wparam, const POINT& p)
{
	
}