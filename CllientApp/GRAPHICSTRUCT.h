#ifndef GRAPHICSTRUCT_H
#define GRAPHICSTRUCT_H

#include "Parameters.h"

typedef struct GRAPHICSTRUCT GRAPHICSTRUCT;
typedef GRAPHICSTRUCT* PGRAPHICSTRUCT;
struct GRAPHICSTRUCT :
	public Parameters
{
	ID2D1SolidColorBrush* back;
	ID2D1SolidColorBrush* back_passive;
	ID2D1SolidColorBrush* back_active;
	ID2D1SolidColorBrush* back_pressed;
	ID2D1SolidColorBrush* comp;
	ID2D1SolidColorBrush* comp_passive;
	ID2D1SolidColorBrush* comp_active;
	ID2D1SolidColorBrush* comp_pressed;

	GRAPHICSTRUCT();
	GRAPHICSTRUCT(PGRAPHICSTRUCT pGs);
	GRAPHICSTRUCT(appPalette palette);

	GRAPHICSTRUCT(
		D2D1::ColorF back
	);

	GRAPHICSTRUCT(
		D2D1::ColorF back,
		D2D1::ColorF comp
	);

	GRAPHICSTRUCT(
		D2D1::ColorF back_passive,
		D2D1::ColorF back_active,
		D2D1::ColorF back_pressed
	);

	GRAPHICSTRUCT(
		D2D1::ColorF back_passive,
		D2D1::ColorF back_active,
		D2D1::ColorF back_pressed,
		D2D1::ColorF comp_passive,
		D2D1::ColorF comp_active,
		D2D1::ColorF comp_pressed
	);

	GRAPHICSTRUCT(
		D2D1::ColorF back,
		D2D1::ColorF back_passive,
		D2D1::ColorF back_active,
		D2D1::ColorF back_pressed
	);

	GRAPHICSTRUCT(
		D2D1::ColorF back,
		D2D1::ColorF back_passive,
		D2D1::ColorF back_active,
		D2D1::ColorF back_pressed,
		D2D1::ColorF comp,
		D2D1::ColorF comp_passive,
		D2D1::ColorF comp_active,
		D2D1::ColorF comp_pressed
	);

	~GRAPHICSTRUCT();
};

#endif
