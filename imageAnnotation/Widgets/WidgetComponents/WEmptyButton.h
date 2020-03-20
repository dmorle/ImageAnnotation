#ifndef WCMP_EMPTY_BUTTON_H
#define WCMP_EMPTY_BUTTON_H

#ifndef WIDGET_CMP_H
#include "../../Parameters.h"
#include "WInteractiveComponent.h"
#endif

namespace WCMP {

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

		GRAPHICSTRUCT() {}
		GRAPHICSTRUCT(PGRAPHICSTRUCT pGs);
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
		EmptyButton(
			ID2D1HwndRenderTarget* pRenderTarget,
			D2D1_RECT_F* pRc,
			PRECT parentpRc,
			Resizable* pRB,
			void (*onClick)(),
			void (*paintSelf)(PRECT),
			appPalette palette
		);

		virtual ~EmptyButton();

		virtual void display(ID2D1HwndRenderTarget* pRenderTarget) override;

		virtual BaseComponent* clone(PRECT npRc) override;

	protected:
		EmptyButton(EmptyButton* pThis, PRECT npRc);

		PGRAPHICSTRUCT pGs;
	};

}

#endif