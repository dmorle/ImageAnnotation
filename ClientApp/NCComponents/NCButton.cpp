#include "NCButton.h"



namespace NCCMP {

	GRAPHICSTRUCT::GRAPHICSTRUCT(
		COLORREF back,
		COLORREF back_passive,
		COLORREF back_active,
		COLORREF back_pressed,
		COLORREF comp,
		COLORREF comp_passive,
		COLORREF comp_active,
		COLORREF comp_pressed
	)
	{
		hbr_back = CreateSolidBrush(back);
		hbr_back_passive = CreateSolidBrush(back_passive);
		hbr_back_active = CreateSolidBrush(back_active);
		hbr_back_pressed = CreateSolidBrush(back_pressed);

		crf_comp = comp;
		crf_comp_passive = comp_passive;
		crf_comp_active = comp_active;
		crf_comp_pressed = comp_pressed;
	}

	GRAPHICSTRUCT::~GRAPHICSTRUCT()
	{
		if (hbr_back)
			DeleteObject(hbr_back);
		if (hbr_back_passive)
			DeleteObject(hbr_back_passive);
		if (hbr_back_active)
			DeleteObject(hbr_back_active);
		if (hbr_back_pressed)
			DeleteObject(hbr_back_pressed);
	}

	// gets the brush for painting the back of the button given the state
	HBRUSH GRAPHICSTRUCT::getBack(BUTTONSTATE state)
	{
		switch (state) {
		case PASSIVE:
			return hbr_back_passive ? hbr_back_passive : hbr_back;
		case ACTIVE:
			return hbr_back_active ? hbr_back_active : hbr_back;
		case PRESSED:
			return hbr_back_pressed ? hbr_back_pressed : hbr_back;
		}

		return NULL;
	}

	// gets the brush for painting components of the button given the state
	COLORREF GRAPHICSTRUCT::getComp(BUTTONSTATE state)
	{
		switch (state) {
		case PASSIVE:
			return crf_comp_passive ? crf_comp_passive : crf_comp;
		case ACTIVE:
			return crf_comp_active ? crf_comp_active : crf_comp;
		case PRESSED:
			return crf_comp_pressed ? crf_comp_pressed : crf_comp;
		}

		return NULL;
	}



	NCButton::NCButton(
		COLORREF back,
		COLORREF back_passive,
		COLORREF back_active,
		COLORREF back_pressed,
		COLORREF comp,
		COLORREF comp_passive,
		COLORREF comp_active,
		COLORREF comp_pressed,
		void (*onClick)()
	)
	{
		pAssets = new struct GRAPHICSTRUCT(
			back,
			back_passive,
			back_active,
			back_pressed,
			comp,
			comp_passive,
			comp_active,
			comp_pressed
		);
		this->onClick = onClick;
		state = PASSIVE;
	}

	NCButton::NCButton(
		COLORREF back_passive,
		COLORREF back_active,
		COLORREF back_pressed,
		COLORREF comp_passive,
		COLORREF comp_active,
		COLORREF comp_pressed,
		void (*onClick)()
	)
	{
		pAssets = new struct GRAPHICSTRUCT(
			NULL,
			back_passive,
			back_active,
			back_pressed,
			NULL,
			comp_passive,
			comp_active,
			comp_pressed
		);
		this->onClick = onClick;
		state = PASSIVE;
	}

	NCButton::~NCButton()
	{
		delete pAssets;
	}

	void NCButton::LDown(POINT p)
	{
		if (contains(p))
			state = PRESSED;
	}

	void NCButton::LUp(POINT p)
	{
		if (contains(p) && state == PRESSED) {
			state = ACTIVE;
			onClick();
		}
	}

	void NCButton::mousemove(POINT p)
	{
		if (contains(p)) {
			if (state != PRESSED)
				state = ACTIVE;
		}
		else
			state = PASSIVE;
	}

	BOOL NCButton::mouseleave()
	{
		if (state != PASSIVE) {
			state = PASSIVE;
			return TRUE;
		}
		return FALSE;
	}

	void NCButton::setTrans(LONG dist)
	{
		LONG size = rc.right - rc.left;
		rc.left = dist + edgeSpace;
		rc.right = rc.left + size;
	}

	void NCButton::display(HDC hdc)
	{
		HBRUSH hbr = pAssets->getBack(state);
		if (hbr)
			FillRect(hdc, &rc, hbr);

		SetBkMode(hdc, TRANSPARENT);
	}

	BOOL NCButton::contains(POINT p)
	{
		if (
			p.x >= rc.left && p.x < rc.right &&
			p.y >= rc.top && p.y < rc.bottom
			)
			return TRUE;

		return FALSE;
	}

}