#include "DropDownOverlay.h"
#include "../GRAPHICSTRUCT.h"



DropDownOverlay::DropDownOverlay(const POINT& p, LONG width, const std::vector<OLDDElem>& elements) :
	BaseOverlay(
		RECT{
			p.x,
			p.y,
			p.x + width,
			p.y + lSize * (LONG)elements.size() + 4 * edgeSpace
		}
	),
	SolidOverlay(
		RECT{
			p.x,
			p.y,
			p.x + width,
			p.y + lSize * (LONG)elements.size() + 4 * edgeSpace
		}
	)
{
	lblNum = elements.size();
	currLbl = -1;

	pLabels = (OLDDElem*)malloc(sizeof(OLDDElem) * elements.size());
	for (int i = 0; i < elements.size(); i++)
		memcpy(&(pLabels[i]), &(elements[i]), sizeof(OLDDElem));
}

DropDownOverlay::DropDownOverlay(BaseOverlay* pParent, const POINT& p, LONG width, const std::vector<OLDDElem>& elements) :
	BaseOverlay(
		RECT{
			p.x,
			p.y,
			p.x + width,
			p.y + lSize * (LONG)elements.size() + 4 * edgeSpace
		},
		pParent
	),
	SolidOverlay(
		RECT{
			p.x,
			p.y,
			p.x + width,
			p.y + lSize * (LONG)elements.size() + 4 * edgeSpace
		},
		pParent
	)
{
	lblNum = elements.size();
	currLbl = -1;

	pLabels = (OLDDElem*)malloc(sizeof(OLDDElem) * elements.size());
	for (int i = 0; i < elements.size(); i++)
		memcpy(&(pLabels[i]), &(elements[i]), sizeof(OLDDElem));
}

DropDownOverlay::~DropDownOverlay()
{
	free(pLabels);
}

void DropDownOverlay::MouseMove(const WPARAM& wparam, const POINT& p)
{
	INT8 nLbl = getLabelNum(p);
	if (nLbl == currLbl)
		return;

	currLbl = nLbl;
	state = ACTIVE;

	InvalidateRect(hwnd, pRc, TRUE);
}

void DropDownOverlay::LDown(const WPARAM& wparam, const POINT& p)
{
	currLbl = getLabelNum(p);
	state = PRESSED;

	if (pLabels[currLbl].LDown)
		pLabels[currLbl].LDown(this);

	InvalidateRect(hwnd, pRc, TRUE);
}

void DropDownOverlay::LUp(const WPARAM& wparam, const POINT& p)
{
	INT8 nLbl = getLabelNum(p);
	if (nLbl == currLbl)
	{
		if (nLbl == -1)
		{
			update(p);
			return;
		}
		if (state == PRESSED)
		{
			if (pLabels[currLbl].LUp)
				pLabels[currLbl].LUp(this);

			state = ACTIVE;
			InvalidateRect(hwnd, pRc, TRUE);
		}
	}
}

void DropDownOverlay::display()
{
	SolidOverlay::display();

	if (currLbl != -1)
	{
		D2D1_RECT_F rc{
			pRc->left + 2 * edgeSpace,
			pRc->top + currLbl * lSize + 3 * edgeSpace,
			pRc->right - 2 * edgeSpace,
			pRc->top + currLbl * lSize + lSize + edgeSpace
		};
		switch (state)
		{
		case PASSIVE:
			pRenderTarget->FillRectangle(rc, pStdGs->back_passive);
			break;
		case ACTIVE:
			pRenderTarget->FillRectangle(rc, pStdGs->back_active);
			break;
		case PRESSED:
			pRenderTarget->FillRectangle(rc, pStdGs->back_pressed);
		}
	}

	for (int i = 0; i < lblNum; i++)
	{
		D2D1_RECT_F rc{
			pRc->left + 4 * edgeSpace,
			pRc->top + i * lSize + 4 * edgeSpace,
			pRc->right - 4 * edgeSpace,
			pRc->top + i * lSize + lSize - 4 * edgeSpace
		};
		pRenderTarget->DrawText(pLabels[i].label, wcslen(pLabels[i].label), pTextFormat, rc, pBrushes->overlayText1);
	}
}

INT8 DropDownOverlay::getLabelNum(const POINT& p)
{
	// checking if a label is selected
	if (!contains(p))
		return -1;

	// getting the label number
	UINT8 i;
	for (i = 1; p.y > getTop() + lSize * i + 2 * edgeSpace; i++);
	return min(i, lblNum) - 1;
}
