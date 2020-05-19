#include "WResizable.h"



Resizable::Resizable(
	BOOL StaticLeftMargin,
	BOOL StaticRightMargin,
	BOOL StaticTopMargin,
	BOOL StaticBottomMargin,
	BOOL StaticWidth,
	BOOL StaticHeight,
	BOOL StaticAspectRatio,
	const PRECT rc,
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

	XSize = rc->right - rc->left;
	YSize = rc->bottom - rc->top;

	LMarg = parentRc->left - rc->left;
	TMarg = parentRc->top - rc->top;
	RMarg = rc->right - parentRc->right;
	BMarg = rc->bottom - parentRc->bottom;

	ARatio = XSize / YSize;

	LProp = LMarg / parentRcSize.width;
	TProp = TMarg / parentRcSize.height;
	RProp = RMarg / parentRcSize.width;
	BProp = BMarg / parentRcSize.height;
}

Resizable::Resizable(
	BOOL StaticLeftMargin,
	BOOL StaticRightMargin,
	BOOL StaticTopMargin,
	BOOL StaticBottomMargin,
	BOOL StaticWidth,
	BOOL StaticHeight,
	BOOL StaticAspectRatio,
	const PRECT rc,
	const D2D1_RECT_F* parentRc
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

	XSize = rc->right - rc->left;
	YSize = rc->bottom - rc->top;

	LMarg = parentRc->left - rc->left;
	TMarg = parentRc->top - rc->top;
	RMarg = rc->right - parentRc->right;
	BMarg = rc->bottom - parentRc->bottom;

	ARatio = XSize / YSize;

	LProp = LMarg / parentRcSize.width;
	TProp = TMarg / parentRcSize.height;
	RProp = RMarg / parentRcSize.width;
	BProp = BMarg / parentRcSize.height;
}

Resizable::Resizable(
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

	XSize = rc->right - rc->left;
	YSize = rc->bottom - rc->top;

	LMarg = parentRc->left - rc->left;
	TMarg = parentRc->top - rc->top;
	RMarg = rc->right - parentRc->right;
	BMarg = rc->bottom - parentRc->bottom;

	ARatio = XSize / YSize;

	LProp = LMarg / parentRcSize.width;
	TProp = TMarg / parentRcSize.height;
	RProp = RMarg / parentRcSize.width;
	BProp = BMarg / parentRcSize.height;
}

Resizable::Resizable(
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
	this->StaticLeftMargin = StaticLeftMargin;
	this->StaticRightMargin = StaticRightMargin;
	this->StaticTopMargin = StaticTopMargin;
	this->StaticBottomMargin = StaticBottomMargin;
	this->StaticWidth = StaticWidth;
	this->StaticHeight = StaticHeight;
	this->StaticAspectRatio = StaticAspectRatio;

	D2D1_SIZE_F parentRcSize{ parentRc->right - parentRc->left, parentRc->bottom - parentRc->top };

	XSize = rc->right - rc->left;
	YSize = rc->bottom - rc->top;

	LMarg = parentRc->left - rc->left;
	TMarg = parentRc->top - rc->top;
	RMarg = rc->right - parentRc->right;
	BMarg = rc->bottom - parentRc->bottom;

	ARatio = XSize / YSize;

	LProp = LMarg / parentRcSize.width;
	TProp = TMarg / parentRcSize.height;
	RProp = RMarg / parentRcSize.width;
	BProp = BMarg / parentRcSize.height;
}

Resizable::Resizable(Resizable* pThis)
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

void Resizable::getCmpRect(PRECT npRc, PRECT pRc)
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
	else {
		if (StaticLeftMargin) {
			if (StaticLeftMargin ^ StaticRightMargin) {
				if (StaticRightMargin) {
					// translate horizontally such that the right margin remains constant
					pRc->left = pRc->right - XSize;
					pRc->right = npRc->right - RMarg;
				}
			}
			else {
				// translate horizontally such that the midpoint remain proportional
				FLOAT s2 =  XSize / 2;
				FLOAT w1 = npRc->right - npRc->left;
				FLOAT m1 = w1 * LProp * (1 + s2 / LMarg);
				pRc->left = m1 - s2;
				pRc->right = w1 - m1 - s2;
			}

			if (StaticTopMargin ^ StaticBottomMargin) {
				if (StaticBottomMargin) {
					// translate vertically such that the bottom margin remains constant
					pRc->top = pRc->bottom - YSize;
					pRc->bottom = npRc->bottom - BMarg;
				}
			}
			else {
				// translate vertically such that the midpoint remain proportional
				FLOAT s2 = YSize / 2;
				FLOAT h1 = npRc->bottom - npRc->top;
				FLOAT m1 = h1 * TProp * (1 + s2 / TMarg);
				pRc->top = m1 - s2;
				pRc->bottom = h1 - m1 - s2;
			}
		}
	}
}

