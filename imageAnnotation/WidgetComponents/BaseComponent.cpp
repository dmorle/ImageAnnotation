#include "BaseComponent.h"



namespace WCMP {

	ResizeBehaviour::ResizeBehaviour(
		BOOL StaticLeftMargin,
		BOOL StaticRightMargin,
		BOOL StaticTopMargin,
		BOOL StaticBottomMargin,
		BOOL StaticWidth,
		BOOL StaticHeight,
		BOOL StaticAspectRatio,
		const D2D1_RECT_F* rc,
		const D2D1_RECT_F* parentRc
	)
	{
		this->StaticLeftMargin   = StaticLeftMargin;
		this->StaticRightMargin  = StaticRightMargin;
		this->StaticTopMargin    = StaticTopMargin;
		this->StaticBottomMargin = StaticBottomMargin;
		this->StaticWidth        = StaticWidth;
		this->StaticHeight       = StaticHeight;
		this->StaticAspectRatio  = StaticAspectRatio;

		D2D1_SIZE_F parentRcSize{ parentRc->right - parentRc->left, parentRc->bottom - parentRc->top };
		D2D1_SIZE_F rcSize{ rc->right - rc->left, rc->bottom - rc->top };

		LMarg = parentRc->left - rc->left;
		TMarg = parentRc->top - rc->top;
		RMarg = rc->right - parentRc->right;
		BMarg = rc->bottom - parentRc->bottom;

		ARatio = rcSize.width / rcSize.height;

		LProp = LMarg / parentRcSize.width;
		TProp = TMarg / parentRcSize.height;
		RProp = RMarg / parentRcSize.width;
		BProp = BMarg / parentRcSize.height;
	}

	ResizeBehaviour::ResizeBehaviour(
		BOOL StaticLeftMargin,
		BOOL StaticRightMargin,
		BOOL StaticTopMargin,
		BOOL StaticBottomMargin,
		BOOL StaticWidth,
		BOOL StaticHeight,
		BOOL StaticAspectRatio,
		const D2D1_RECT_F* rc,
		const PRECT parentRc
	)
	{
		this->StaticLeftMargin = StaticLeftMargin;
		this->StaticRightMargin = StaticRightMargin;
		this->StaticTopMargin = StaticTopMargin;
		this->StaticBottomMargin = StaticBottomMargin;
		this->StaticWidth = StaticWidth;
		this->StaticHeight = StaticHeight;
		this->StaticAspectRatio = StaticAspectRatio;

		D2D1_SIZE_F parentRcSize{ parentRc->right - parentRc->left, parentRc->bottom - parentRc->top };
		D2D1_SIZE_F rcSize{ rc->right - rc->left, rc->bottom - rc->top };

		LMarg = parentRc->left - rc->left;
		TMarg = parentRc->top - rc->top;
		RMarg = rc->right - parentRc->right;
		BMarg = rc->bottom - parentRc->bottom;

		ARatio = rcSize.width / rcSize.height;

		LProp = LMarg / parentRcSize.width;
		TProp = TMarg / parentRcSize.height;
		RProp = RMarg / parentRcSize.width;
		BProp = BMarg / parentRcSize.height;
	}

	ResizeBehaviour::ResizeBehaviour(ResizeBehaviour* pThis)
	{
		StaticLeftMargin = pThis->StaticLeftMargin;
		StaticRightMargin = pThis->StaticRightMargin;
		StaticTopMargin = pThis->StaticTopMargin;
		StaticBottomMargin = pThis->StaticBottomMargin;
		StaticWidth = pThis->StaticWidth;
		StaticHeight = pThis->StaticHeight;
		StaticAspectRatio = pThis->StaticAspectRatio;
		LMarg = pThis->LMarg;
		TMarg = pThis->TMarg;
		RMarg = pThis->RMarg;
		BMarg = pThis->BMarg;
		ARatio = pThis->ARatio;
		LProp = pThis->LProp;
		TProp = pThis->TProp;
		RProp = pThis->RProp;
		BProp = pThis->BProp;
	}

