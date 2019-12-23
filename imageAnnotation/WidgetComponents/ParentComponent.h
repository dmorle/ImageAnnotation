#ifndef PARENTCOMPONENT_H
#define PARENTCOMPONENT_H

#include "BaseComponent.h"
#include <list>

namespace WCMP {

	class ParentComponent :
		public BaseComponent
	{
	public:
		ParentComponent(D2D1_RECT_F* pRc, PRECT parentpRc);

		~ParentComponent();

		void MouseMove(POINT p) override;
		void LDown(POINT p) override;
		void LUp(POINT p) override;
		void MouseLeave() override;

		void resize(PRECT npRc) override;
		virtual void display(ID2D1HwndRenderTarget* pRenderTarget) override;

		virtual BaseComponent* clone(PRECT nparentpRc) override;

	protected:
		std::list<PBaseComponent> children;

		void activateElement(std::list<PBaseComponent>::iterator);
	};

	typedef ParentComponent* PParentComponent;

}

#endif