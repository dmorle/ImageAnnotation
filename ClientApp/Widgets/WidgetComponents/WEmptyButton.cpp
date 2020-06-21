#include "WEmptyButton.h"



namespace WCMP {

	EmptyButton::EmptyButton(
		ID2D1HwndRenderTarget* pRenderTarget,
		D2D1_RECT_F* pRc,
		PRECT parentpRc,
		Resizable* pRB,
		void (*onClick)(),
		void (*paintSelf)(PRECT),
		appPalette palette
	) :
		BaseComponent(pRc, parentpRc, pRB),
		InteractiveComponent(pRc, parentpRc, pRB, onClick, paintSelf)
	{
		this->pRB = new Resizable(pRB);
		this->pGs = new GRAPHICSTRUCT(palette);
	}

	EmptyButton::EmptyButton(EmptyButton* pThis, PRECT npRc)
		: BaseComponent(pThis, npRc), InteractiveComponent(pThis, npRc)
	{
		this->pRB = new Resizable(pThis->pRB);
		this->pGs = new GRAPHICSTRUCT(pThis->pGs);
	}

	EmptyButton::~EmptyButton()
	{
		if (pGs)
			delete pGs;
	};

	BaseComponent* EmptyButton::clone(PRECT npRc)
	{
		return new EmptyButton(this, npRc);
	}

	void EmptyButton::display(ID2D1HwndRenderTarget* pRenderTarget)
	{
		if (IsValidRect()) {
			D2D1_RECT_F rc;
			getGlobalRect(rc);

			switch (state) {
			case STATE::PASSIVE:
				if (pGs->back_passive)
					pRenderTarget->FillRectangle(rc, pGs->back_passive);
				break;
			case STATE::ACTIVE:
				if (pGs->back_active)
					pRenderTarget->FillRectangle(rc, pGs->back_active);
				break;
			case STATE::PRESSED:
				if (pGs->back_pressed)
					pRenderTarget->FillRectangle(rc, pGs->back_pressed);
				break;
			default:
				if (pGs->back)
					pRenderTarget->FillRectangle(rc, pGs->back);
			}
		}
	}
}