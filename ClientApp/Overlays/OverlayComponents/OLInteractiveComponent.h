#ifndef OLCMP_INTERACTIVE_COMPONENT_H
#define OLCMP_INTERACTIVE_COMPONENT_H

#ifndef OVERLAY_COMPONENTS_H
#include "OLBaseComponent.h"
#endif

namespace OLCMP {

	class InteractiveComponent :
		public BaseComponent
	{
	public:
		InteractiveComponent(const RECT& rc);

		virtual ~InteractiveComponent();

		// user inputs
		virtual void MouseMove(const WPARAM& wparam, const POINT& p) = 0;
		virtual void LDown(const WPARAM& wparam, const POINT& p) = 0;
		virtual void LUp(const WPARAM& wparam, const POINT& p) = 0;
	};

}

#endif
