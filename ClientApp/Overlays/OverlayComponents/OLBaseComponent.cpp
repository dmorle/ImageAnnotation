#include "OLBaseComponent.h"



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

	OLCMP::BaseComponent::BaseComponent(const RECT& rc)
	{
		this->pRc = new RECT(rc);
	}

	void BaseComponent::getGlobalRect(RECT& nrc)
	{
		nrc.left = pRc->left + pParent->getLeft();
		nrc.top = pRc->top + pParent->getTop();
		nrc.right = pRc->right + pParent->getLeft();
		nrc.bottom = pRc->bottom + pParent->getTop();
	}

	void BaseComponent::getGlobalRect(D2D1_RECT_F& nrc)
	{
		nrc.left = pRc->left + pParent->getLeft();
		nrc.top = pRc->top + pParent->getTop();
		nrc.right = pRc->right + pParent->getLeft();
		nrc.bottom = pRc->bottom + pParent->getTop();
	}

	void BaseComponent::getGlobalRect(PRECT npRc)
	{
		npRc->left = pRc->left + pParent->getLeft();
		npRc->top = pRc->top + pParent->getTop();
		npRc->right = pRc->right + pParent->getLeft();
		npRc->bottom = pRc->bottom + pParent->getTop();
	}

	void BaseComponent::getGlobalRect(D2D1_RECT_F* npRc)
	{
		npRc->left = pRc->left + pParent->getLeft();
		npRc->top = pRc->top + pParent->getTop();
		npRc->right = pRc->right + pParent->getLeft();
		npRc->bottom = pRc->bottom + pParent->getTop();
	}

	BOOL BaseComponent::IsValidRect()
	{
		if (
			pRc->left < pRc->right &&
			pRc->top < pRc->bottom &&
			pParent->getLeft() + pRc->right < pParent->getRight() &&
			pParent->getTop() + pRc->bottom < pParent->getBottom() &&
			pRc->left > 0 && pRc->top > 0
			)
			return TRUE;
		return FALSE;
	}

	const BaseOverlay* BaseComponent::getParent() const
	{
		return pParent;
	}

	const BOOL BaseComponent::isInteractive() const
	{
		return interactive;
	}

}