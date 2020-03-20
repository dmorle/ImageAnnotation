#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#ifndef OVERLAY_COMPONENTS_H
#include "OLBaseComponent.h"
#endif

namespace OLCMP {

	class TextComponent :
		public BaseComponent
	{
		TextComponent(BaseOverlay* pParent, const RECT& rc);
	};

}

#endif