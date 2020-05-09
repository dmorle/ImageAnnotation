#include "OLCompositeComponent.h"



namespace OLCMP {

	CompositeComponent::CompositeComponent(BaseOverlay* pParent, const RECT& rc)
		: BaseComponent(pParent, rc)
	{
		
	}

	CompositeComponent::~CompositeComponent()
	{
	}

}
