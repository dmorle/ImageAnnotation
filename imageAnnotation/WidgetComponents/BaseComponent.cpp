#include "BaseComponent.h"



namespace WCMP {

	BaseComponent::BaseComponent(D2D1_RECT_F* pRc, PRECT parentpRc, ResizeBehaviour* pRB)
	{
		this->pRc = pRc;
		this->parentpRc = parentpRc;
		if (pRB)
			this->pRB = pRB;
		else
			this->pRB = RESIZE_DEFAULT(pRc, parentpRc);
	}

	BaseComponent::BaseComponent(BaseComponent* pThis, PRECT npRc)
	{
		this->pRc = new D2D1_RECT_F(*pThis->pRc);
		this->parentpRc = npRc;
		if (pThis->pRB)
			this->pRB = new ResizeBehaviour(pThis->pRB);
		else
			this->pRB = RESIZE_DEFAULT(pRc, npRc);
	}

	BaseComponent::~BaseComponent()
	{
		if (pRc)
			delete pRc;
		if (pRB)
			delete pRB;
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

	BOOL BaseComponent::IsValidRect()
	{
		if (
			pRc->left < pRc->right &&
			pRc->top < pRc->bottom &&
			parentpRc->left + pRc->right < parentpRc->right &&
			parentpRc->top + pRc->bottom < parentpRc->bottom &&
			pRc->left > 0 && pRc->top > 0
			)
			return TRUE;
		return FALSE;
	}

	void BaseComponent::resize(PRECT npRc)
	{
		if (!npRc)
			npRc = parentpRc;

		pRB->getCmpRect(npRc, this->pRc);
	}

}