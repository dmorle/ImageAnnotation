#ifndef PARENTCOMPONENT_H
#define PARENTCOMPONENT_H

#include "BaseComponent.h"
#include <list>

namespace WCMP {

	class ParentComponent :
		public BaseComponent
	{
	public:
		~ParentComponent();

		void MouseMove(POINT p);
		void LDown(POINT p);
		void LUp(POINT p);
		void MouseLeave();

		virtual void display(ID2D1HwndRenderTarget* pRenderTarget);

		virtual BaseComponent* clone();

	protected:
		std::list<PBaseComponent> children;

		void activateElement(std::list<PBaseComponent>::iterator);
	};

	typedef ParentComponent* PParentComponent;

}

#endif