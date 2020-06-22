#ifndef WCMP_EMPTY_BUTTON_H
#define WCMP_EMPTY_BUTTON_H

#ifndef WIDGET_CMP_H
#include "../../Parameters.h"
#include "WInteractiveComponent.h"
#endif

#include "../../GRAPHICSTRUCT.h"

namespace WCMP {

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
			void (*paintSelf)(PRECT)
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