#include "BaseComponent.h"



namespace WCMP {

	BaseComponent::BaseComponent(D2D1_RECT_F* pRc, PRECT parentpRc)
	{
		this->pRc = pRc;
		this->parentpRc = parentpRc;
	}

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

	void BaseComponent::getGlobalRect(RECT& nrc)
	{
		nrc.left = pRc->left + parentpRc->left;
		nrc.top = pRc->top + parentpRc->top;
		nrc.right = pRc->right + parentpRc->left;
		nrc.bottom = pRc->bottom + parentpRc->top;
	}

	void BaseComponent::getGlobalRect(D2D1_RECT_F& nrc)
	{
		nrc.left = pRc->left + parentpRc->left;
		nrc.top = pRc->top + parentpRc->top;
		nrc.right = pRc->right + parentpRc->left;
		nrc.bottom = pRc->bottom + parentpRc->top;
	}

	void BaseComponent::getGlobalRect(PRECT npRc)
	{
		npRc->left   = pRc->left   + parentpRc->left;
		npRc->top    = pRc->top    + parentpRc->top ;
		npRc->right  = pRc->right  + parentpRc->left;
		npRc->bottom = pRc->bottom + parentpRc->top ;
	}

	void BaseComponent::getGlobalRect(D2D1_RECT_F* npRc)
	{
		npRc->left   = pRc->left   + parentpRc->left;
		npRc->top    = pRc->top    + parentpRc->top ;
		npRc->right  = pRc->right  + parentpRc->left;
		npRc->bottom = pRc->bottom + parentpRc->top ;
	}

}