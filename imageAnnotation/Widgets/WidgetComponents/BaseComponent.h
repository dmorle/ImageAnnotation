#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#ifndef WIDGETCMP_H
#include "../../Parameters.h"
#include "Resizable.h"
#endif

namespace WCMP {

	class BaseComponent :
		public Parameters
	{
	public:
		BaseComponent(D2D1_RECT_F* pRc, PRECT parentpRc, Resizable* pRB);
		BaseComponent(BaseComponent* pThis, PRECT npRc);

		virtual ~BaseComponent();

		BOOL contains(POINT p);

		virtual void MouseMove(POINT p) = 0;
		virtual void LDown(POINT p) = 0;
		virtual void LUp(POINT p) = 0;
		virtual void MouseLeave() = 0;

		void resize(PRECT npRc = NULL);
		virtual void display(ID2D1HwndRenderTarget* pRenderTarget) = 0;

		virtual BaseComponent* clone(PRECT nparentpRc) = 0;

	protected:
		D2D1_RECT_F* pRc;
		PRECT parentpRc;

		Resizable* pRB;

		void getGlobalRect(RECT& nrc);
		void getGlobalRect(D2D1_RECT_F& nrc);

		void getGlobalRect(PRECT npRc);
		void getGlobalRect(D2D1_RECT_F* npRc);

		BOOL IsValidRect();
	};

	typedef BaseComponent* PBaseComponent;

}

#endif