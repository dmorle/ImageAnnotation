#include "Container.h"
#include <cassert>



Container::pResizeInfo Container::pResizingInfo = NULL;
BOOL Container::f_widgetEdit = FALSE;

Container::Container(Panel* pParent, PRECT npRc)
	: Panel(pParent, npRc, 0, 0, 0)
{
	this->orientation = PANEL_ORIENTATION::NONE;
}

Container::~Container()
{
	for (auto& e : cmp)
		if (e)
			delete e;

	if (pResizingInfo)
		delete pResizingInfo;
}

void Container::addPanel(Panel* npPanel)
{
	switch (orientation) {
	case PANEL_ORIENTATION::NONE:
		if (!((pRc->right - pRc->left) -
			(npPanel->getRight() - npPanel->getLeft())))
			this->orientation = PANEL_ORIENTATION::VERTICAL;
		else
			this->orientation = PANEL_ORIENTATION::HORIZONTAL;

		minWidth = npPanel->getMinWidth();
		minHeight = npPanel->getMinHeight();
		break;
	case PANEL_ORIENTATION::HORIZONTAL:
		if (!((pRc->bottom - pRc->top) -
			(npPanel->getBottom() - npPanel->getTop()))) {
			minWidth += npPanel->getMinWidth();
			minHeight = max(minHeight, npPanel->getMinHeight());
		}
		else if (cmp.size() == 1) {
			orientation = PANEL_ORIENTATION::VERTICAL;
			minWidth = max(minWidth, npPanel->getMinWidth());
			minHeight += npPanel->getMinHeight();
		}
		else
			return;
		break;
	case PANEL_ORIENTATION::VERTICAL:
		if (!((pRc->right - pRc->left) -
			(npPanel->getRight() - npPanel->getLeft()))) {
			minWidth = max(minWidth, npPanel->getMinWidth());
			minHeight += npPanel->getMinHeight();
		}
		else if (cmp.size() == 1) {
			orientation = PANEL_ORIENTATION::HORIZONTAL;
			minWidth += npPanel->getMinWidth();
			minHeight = max(minHeight, npPanel->getMinHeight());
		}
		break;
	}

	this->cmp.push_back(npPanel);
}

void Container::MouseMove(const WPARAM& wparam, const POINT& p)
{
	POINT np(p);
	getLocalPoint(&np);
	// np is now in local coordinates

	if (pResizingInfo) {
		assert(orientation != PANEL_ORIENTATION::NONE);

		LONG nloc;
		if (orientation == PANEL_ORIENTATION::HORIZONTAL) {
			// horizontal orientation
			SetCursor(pCursors->sizewe);

			if (np.x - pResizingInfo->p1->getLeft() < pResizingInfo->p1->getMinWidth())
				// min width for p1
				nloc = pResizingInfo->p1->getLeft() + pResizingInfo->p1->getMinWidth();
			else if (pResizingInfo->p2->getRight() - np.x < pResizingInfo->p2->getMinWidth())
				// min width for p2
				nloc = pResizingInfo->p2->getRight() - pResizingInfo->p2->getMinWidth();
			else
				// regular resizing
				nloc = np.x;

			pResizingInfo->p1->resizeX(pResizingInfo->p1->getLeft(), nloc);
			pResizingInfo->p2->resizeX(nloc, pResizingInfo->p2->getRight());
		}
		else {
			// vertical orientation
			SetCursor(pCursors->sizens);

			if (np.y - pResizingInfo->p1->getTop() < pResizingInfo->p1->getMinHeight())
				// min height for p1
				nloc = pResizingInfo->p1->getTop() + pResizingInfo->p1->getMinHeight();
			else if (pResizingInfo->p2->getBottom() - np.y < pResizingInfo->p2->getMinHeight())
				// min height for p2
				nloc = pResizingInfo->p2->getBottom() - pResizingInfo->p2->getMinHeight();
			else
				// regular resizing
				nloc = np.y;

			pResizingInfo->p1->resizeY(pResizingInfo->p1->getTop(), nloc);
			pResizingInfo->p2->resizeY(nloc, pResizingInfo->p2->getBottom());
		}
		
		RECT nRc(*pRc);
		if (pParent)
			pParent->getGlobalRect(&nRc);

		InvalidateRect(NULL, &nRc, FALSE);
	}
	else if (f_widgetEdit) {
		// TODO: come up with a widget splitting / merging system to work with the new widget system
	}
	else {
		if (!contains(p) || onBorder(p))
			if (pParent) {
				pAP = pParent;
				pParent->MouseMove(wparam, p);
				return;
			}

		// checking for a resize event
		if (orientation == PANEL_ORIENTATION::VERTICAL) {
			Panel* topPanel = NULL;
			Panel* bottomPanel = NULL;
			for (auto& e : cmp) {
				if (
					!bottomPanel &&
					e->getTop() - edgeSpace < np.y &&
					e->getTop() + edgeSpace > np.y
					)
					bottomPanel = e;
				else if (topPanel)
					break;	// both panels have been found
				if (
					e->getBottom() - edgeSpace < np.y &&
					e->getBottom() + edgeSpace > np.y
					)
					topPanel = e;
			}
			if (topPanel) {
				assert(bottomPanel);
				SetCursor(pCursors->sizens);
			}
		}
		else {
			Panel* leftPanel = NULL;
			Panel* rightPanel = NULL;
			for (auto& e : cmp) {
				if (
					!rightPanel &&
					e->getLeft() - edgeSpace < np.x &&
					e->getLeft() + edgeSpace > np.x
					)
					rightPanel = e;
				else if (leftPanel)
					break;
				if (
					e->getRight() - edgeSpace < np.x &&
					e->getRight() + edgeSpace > np.x
					)
					leftPanel = e;
			}
			if (leftPanel) {
				assert(rightPanel);
				SetCursor(pCursors->sizewe);
			}
		}

		for (auto& e : cmp)
			if (e->contains(np, TRUE) && !e->onBorder(np, TRUE)) {
				pAP = e;
				e->MouseMove(wparam, p);
			}
	}
}

