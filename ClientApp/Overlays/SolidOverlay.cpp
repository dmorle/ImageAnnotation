#include "SolidOverlay.h"



SolidOverlay::SolidOverlay(const RECT& rc) :
	BaseOverlay(rc)
{}

SolidOverlay::~SolidOverlay()
{}

void SolidOverlay::display()
{
	D2D1_RECT_F rc{
		pRc->left,
		pRc->top,
		pRc->right,
		pRc->bottom
	};
	pRenderTarget->FillRectangle(rc, pBrushes->overlayBack);
}
