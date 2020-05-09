#ifndef OLCMP_BASE_COMPONENT_H
#define OLCMP_BASE_COMPONENT_H

#ifndef OVERLAY_COMPONENTS_H
#include "../../Parameters.h"
#endif

namespace OLCMP {

	class BaseComponent :
		public Parameters
	{
	public:
		// determines if p is in pRc
		BOOL contains(const POINT& p);

		// user inputs
		virtual void MouseMove(const WPARAM& wparam, const POINT& p) = 0;
		virtual void LDown(const WPARAM& wparam, const POINT& p) = 0;
		virtual void LUp(const WPARAM& wparam, const POINT& p) = 0;

		// return pRc->left;
		LONG getLeft();
		// return pRc->top;
		LONG getTop();
		// return pRc->right;
		LONG getRight();
		// return pRc->bottom;
		LONG getBottom();

		// displays the component to the screen
		virtual void display() = 0;

	protected:
		BaseComponent(BaseOverlay* pParent, const RECT& rc);

		// bounding rectangle
		PRECT pRc;

		void getGlobalRect(RECT& nrc);
		void getGlobalRect(D2D1_RECT_F& nrc);

		void getGlobalRect(PRECT npRc);
		void getGlobalRect(D2D1_RECT_F* npRc);

		BOOL IsValidRect();

	private:
		BaseOverlay* pParent;
	};

}

#ifndef OVERLAY_COMPONENTS_H
#include "../BaseOverlay.h"
#endif

#endif