void Container::LDown(const WPARAM& wparam, const POINT& p)
{
	assert(orientation != PANEL_ORIENTATION::NONE);

	if (!contains(p))
		if (pParent) {
			pAP = pParent;
			pParent->LDown(wparam, p);
			return;
		}

	POINT np(p);
	getLocalPoint(&np);
	// np is now in local coordinates

	// checking for a resize event
	if (orientation == PANEL_ORIENTATION::VERTICAL) {
		Panel* topPanel = NULL;
		Panel* bottomPanel = NULL;
		for (auto& e : cmp) {
			if (
				!bottomPanel &&
				e->getTop() - edgeSpace < np.y &&
				e->getTop() + edgeSpace > np.y
				)
				bottomPanel = e;
			else if (topPanel)
				break;	// both panels have been found
			if (
				e->getBottom() - edgeSpace < np.y &&
				e->getBottom() + edgeSpace > np.y
				)
				topPanel = e;
		}
		if (topPanel) {
			assert(bottomPanel);
			SetCursor(pCursors->sizens);
			pResizingInfo = new resizeInfo{ topPanel, bottomPanel };
			return;
		}
	}
	else {
		Panel* leftPanel = NULL;
		Panel* rightPanel = NULL;
		for (auto& e : cmp) {
			if (
				!rightPanel &&
				e->getLeft() - edgeSpace < np.x &&
				e->getLeft() + edgeSpace > np.x
				)
				rightPanel = e;
			else if (leftPanel)
				break;
			if (
				e->getRight() - edgeSpace < np.x &&
				e->getRight() + edgeSpace > np.x
				)
				leftPanel = e;
		}
		if (leftPanel) {
			assert(rightPanel);
			SetCursor(pCursors->sizewe);
			pResizingInfo = new resizeInfo{ leftPanel, rightPanel };
			return;
		}
	}

	for (auto& e : cmp)
		if (e->contains(np, TRUE))
			e->LDown(wparam, p);
}

