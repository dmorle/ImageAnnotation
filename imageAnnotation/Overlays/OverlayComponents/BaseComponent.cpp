#include "BaseComponent.h"



namespace OLCMP {

	BOOL BaseComponent::contains(const POINT& p)
	{
		LONG localX = p.x - pParent->getLeft();

		if (
			p.x >= pRc->left && p.x < pRc->right &&
			p.y >= pRc->top && p.y < pRc->bottom
			)
			return TRUE;

		return FALSE;
	}

	OLCMP::BaseComponent::BaseComponent(BaseOverlay* pParent, LONG minWidth, LONG minHeight)
	{
	}

}