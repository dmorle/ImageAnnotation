#include "NCTextButton.h"



NCTextButton::NCTextButton(
	COLORREF back,
	COLORREF back_passive,
	COLORREF back_active,
	COLORREF back_pressed,
	COLORREF comp,
	COLORREF comp_passive,
	COLORREF comp_active,
	COLORREF comp_pressed,
	void(*onClick)()
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
) {}

NCTextButton::NCTextButton(
	COLORREF back_passive,
	COLORREF back_active,
	COLORREF back_pressed,
	COLORREF comp_passive,
	COLORREF comp_active,
	COLORREF comp_pressed,
	void(*onClick)()
) : NCButton(
	back_passive,
	back_active,
	back_pressed,
	comp_passive,
	comp_active,
	comp_pressed,
	onClick
) {}