void Container::LUp(const WPARAM& wparam, const POINT& p)
{
	POINT np(p);
	getLocalPoint(&np);
	// np is now in local coordinates

	if (pResizingInfo) {
		assert(orientation != PANEL_ORIENTATION::NONE);

		LONG nloc;
		if (orientation == PANEL_ORIENTATION::HORIZONTAL) {
			// horizontal orientation
			SetCursor(pCursors->sizewe);

			if (np.x - pResizingInfo->p1->getLeft() < pResizingInfo->p1->getMinWidth())
				// min width for p1
				nloc = pResizingInfo->p1->getLeft() + pResizingInfo->p1->getMinWidth();
			else if (pResizingInfo->p2->getRight() - np.x < pResizingInfo->p2->getMinWidth())
				// min width for p2
				nloc = pResizingInfo->p2->getRight() - pResizingInfo->p2->getMinWidth();
			else
				// regular resizing
				nloc = np.x;

			pResizingInfo->p1->resizeX(pResizingInfo->p1->getLeft(), nloc);
			pResizingInfo->p2->resizeX(nloc, pResizingInfo->p2->getRight());
		}
		else {
			// vertical orientation
			SetCursor(pCursors->sizens);

			if (np.y - pResizingInfo->p1->getTop() < pResizingInfo->p1->getMinHeight())
				// min height for p1
				nloc = pResizingInfo->p1->getTop() + pResizingInfo->p1->getMinHeight();
			else if (pResizingInfo->p2->getBottom() - np.y < pResizingInfo->p2->getMinHeight())
				// min height for p2
				nloc = pResizingInfo->p2->getBottom() - pResizingInfo->p2->getMinHeight();
			else
				// regular resizing
				nloc = np.y;

			pResizingInfo->p1->resizeY(pResizingInfo->p1->getTop(), nloc);
			pResizingInfo->p2->resizeY(nloc, pResizingInfo->p2->getBottom());
		}

		RECT nRc(*pRc);
		if (pParent)
			pParent->getGlobalRect(&nRc);

		InvalidateRect(NULL, &nRc, FALSE);

		delete pResizingInfo;
		pResizingInfo = NULL;
	}
	else if (f_widgetEdit) {

	}
	else {
		if (!contains(p))
			if (pParent) {
				pAP = pParent;
				pParent->LUp(wparam, p);
				return;
			}

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
			Panel* pHighMalPanel = cmp[0];
			for (auto& e : cmp)
				if (e->getPanelMaliability() > pHighMalPanel->getPanelMaliability())
					pHighMalPanel = e;

			// getting all elements right of the above element
			std::vector<Panel*> pPanels;
			for (auto& e : cmp)
				if (e->getLeft() >= pHighMalPanel->getRight())
					pPanels.push_back(e);

			// adjusting all components
			pHighMalPanel->resizeX(pHighMalPanel->getLeft(), pHighMalPanel->getRight() + dWidth);
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
				// getting all panels right of e
				std::vector<Panel*> pPanels;
				for (auto& e1 : cmp)
					if (e1->getLeft() >= e->getRight())
						pPanels.push_back(e1);

				// adjusting e and pPanels
				if (e->getMinWidth() <= e->getRight() - e->getLeft() + dWidth) {
					// last resize needed, resize by dWidth
					e->resizeX(e->getLeft(), e->getRight() + dWidth);
					for (auto& e1 : pPanels)
						e1->transX(dWidth);

					break;
				}
				else {
					// resize e to the minWidth and update dWidth
					LONG ddWidth = e->getMinWidth() - e->getRight() + e->getLeft();
					dWidth -= ddWidth;
					e->resizeX(e->getLeft(), e->getLeft() + e->getMinWidth());
					for (auto& e1 : pPanels)
						e1->transX(ddWidth);
				}
			}
		}
	}
	else {
		// vertical orientation => trivial resizing
		for (auto& e : cmp)
			e->resizeX(0, right - left);
	}

	pRc->left = left;
	pRc->right = right;
}

void Container::resizeY(LONG top, LONG bottom)
{
	assert(orientation != PANEL_ORIENTATION::NONE);

	if (orientation == PANEL_ORIENTATION::VERTICAL) {
		// vertical orientation
		LONG dHeight = (bottom - top) - (pRc->bottom - pRc->top);

		if (dHeight > 0) {
			// increase the size of the panel with the lowest maliability

			// finding the panel with lowest maliability
			Panel* pHighMalPanel = cmp[0];
			for (auto& e : cmp)
				if (e->getPanelMaliability() > pHighMalPanel->getPanelMaliability())
					pHighMalPanel = e;

			// getting all elements right of the above element
			std::vector<Panel*> pPanels;
			for (auto& e : cmp)
				if (e->getTop() >= pHighMalPanel->getBottom())
					pPanels.push_back(e);

			// adjusting all components
			pHighMalPanel->resizeY(pHighMalPanel->getTop(), pHighMalPanel->getBottom() + dHeight);
			for (auto& e : pPanels)
				e->transY(dHeight);
		}
		else if (dHeight < 0) {
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
					if (e1->getTop() >= e->getBottom())
						pPanels.push_back(e1);

				// adjusting the e and pPanels
				if (e->getMinHeight() <= e->getBottom() - e->getTop() + dHeight) {
					// last resize needed, resize by dWidth
					e->resizeY(e->getTop(), e->getBottom() + dHeight);
					for (auto& e1 : pPanels)
						e1->transY(dHeight);

					break;
				}
				else {
					// resize e to the minWidth and update dWidth
					LONG ddHeight = e->getMinHeight() - e->getBottom() + e->getTop();
					dHeight -= ddHeight;
					e->resizeY(e->getTop(), e->getTop() + e->getMinHeight());
					for (auto& e1 : pPanels)
						e1->transY(ddHeight);
				}
			}
		}
	}
	else {
		// horizontal orientation => trivial resizing
		for (auto& e : cmp)
			e->resizeY(0, bottom - top);
	}

	pRc->top = top;
	pRc->bottom = bottom;
}

void Container::widgetEdit(WidgetPanel* pWidget)
{
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
		if (npMal < pMal)
			pMal = npMal;
	}
	return pMal;
}