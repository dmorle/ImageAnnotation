#include "MsgOverlay.h"



MsgOverlay::MsgOverlay(PCWSTR msg, const POINT& p) :
	BaseOverlay(
		RECT{
			p.x,
			p.y,
			p.x + stdWidth,
			p.y + stdHeight
		}
	),
	SolidOverlay(
		RECT{
			p.x,
			p.y,
			p.x + stdWidth,
			p.y + stdHeight
		}
	)
{
	this->msg = std::wstring(msg);
	this->width = stdWidth;
	this->height = stdHeight;
}

MsgOverlay::MsgOverlay(BaseOverlay* pParent, PCWSTR msg, const POINT& p) :
	BaseOverlay(
		RECT{
			p.x,
			p.y,
			p.x + stdWidth,
			p.y + stdHeight
		},
		pParent
	),
	SolidOverlay(
		RECT{
			p.x,
			p.y,
			p.x + stdWidth,
			p.y + stdHeight
		},
		pParent
	)
{
	this->msg = std::wstring(msg);
	this->width = stdWidth;
	this->height = stdHeight;
}

MsgOverlay::MsgOverlay(PCWSTR msg, const POINT& p, LONG width, LONG height) :
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
	this->width = width;
	this->height = height;
}

MsgOverlay::MsgOverlay(BaseOverlay* pParent, PCWSTR msg, const POINT& p, LONG width, LONG height) :
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
	this->width = width;
	this->height = height;
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

	IDWriteTextLayout* pLayout;
	pDWriteFactory->CreateTextLayout(
		msg.c_str(),
		msg.length(),
		pTextFormats->pText1,
		pRc->right - pRc->left,
		pRc->bottom - pRc->top,
		&pLayout
	);

	DWRITE_TEXT_METRICS metrics;
	pLayout->GetMetrics(&metrics);

	D2D1_POINT_2F origin{
		(FLOAT)(pRc->left + pRc->right - metrics.width) / 2,
		(FLOAT)(pRc->top + pRc->bottom - metrics.height) / 2
	};

	pRenderTarget->DrawTextLayout(
		origin,
		pLayout,
		pBrushes->overlayText1,
		D2D1_DRAW_TEXT_OPTIONS_NONE
	);
}

const LONG MsgOverlay::getWidth() const
{
	return width;
}

const LONG MsgOverlay::getHeight() const
{
	return height;
}

const LONG MsgOverlay::getStdWidth()
{
	return stdWidth;
}

const LONG MsgOverlay::getStdHeight()
{
	return stdHeight;
}
