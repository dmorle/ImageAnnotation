#include "GRAPHICSTRUCT.h"



GRAPHICSTRUCT::GRAPHICSTRUCT()
{
	back = NULL;
	back_passive = NULL;
	back_active = NULL;
	back_pressed = NULL;
	comp = NULL;
	comp_passive = NULL;
	comp_active = NULL;
	comp_pressed = NULL;
}

GRAPHICSTRUCT::GRAPHICSTRUCT(const PGRAPHICSTRUCT pGs)
{
	back = pGs->back;
	back_passive = pGs->back_passive;
	back_active = pGs->back_active;
	back_pressed = pGs->back_pressed;
	comp = pGs->comp;
	comp_passive = pGs->comp_passive;
	comp_active = pGs->comp_active;
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

GRAPHICSTRUCT::GRAPHICSTRUCT(appPalette palette)
{
	back = NULL;
	back_passive = NULL;
	pRenderTarget->CreateSolidColorBrush(pPalette->passive, &back_active);
	pRenderTarget->CreateSolidColorBrush(pPalette->active, &back_pressed);
	pRenderTarget->CreateSolidColorBrush(pPalette->text, &comp);
	comp_passive = NULL;
	comp_active = NULL;
	comp_pressed = NULL;
}

GRAPHICSTRUCT::GRAPHICSTRUCT(
	D2D1::ColorF back
)
{
	pRenderTarget->CreateSolidColorBrush(back, &this->back);
	back_passive = NULL;
	back_active = NULL;
	back_pressed = NULL;
	comp = NULL;
	comp_passive = NULL;
	comp_active = NULL;
	comp_pressed = NULL;
}

GRAPHICSTRUCT::GRAPHICSTRUCT(
	D2D1::ColorF back,
	D2D1::ColorF comp
)
{
	pRenderTarget->CreateSolidColorBrush(back, &this->back);
	back_passive = NULL;
	back_active = NULL;
	back_pressed = NULL;
	pRenderTarget->CreateSolidColorBrush(comp, &this->comp);
	comp_passive = NULL;
	comp_active = NULL;
	comp_pressed = NULL;
}

GRAPHICSTRUCT::GRAPHICSTRUCT(
	D2D1::ColorF back_passive,
	D2D1::ColorF back_active,
	D2D1::ColorF back_pressed
)
{
	back = NULL;
	pRenderTarget->CreateSolidColorBrush(back_passive, &this->back_passive);
	pRenderTarget->CreateSolidColorBrush(back_active, &this->back_active);
	pRenderTarget->CreateSolidColorBrush(back_pressed, &this->back_pressed);
	comp = NULL;
	comp_passive = NULL;
	comp_active = NULL;
	comp_pressed = NULL;
}

GRAPHICSTRUCT::GRAPHICSTRUCT(
	D2D1::ColorF back_passive,
	D2D1::ColorF back_active,
	D2D1::ColorF back_pressed,
	D2D1::ColorF comp_passive,
	D2D1::ColorF comp_active,
	D2D1::ColorF comp_pressed
)
{
	back = NULL;
	pRenderTarget->CreateSolidColorBrush(back_passive, &this->back_passive);
	pRenderTarget->CreateSolidColorBrush(back_active, &this->back_active);
	pRenderTarget->CreateSolidColorBrush(back_pressed, &this->back_pressed);
	comp = NULL;
	pRenderTarget->CreateSolidColorBrush(comp_passive, &this->comp_passive);
	pRenderTarget->CreateSolidColorBrush(comp_active, &this->comp_active);
	pRenderTarget->CreateSolidColorBrush(comp_pressed, &this->comp_pressed);
}

GRAPHICSTRUCT::GRAPHICSTRUCT(
	D2D1::ColorF back,
	D2D1::ColorF back_passive,
	D2D1::ColorF back_active,
	D2D1::ColorF back_pressed
)
{
	pRenderTarget->CreateSolidColorBrush(back, &this->back);
	pRenderTarget->CreateSolidColorBrush(back_passive, &this->back_passive);
	pRenderTarget->CreateSolidColorBrush(back_active, &this->back_active);
	pRenderTarget->CreateSolidColorBrush(back_pressed, &this->back_pressed);
	comp = NULL;
	comp_passive = NULL;
	comp_active = NULL;
	comp_pressed = NULL;
}

GRAPHICSTRUCT::GRAPHICSTRUCT(
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
	pRenderTarget->CreateSolidColorBrush(back, &this->back);
	pRenderTarget->CreateSolidColorBrush(back_passive, &this->back_passive);
	pRenderTarget->CreateSolidColorBrush(back_active, &this->back_active);
	pRenderTarget->CreateSolidColorBrush(back_pressed, &this->back_pressed);
	pRenderTarget->CreateSolidColorBrush(comp, &this->comp);
	pRenderTarget->CreateSolidColorBrush(comp_passive, &this->comp_passive);
	pRenderTarget->CreateSolidColorBrush(comp_active, &this->comp_active);
	pRenderTarget->CreateSolidColorBrush(comp_pressed, &this->comp_pressed);
}

GRAPHICSTRUCT::~GRAPHICSTRUCT()
{
	SafeRelease(&back);
	SafeRelease(&back_passive);
	SafeRelease(&back_active);
	SafeRelease(&back_pressed);
	SafeRelease(&comp);
	SafeRelease(&comp_passive);
	SafeRelease(&comp_active);
	SafeRelease(&comp_pressed);
}