#ifndef OLCMP_BASE_COMPONENT_H
#define OLCMP_BASE_COMPONENT_H

#ifndef OVERLAY_COMPONENTS_H
#include "../../Parameters.h"
#endif

class CmpOverlay;

namespace OLCMP {

	class BaseComponent :
		public Parameters
	{
		friend CmpOverlay;

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
		BaseComponent(const RECT& rc);

		// bounding rectangle
		PRECT pRc;

		void getGlobalRect(RECT& nrc);
		void getGlobalRect(D2D1_RECT_F& nrc);

		void getGlobalRect(PRECT npRc);
		void getGlobalRect(D2D1_RECT_F* npRc);

		BOOL IsValidRect();

		const BaseOverlay* getParent() const;

	private:
		// this parameter is set when passing the component to the overlay through addComponent
		BaseOverlay* pParent;
	};

}

#ifndef OVERLAY_COMPONENTS_H
#include "../BaseOverlay.h"
#endif

#endif