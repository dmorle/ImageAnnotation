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
		// CmpOverlay sets OLCMP::BaseComponent::pParent to this
		friend CmpOverlay;

	public:
		// determines if p is in pRc
		BOOL contains(const POINT& p);

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

		// true -> has user input functions
		const BOOL isInteractive() const;

	protected:
		BaseComponent(const RECT& rc);

		// bounding rectangle
		PRECT pRc;
		
		// if the component is an instance of OLCMP::InteractiveComponent
		BOOL interactive;

		// initializes a RECT struct declared with the coordinates
		// of the component in global coordinates through a reference
		void getGlobalRect(RECT& nrc);

		// initializes a D2D1_RECT_F struct declared with the coordinates
		// of the component in global coordinates through a reference
		void getGlobalRect(D2D1_RECT_F& nrc);

		// initializes a RECT struct declared with the coordinates
		// of the component in global coordinates through a pointer
		void getGlobalRect(PRECT npRc);

		// initializes a D2D1_RECT_F struct declared with the coordinates
		// of the component in global coordinates through a pointer
		void getGlobalRect(D2D1_RECT_F* npRc);

		// checks if the component rect is contained within the overlay's rect
		BOOL IsValidRect();

		// gets a reference to the parent overlay
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