#include "MaxButton.h"



namespace NCCMP {

	MaxButton::MaxButton(
		COLORREF back,
		COLORREF back_passive,
		COLORREF back_active,
		COLORREF back_pressed,
		COLORREF comp,
		COLORREF comp_passive,
		COLORREF comp_active,
		COLORREF comp_pressed,
		void(*onClick)(),
		RECT rc
	) : NCButton(
		back,
		back_passive,
		back_active,
		back_pressed,
		comp,
		comp_passive,
		comp_active,
		comp_pressed,
		onClick
	)
	{
		this->rc = rc;
	}

	MaxButton::MaxButton(
		COLORREF back_passive,
		COLORREF back_active,
		COLORREF back_pressed,
		COLORREF comp_passive,
		COLORREF comp_active,
		COLORREF comp_pressed,
		void(*onClick)(),
		RECT rc
	) : NCButton(
		back_passive,
		back_active,
		back_pressed,
		comp_passive,
		comp_active,
		comp_pressed,
		onClick
	)
	{
		this->rc = rc;
	}

	void MaxButton::display(HDC hdc)
	{
		NCButton::display(hdc);
	}

}