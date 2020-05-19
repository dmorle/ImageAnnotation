#ifndef WCMP_PARENT_COMPONENT_H
#define WCMP_PARENT_COMPONENT_H

#ifndef WIDGET_CMP_H
#include "WBaseComponent.h"
#endif

#include <list>

namespace WCMP {

	class ParentComponent :
		public BaseComponent
	{
	public:
		ParentComponent(D2D1_RECT_F* pRc, PRECT parentpRc, Resizable* pRB);

		~ParentComponent();

		void MouseMove(POINT p) override;
		void LDown(POINT p) override;
		void LUp(POINT p) override;
		void MouseLeave() override;

		virtual void display(ID2D1HwndRenderTarget* pRenderTarget) override;

		virtual BaseComponent* clone(PRECT npRc) override;

	protected:
		ParentComponent(ParentComponent* pThis, PRECT npRc);

		std::list<PBaseComponent> children;

		void activateElement(std::list<PBaseComponent>::iterator);
	};

	typedef ParentComponent* PParentComponent;

}

#endif