#ifndef OLCMP_COMPOSITE_COMPONENT_H
#define OLCMP_COMPOSITE_COMPONENT_H

#ifndef OVERLAY_COMPONENTS_H
#include "OLBaseComponent.h"
#endif

namespace OLCMP {

	class CompositeComponent :
		public BaseComponent
	{
	public:
		CompositeComponent(BaseOverlay* pParent, const RECT& rc);

		virtual ~CompositeComponent();
	};

}

#endif