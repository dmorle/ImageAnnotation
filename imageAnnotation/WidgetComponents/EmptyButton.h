#ifndef EMPTYBUTTON_H
#define EMPTYBUTTON_H

#include "InteractiveComponent.h"

typedef struct appPalette appPalette;
#include "../Widget.h"

namespace WCMP {

	typedef struct GRAPHICSTRUCT GRAPHICSTRUCT;
	typedef GRAPHICSTRUCT* PGRAPHICSTRUCT;
	struct GRAPHICSTRUCT {
		ID2D1SolidColorBrush* back;
		ID2D1SolidColorBrush* back_passive;
		ID2D1SolidColorBrush* back_active;
		ID2D1SolidColorBrush* back_pressed;
		ID2D1SolidColorBrush* comp;
		ID2D1SolidColorBrush* comp_passive;
		ID2D1SolidColorBrush* comp_active;
		ID2D1SolidColorBrush* comp_pressed;

		GRAPHICSTRUCT() {}
		GRAPHICSTRUCT(ID2D1HwndRenderTarget* pRenderTarget, appPalette palette);

		GRAPHICSTRUCT(
			ID2D1HwndRenderTarget* pRenderTarget,
			D2D1::ColorF back
		);

		GRAPHICSTRUCT(
			ID2D1HwndRenderTarget* pRenderTarget,
			D2D1::ColorF back,
			D2D1::ColorF comp
		);

		GRAPHICSTRUCT(
			ID2D1HwndRenderTarget* pRenderTarget,
			D2D1::ColorF back_passive,
			D2D1::ColorF back_active,
			D2D1::ColorF back_pressed
		);

		GRAPHICSTRUCT(
			ID2D1HwndRenderTarget* pRenderTarget,
			D2D1::ColorF back_passive,
			D2D1::ColorF back_active,
			D2D1::ColorF back_pressed,
			D2D1::ColorF comp_passive,
			D2D1::ColorF comp_active,
			D2D1::ColorF comp_pressed
		);

		GRAPHICSTRUCT(
			ID2D1HwndRenderTarget* pRenderTarget,
			D2D1::ColorF back,
			D2D1::ColorF back_passive,
			D2D1::ColorF back_active,
			D2D1::ColorF back_pressed
		);

		GRAPHICSTRUCT(
			ID2D1HwndRenderTarget* pRenderTarget,
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

	class EmptyButton :
		public InteractiveComponent
	{
	public:
		EmptyButton(ID2D1HwndRenderTarget* pRenderTarget, D2D1_RECT_F* pRc, appPalette palette, void (*onClick)(), void (*paintSelf)(D2D1_RECT_F*));
		virtual ~EmptyButton();

		virtual void display(ID2D1HwndRenderTarget* pRenderTarget);

		virtual BaseComponent* clone();

	protected:
		PGRAPHICSTRUCT pGs;

	private:
		EmptyButton(D2D1_RECT_F* pRc, PGRAPHICSTRUCT pGs, void (*onClick)(), void (*paintSelf)(D2D1_RECT_F*));
	};

}

#endif