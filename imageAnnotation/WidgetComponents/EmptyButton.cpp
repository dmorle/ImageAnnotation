#include "EmptyButton.h"



namespace WCMP {

	GRAPHICSTRUCT::GRAPHICSTRUCT(const GRAPHICSTRUCT& gs)
	{
		back         = gs.back;
		back_passive = gs.back_passive;
		back_active  = gs.back_active;
		back_pressed = gs.back_pressed;
		comp         = gs.comp;
		comp_passive = gs.comp_passive;
		comp_active  = gs.comp_active;
		comp_pressed = gs.comp_pressed;
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



	EmptyButton::EmptyButton(ID2D1HwndRenderTarget* pRenderTarget, D2D1_RECT_F* pRc, appPalette palette, void (*onClick)(), void (*paintSelf)(D2D1_RECT_F*))
	{
		this->pRc = pRc;
		this->pGs = new GRAPHICSTRUCT(pRenderTarget, palette);
		this->state = PASSIVE;
		this->onClick = onClick;
		this->paintSelf = paintSelf;
	}

	EmptyButton::EmptyButton(D2D1_RECT_F* pRc, PGRAPHICSTRUCT pGs, void (*onClick)(), void (*paintSelf)(D2D1_RECT_F*))
	{
		this->pRc = pRc;
		this->pGs = pGs;
		this->state = PASSIVE;
		this->onClick = onClick;
		this->paintSelf = paintSelf;
	}

	EmptyButton::~EmptyButton()
	{
		if (pGs)
			delete pGs;
	};

	BaseComponent* EmptyButton::clone()
	{
		return new EmptyButton(new D2D1_RECT_F(*pRc), new GRAPHICSTRUCT(*pGs), onClick, paintSelf);
	}

	void EmptyButton::display(ID2D1HwndRenderTarget* pRenderTarget)
	{
		switch (state) {
		case PASSIVE:
			if (pGs->back_passive)
				pRenderTarget->FillRectangle(*pRc, pGs->back_passive);
		case ACTIVE:
			if (pGs->back_active)
				pRenderTarget->FillRectangle(*pRc, pGs->back_active);
		case PRESSED:
			if (pGs->back_pressed)
				pRenderTarget->FillRectangle(*pRc, pGs->back_pressed);
		default:
			if (pGs->back)
				pRenderTarget->FillRectangle(*pRc, pGs->back);
		}
	}
}