	void ResizeBehaviour::getCmpRect(D2D1_RECT_F* npRc, D2D1_RECT_F* pRc)
	{
		if (!StaticWidth && !StaticHeight) { // Static margin or aspect ratio behaviour
			D2D1_SIZE_F nRcSize{ npRc->right - npRc->left, npRc->bottom - npRc->top };

			if (!StaticLeftMargin)
				pRc->left = nRcSize.width * LProp;

			if (!StaticTopMargin)
				pRc->top = nRcSize.height * TProp;

			if (StaticRightMargin)
				pRc->right = nRcSize.width - RMarg;
			else
				pRc->right = nRcSize.width - nRcSize.width * RProp;

			if (StaticBottomMargin)
				pRc->bottom = nRcSize.height - BMarg;
			else
				pRc->bottom = nRcSize.height - nRcSize.height * BProp;

			if (StaticAspectRatio) {
				FLOAT h = pRc->bottom - pRc->top;
				FLOAT w = pRc->right - pRc->left;
				if (w / h > 1) {
					// scale down width
					FLOAT d = w - ARatio * h;
					if (StaticTopMargin ^ StaticBottomMargin) {
						// ignore margins
						FLOAT total = LProp + RProp;
						pRc->left += d * LProp / total;
						pRc->right -= d * RProp / total;
					}
					else if (StaticTopMargin) {
						// only move pRc->bottom
						pRc->bottom -= d;
					}
					else {
						// only move pRc->top
						pRc->top += d;
					}
				}
				else {
					// scale down height
					FLOAT d = h - w / ARatio;
					if (StaticTopMargin ^ StaticBottomMargin) {
						// ignore margins
						FLOAT total = TProp + BProp;
						pRc->top += d * TProp / total;
						pRc->bottom -= d * BProp / total;
					}
					else if (StaticTopMargin) {
						// only move pRc->bottom
						pRc->bottom -= d;
					}
					else {
						// only move pRc->top
						pRc->top += d;
					}
				}
			}
		}
		else if (StaticWidth) {
			if (StaticTopMargin || StaticBottomMargin) {
				if (StaticTopMargin)
					// relative scaling for bottom margin
					pRc->bottom = (npRc->bottom - npRc->top) * (1 - BProp);
				else
					// relative scaling for top margin
					pRc->top = (npRc->bottom - npRc->top) * TProp;
			}
			else if (!StaticAspectRatio) {
				// relative scaling
				FLOAT h = npRc->bottom - npRc->top;
				pRc->top = h * TProp;
				pRc->bottom = h - h * BProp;
			}
		}
		else if (StaticHeight) {
			if (StaticLeftMargin || StaticRightMargin) {
				if (StaticLeftMargin)
					// relative scaling for right margin
					pRc->right = (npRc->right - npRc->left) * (1 - RProp);
				else
					// relative scaling for left margin
					pRc->left = (npRc->right - npRc->left) * LProp;
			}
			else if (!StaticAspectRatio) {
				// relative scaling
				FLOAT w = npRc->right - npRc->left;
				pRc->left = w * LProp;
				pRc->right = w - w * RProp;
			}
		}
	}

	void ResizeBehaviour::getCmpRect(PRECT npRc, D2D1_RECT_F* pRc)
	{
		if (!StaticWidth && !StaticHeight) { // Static margin or aspect ratio behaviour
			D2D1_SIZE_F nRcSize{ npRc->right - npRc->left, npRc->bottom - npRc->top };

			if (!StaticLeftMargin)
				pRc->left = nRcSize.width * LProp;

			if (!StaticTopMargin)
				pRc->top = nRcSize.height * TProp;

			if (StaticRightMargin)
				pRc->right = nRcSize.width - RMarg;
			else
				pRc->right = nRcSize.width - nRcSize.width * RProp;

			if (StaticBottomMargin)
				pRc->bottom = nRcSize.height - BMarg;
			else
				pRc->bottom = nRcSize.height - nRcSize.height * BProp;

			if (StaticAspectRatio) {
				FLOAT h = pRc->bottom - pRc->top;
				FLOAT w = pRc->right - pRc->left;
				if (w / h > 1) {
					// scale down width
					FLOAT d = w - ARatio * h;
					if (StaticTopMargin ^ StaticBottomMargin) {
						// ignore margins
						FLOAT total = LProp + RProp;
						pRc->left += d * LProp / total;
						pRc->right -= d * RProp / total;
					}
					else if (StaticTopMargin) {
						// only move pRc->bottom
						pRc->bottom -= d;
					}
					else {
						// only move pRc->top
						pRc->top += d;
					}
				}
				else {
					// scale down height
					FLOAT d = h - w / ARatio;
					if (StaticTopMargin ^ StaticBottomMargin) {
						// ignore margins
						FLOAT total = TProp + BProp;
						pRc->top += d * TProp / total;
						pRc->bottom -= d * BProp / total;
					}
					else if (StaticTopMargin) {
						// only move pRc->bottom
						pRc->bottom -= d;
					}
					else {
						// only move pRc->top
						pRc->top += d;
					}
				}
			}
		}
		else if (StaticWidth) {
			if (StaticTopMargin || StaticBottomMargin) {
				if (StaticTopMargin)
					// relative scaling for bottom margin
					pRc->bottom = (npRc->bottom - npRc->top) * (1 - BProp);
				else
					// relative scaling for top margin
					pRc->top = (npRc->bottom - npRc->top) * TProp;
			}
			else if (!StaticAspectRatio) {
				// relative scaling
				FLOAT h = npRc->bottom - npRc->top;
				pRc->top = h * TProp;
				pRc->bottom = h - h * BProp;
			}
		}
		else if (StaticHeight) {
			if (StaticLeftMargin || StaticRightMargin) {
				if (StaticLeftMargin)
					// relative scaling for right margin
					pRc->right = (npRc->right - npRc->left) * (1 - RProp);
				else
					// relative scaling for left margin
					pRc->left = (npRc->right - npRc->left) * LProp;
			}
			else if (!StaticAspectRatio) {
				// relative scaling
				FLOAT w = npRc->right - npRc->left;
				pRc->left = w * LProp;
				pRc->right = w - w * RProp;
			}
		}
	}

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