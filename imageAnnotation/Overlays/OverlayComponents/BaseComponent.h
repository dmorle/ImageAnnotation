#ifndef OLCMP_BASE_COMPONENT_H
#define OLCMP_BASE_COMPONENT_H

#ifndef OVERLAY_COMPONENTS_H
#include "../../Parameters.h"
#include "../BaseOverlay.h"
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

		virtual void display() = 0;

	protected:
		BaseComponent(BaseOverlay* pParent, const RECT& rc);

		// bounding rectangle
		PRECT pRc;

	private:
		BaseOverlay* pParent;
	};

}

#endif