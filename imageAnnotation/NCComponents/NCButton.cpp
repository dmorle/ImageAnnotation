#include "NCButton.h"

struct HBRSTRUCT
{
public:
	HBRSTRUCT(
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

		hbr_comp = CreateSolidBrush(comp);
		hbr_comp_passive = CreateSolidBrush(comp_passive);
		hbr_comp_active = CreateSolidBrush(comp_active);
		hbr_comp_pressed = CreateSolidBrush(comp_pressed);
	}

	~HBRSTRUCT()
	{
		if (hbr_back)
			DeleteObject(hbr_back);
		if (hbr_back_passive)
			DeleteObject(hbr_back_passive);
		if (hbr_back_active)
			DeleteObject(hbr_back_active);
		if (hbr_back_pressed)
			DeleteObject(hbr_back_pressed);

		if (hbr_comp)
			DeleteObject(hbr_comp);
		if (hbr_comp_passive)
			DeleteObject(hbr_comp_passive);
		if (hbr_comp_active)
			DeleteObject(hbr_comp_active);
		if (hbr_comp_pressed)
			DeleteObject(hbr_comp_pressed);

	}

	// gets the brush for painting the back of the button given the state
	HBRUSH getBack(BUTTONSTATE state)
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
	HBRUSH getComp(BUTTONSTATE state)
	{
		switch (state) {
		case PASSIVE:
			return hbr_comp_passive ? hbr_comp_passive : hbr_comp;
		case ACTIVE:
			return hbr_comp_active ? hbr_comp_active : hbr_comp;
		case PRESSED:
			return hbr_comp_pressed ? hbr_comp_pressed : hbr_comp;
		}

		return NULL;
	}

private:
	HBRUSH hbr_back;			// default for back of button
	HBRUSH hbr_back_passive;	// color for back of button passively
	HBRUSH hbr_back_active;		// color for back of button when active
	HBRUSH hbr_back_pressed;	// color for back of button when pressed

	HBRUSH hbr_comp;			// default for button colors
	HBRUSH hbr_comp_passive;	// color for components passively
	HBRUSH hbr_comp_active;		// color for components when active
	HBRUSH hbr_comp_pressed;	// color for components when pressed
};

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
	this->onClick = onClick;
}

NCButton::~NCButton()
{
	delete pBrushes;
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
	if (contains(p) && state != PRESSED)
		state = ACTIVE;

	state = PASSIVE;
}

void NCButton::display(HDC hdc)
{
	FillRect(hdc, &rc, pBrushes->getBack(state));
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