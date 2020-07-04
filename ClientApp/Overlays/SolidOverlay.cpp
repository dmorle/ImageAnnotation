#include "SolidOverlay.h"



SolidOverlay::SolidOverlay() :
	BaseOverlay()
{}

SolidOverlay::SolidOverlay(const RECT& rc) :
	BaseOverlay(rc)
{}

SolidOverlay::SolidOverlay(BaseOverlay* pParent) :
	BaseOverlay(pParent)
{}

SolidOverlay::SolidOverlay(const RECT& rc, BaseOverlay* pParent) :
	BaseOverlay(rc, pParent)
{}

SolidOverlay::~SolidOverlay()
{}

void SolidOverlay::display()
{
	BaseOverlay::display();
	D2D1_RECT_F rc{
		pRc->left,
		pRc->top,
		pRc->right,
		pRc->bottom
	};
	pRenderTarget->FillRectangle(rc, pBrushes->overlayBack);
}