void Resizable::getCmpRect(PRECT npRc, D2D1_RECT_F* pRc)
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
	else {
		if (StaticLeftMargin) {
			if (StaticLeftMargin ^ StaticRightMargin) {
				if (StaticRightMargin) {
					// translate horizontally such that the right margin remains constant
					pRc->left = pRc->right - XSize;
					pRc->right = npRc->right - RMarg;
				}
			}
			else {
				// translate horizontally such that the midpoint remain proportional
				FLOAT s2 = XSize / 2;
				FLOAT w1 = npRc->right - npRc->left;
				FLOAT m1 = w1 * LProp * (1 + s2 / LMarg);
				pRc->left = m1 - s2;
				pRc->right = w1 - m1 - s2;
			}

			if (StaticTopMargin ^ StaticBottomMargin) {
				if (StaticBottomMargin) {
					// translate vertically such that the bottom margin remains constant
					pRc->top = pRc->bottom - YSize;
					pRc->bottom = npRc->bottom - BMarg;
				}
			}
			else {
				// translate vertically such that the midpoint remain proportional
				FLOAT s2 = YSize / 2;
				FLOAT h1 = npRc->bottom - npRc->top;
				FLOAT m1 = h1 * TProp * (1 + s2 / TMarg);
				pRc->top = m1 - s2;
				pRc->bottom = h1 - m1 - s2;
			}
		}
	}
}

void Resizable::getCmpRect(D2D1_RECT_F* npRc, PRECT pRc)
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
	else {
		if (StaticLeftMargin) {
			if (StaticLeftMargin ^ StaticRightMargin) {
				if (StaticRightMargin) {
					// translate horizontally such that the right margin remains constant
					pRc->left = pRc->right - XSize;
					pRc->right = npRc->right - RMarg;
				}
			}
			else {
				// translate horizontally such that the midpoint remain proportional
				FLOAT s2 = XSize / 2;
				FLOAT w1 = npRc->right - npRc->left;
				FLOAT m1 = w1 * LProp * (1 + s2 / LMarg);
				pRc->left = m1 - s2;
				pRc->right = w1 - m1 - s2;
			}

			if (StaticTopMargin ^ StaticBottomMargin) {
				if (StaticBottomMargin) {
					// translate vertically such that the bottom margin remains constant
					pRc->top = pRc->bottom - YSize;
					pRc->bottom = npRc->bottom - BMarg;
				}
			}
			else {
				// translate vertically such that the midpoint remain proportional
				FLOAT s2 = YSize / 2;
				FLOAT h1 = npRc->bottom - npRc->top;
				FLOAT m1 = h1 * TProp * (1 + s2 / TMarg);
				pRc->top = m1 - s2;
				pRc->bottom = h1 - m1 - s2;
			}
		}
	}
}

void Resizable::getCmpRect(D2D1_RECT_F* npRc, D2D1_RECT_F* pRc)
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
	else {
		if (StaticLeftMargin) {
			if (StaticLeftMargin ^ StaticRightMargin) {
				if (StaticRightMargin) {
					// translate horizontally such that the right margin remains constant
					pRc->left = pRc->right - XSize;
					pRc->right = npRc->right - RMarg;
				}
			}
			else {
				// translate horizontally such that the midpoint remain proportional
				FLOAT s2 = XSize / 2;
				FLOAT w1 = npRc->right - npRc->left;
				FLOAT m1 = w1 * LProp * (1 + s2 / LMarg);
				pRc->left = m1 - s2;
				pRc->right = w1 - m1 - s2;
			}

			if (StaticTopMargin ^ StaticBottomMargin) {
				if (StaticBottomMargin) {
					// translate vertically such that the bottom margin remains constant
					pRc->top = pRc->bottom - YSize;
					pRc->bottom = npRc->bottom - BMarg;
				}
			}
			else {
				// translate vertically such that the midpoint remain proportional
				FLOAT s2 = YSize / 2;
				FLOAT h1 = npRc->bottom - npRc->top;
				FLOAT m1 = h1 * TProp * (1 + s2 / TMarg);
				pRc->top = m1 - s2;
				pRc->bottom = h1 - m1 - s2;
			}
		}
	}
}