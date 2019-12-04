#include "NCButton.h"

NCButton::NCButton(
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
	pBrushes = new struct HBRSTRUCT(
		back,
		back_passive,
		back_active,
		back_pressed,
		comp,
		comp_passive,
		comp_active,
		comp_pressed
	);
}

NCButton::~NCButton()
{
	delete pBrushes;
}
