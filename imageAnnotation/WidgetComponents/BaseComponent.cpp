#include "BaseComponent.h"



namespace WCMP {

	BaseComponent::~BaseComponent()
	{
		if (pRc)
			delete pRc;
	}

	BOOL BaseComponent::contains(POINT p)
	{
		if (
			p.x >= pRc->left && p.x < pRc->right &&
			p.y >= pRc->top && p.y < pRc->bottom
			)
			return TRUE;

		return FALSE;
	}

}