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

	LONG OLCMP::BaseComponent::getLeft()
	{
		return pRc->left;
	}

	LONG OLCMP::BaseComponent::getTop()
	{
		return pRc->top;
	}

	LONG OLCMP::BaseComponent::getRight()
	{
		return pRc->right;
	}

	LONG OLCMP::BaseComponent::getBottom()
	{
		return pRc->bottom;
	}

	OLCMP::BaseComponent::BaseComponent(BaseOverlay* pParent, const RECT& rc)
	{
		this->pParent = pParent;
		this->pRc = new RECT(rc);
	}

}