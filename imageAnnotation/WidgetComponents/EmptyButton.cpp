#include "EmptyButton.h"



namespace WCMP {

	GRAPHICSTRUCT::GRAPHICSTRUCT(const PGRAPHICSTRUCT pGs)
	{
		back         = pGs->back;
		back_passive = pGs->back_passive;
		back_active  = pGs->back_active;
		back_pressed = pGs->back_pressed;
		comp         = pGs->comp;
		comp_passive = pGs->comp_passive;
		comp_active  = pGs->comp_active;
		comp_pressed = pGs->comp_pressed;
		if (back)
			back->AddRef();
		if (back_passive)
			back_passive->AddRef();
		if (back_active)
			back_active->AddRef();
		if (back_pressed)
			back_pressed->AddRef();
		if (comp)
			comp->AddRef();
		if (comp_passive)
			comp_passive->AddRef();
		if (comp_active)
			comp_active->AddRef();
		if (comp_pressed)
			comp_pressed->AddRef();
	}

	GRAPHICSTRUCT::GRAPHICSTRUCT(ID2D1HwndRenderTarget *pRenderTarget, appPalette palette)
	{
		back         = NULL;
		back_passive = NULL;
		pRenderTarget->CreateSolidColorBrush(palette[appPalette::PASSIVE   ], &back_active );
		pRenderTarget->CreateSolidColorBrush(palette[appPalette::ACTIVE    ], &back_pressed);
		pRenderTarget->CreateSolidColorBrush(palette[appPalette::TEXT_COLOR], &comp        );
		comp_passive = NULL;
		comp_active  = NULL;
		comp_pressed = NULL;
	}

	GRAPHICSTRUCT::GRAPHICSTRUCT(
		ID2D1HwndRenderTarget* pRenderTarget,
		D2D1::ColorF back
	)
	{
		pRenderTarget->CreateSolidColorBrush(back, &this->back);
		back_passive = NULL;
		back_active  = NULL;
		back_pressed = NULL;
		comp         = NULL;
		comp_passive = NULL;
		comp_active  = NULL;
		comp_pressed = NULL;
	}

	GRAPHICSTRUCT::GRAPHICSTRUCT(
		ID2D1HwndRenderTarget* pRenderTarget,
		D2D1::ColorF back,
		D2D1::ColorF comp
	)
	{
		pRenderTarget->CreateSolidColorBrush(back, &this->back);
		back_passive = NULL;
		back_active  = NULL;
		back_pressed = NULL;
		pRenderTarget->CreateSolidColorBrush(comp, &this->comp);
		comp_passive = NULL;
		comp_active  = NULL;
		comp_pressed = NULL;
	}

	GRAPHICSTRUCT::GRAPHICSTRUCT(
		ID2D1HwndRenderTarget* pRenderTarget,
		D2D1::ColorF back_passive,
		D2D1::ColorF back_active,
		D2D1::ColorF back_pressed
	)
	{
		back         = NULL;
		pRenderTarget->CreateSolidColorBrush(back_passive, &this->back_passive);
		pRenderTarget->CreateSolidColorBrush(back_active , &this->back_active );
		pRenderTarget->CreateSolidColorBrush(back_pressed, &this->back_pressed);
		comp         = NULL;
		comp_passive = NULL;
		comp_active  = NULL;
		comp_pressed = NULL;
	}

	GRAPHICSTRUCT::GRAPHICSTRUCT(
		ID2D1HwndRenderTarget* pRenderTarget,
		D2D1::ColorF back_passive,
		D2D1::ColorF back_active,
		D2D1::ColorF back_pressed,
		D2D1::ColorF comp_passive,
		D2D1::ColorF comp_active,
		D2D1::ColorF comp_pressed
	)
	{
		back         = NULL;
		pRenderTarget->CreateSolidColorBrush(back_passive, &this->back_passive);
		pRenderTarget->CreateSolidColorBrush(back_active , &this->back_active );
		pRenderTarget->CreateSolidColorBrush(back_pressed, &this->back_pressed);
		comp         = NULL;
		pRenderTarget->CreateSolidColorBrush(comp_passive, &this->comp_passive);
		pRenderTarget->CreateSolidColorBrush(comp_active , &this->comp_active );
		pRenderTarget->CreateSolidColorBrush(comp_pressed, &this->comp_pressed);
	}

	GRAPHICSTRUCT::GRAPHICSTRUCT(
		ID2D1HwndRenderTarget* pRenderTarget,
		D2D1::ColorF back,
		D2D1::ColorF back_passive,
		D2D1::ColorF back_active,
		D2D1::ColorF back_pressed
	)
	{
		pRenderTarget->CreateSolidColorBrush(back        , &this->back        );
		pRenderTarget->CreateSolidColorBrush(back_passive, &this->back_passive);
		pRenderTarget->CreateSolidColorBrush(back_active , &this->back_active );
		pRenderTarget->CreateSolidColorBrush(back_pressed, &this->back_pressed);
		comp         = NULL;
		comp_passive = NULL;
		comp_active  = NULL;
		comp_pressed = NULL;
	}

	GRAPHICSTRUCT::GRAPHICSTRUCT(
		ID2D1HwndRenderTarget* pRenderTarget,
		D2D1::ColorF back,
		D2D1::ColorF back_passive,
		D2D1::ColorF back_active,
		D2D1::ColorF back_pressed,
		D2D1::ColorF comp,
		D2D1::ColorF comp_passive,
		D2D1::ColorF comp_active,
		D2D1::ColorF comp_pressed
	)
	{
		pRenderTarget->CreateSolidColorBrush(back        , &this->back        );
		pRenderTarget->CreateSolidColorBrush(back_passive, &this->back_passive);
		pRenderTarget->CreateSolidColorBrush(back_active , &this->back_active );
		pRenderTarget->CreateSolidColorBrush(back_pressed, &this->back_pressed);
		pRenderTarget->CreateSolidColorBrush(comp        , &this->comp        );
		pRenderTarget->CreateSolidColorBrush(comp_passive, &this->comp_passive);
		pRenderTarget->CreateSolidColorBrush(comp_active , &this->comp_active );
		pRenderTarget->CreateSolidColorBrush(comp_pressed, &this->comp_pressed);
	}

	GRAPHICSTRUCT::~GRAPHICSTRUCT()
	{
		SafeRelease(&back        );
		SafeRelease(&back_passive);
		SafeRelease(&back_active );
		SafeRelease(&back_pressed);
		SafeRelease(&comp        );
		SafeRelease(&comp_passive);
		SafeRelease(&comp_active );
		SafeRelease(&comp_pressed);
	}



	EmptyButton::EmptyButton(
		ID2D1HwndRenderTarget* pRenderTarget,
		D2D1_RECT_F* pRc,
		PRECT parentpRc,
		ResizeBehaviour* pRB,
		void (*onClick)(),
		void (*paintSelf)(PRECT),
		appPalette palette
	) :
		BaseComponent(pRc, parentpRc, pRB),
		InteractiveComponent(pRc, parentpRc, pRB, onClick, paintSelf)
	{
		this->pRB = new ResizeBehaviour(pRB);
		this->pGs = new GRAPHICSTRUCT(pRenderTarget, palette);
	}

	EmptyButton::EmptyButton(EmptyButton* pThis, PRECT npRc)
		: BaseComponent(pThis, npRc), InteractiveComponent(pThis, npRc)
	{
		this->pRB = new ResizeBehaviour(pThis->pRB);
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