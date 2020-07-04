#include "MsgOverlay.h"



MsgOverlay::MsgOverlay(PCWSTR msg, const POINT& p) :
	BaseOverlay(
		RECT{
			p.x,
			p.y,
			p.x + width,
			p.y + height
		}
	),
	SolidOverlay(
		RECT{
			p.x,
			p.y,
			p.x + width,
			p.y + height
		}
	)
{
	this->msg = std::wstring(msg);
}

MsgOverlay::MsgOverlay(BaseOverlay* pParent, PCWSTR msg, const POINT& p) :
	BaseOverlay(
		RECT{
			p.x,
			p.y,
			p.x + width,
			p.y + height
		},
		pParent
	),
	SolidOverlay(
		RECT{
			p.x,
			p.y,
			p.x + width,
			p.y + height
		},
		pParent
	)
{
	this->msg = std::wstring(msg);
}

MsgOverlay::~MsgOverlay()
{
}

void MsgOverlay::MouseMove(const WPARAM& wparam, const POINT& p)
{
}

void MsgOverlay::LDown(const WPARAM& wparam, const POINT& p)
{
}

void MsgOverlay::LUp(const WPARAM& wparam, const POINT& p)
{
	update(p);
}

void MsgOverlay::display()
{
	SolidOverlay::display();

	D2D1_RECT_F rc{
		pRc->left,
		pRc->top,
		pRc->right,
		pRc->bottom
	};
	pRenderTarget->DrawText(msg.c_str(), msg.length(), pTextFormat, rc, pBrushes->overlayText1);
}
