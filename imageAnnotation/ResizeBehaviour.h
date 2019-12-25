#ifndef RESIZE_BEHAVIOUR_H
#define RESIZE_BEHAVIOUR_H

#include <windows.h>
#include <windowsx.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#define TOD2DRECTF(rc)  D2D1_RECT_F{ rc.left, rc.top, rc.right, rc.bottom }
#define TORECT(rc)      RECT       { rc.left, rc.top, rc.right, rc.bottom }

#define RESIZE_DEFAULT(pRc, pParent)        new ResizeBehaviour(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, pRc, pParent)
#define RESIZE_FULL(pParent)                new ResizeBehaviour(TRUE , TRUE , TRUE , TRUE , FALSE, FALSE, FALSE, pParent, pParent)
#define RESIZE_STATIC_MARG(pRc, pParent)    new ResizeBehaviour(TRUE , TRUE , TRUE , TRUE , FALSE, FALSE, FALSE, pRc, pParent)

#define RESIZE_STATIC_SIZE_LT(pRc, pParent) new ResizeBehaviour(TRUE , TRUE , FALSE, FALSE, TRUE , TRUE , FALSE, pRc, pParent)
#define RESIZE_STATIC_SIZE_LB(pRc, pParent) new ResizeBehaviour(TRUE , FALSE, FALSE, TRUE , TRUE , TRUE , FALSE, pRc, pParent)
#define RESIZE_STATIC_SIZE_RT(pRc, pParent) new ResizeBehaviour(FALSE, TRUE , TRUE , FALSE, TRUE , TRUE , FALSE, pRc, pParent)
#define RESIZE_STATIC_SIZE_RB(pRc, pParent) new ResizeBehaviour(FALSE, FALSE, TRUE , TRUE , TRUE , TRUE , FALSE, pRc, pParent)

#define RESIZE_STATIC_MARG_LT(pRc, pParent) new ResizeBehaviour(TRUE , TRUE , FALSE, FALSE, FALSE, FALSE, FALSE, pRc, pParent)
#define RESIZE_STATIC_MARG_LB(pRc, pParent) new ResizeBehaviour(TRUE , FALSE, FALSE, TRUE , FALSE, FALSE, FALSE, pRc, pParent)
#define RESIZE_STATIC_MARG_RT(pRc, pParent) new ResizeBehaviour(FALSE, TRUE , TRUE , FALSE, FALSE, FALSE, FALSE, pRc, pParent)
#define RESIZE_STATIC_MARG_RB(pRc, pParent) new ResizeBehaviour(FALSE, FALSE, TRUE , TRUE , FALSE, FALSE, FALSE, pRc, pParent)

#define RESIZE_STATIC_MARG_LR(pRc, pParent) new ResizeBehaviour(TRUE , FALSE, TRUE , FALSE, FALSE, FALSE, FALSE, pRc, pParent)
#define RESIZE_STATIC_MARG_TB(pRc, pParent) new ResizeBehaviour(FALSE, TRUE , FALSE, TRUE , FALSE, FALSE, FALSE, pRc, pParent)

class ResizeBehaviour
{
public:
	ResizeBehaviour(BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, const PRECT, const PRECT);
	ResizeBehaviour(BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, const PRECT, const D2D1_RECT_F*);
	ResizeBehaviour(BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, const D2D1_RECT_F*, const PRECT);
	ResizeBehaviour(BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, const D2D1_RECT_F*, const D2D1_RECT_F*);
	ResizeBehaviour(ResizeBehaviour* pThis);

	void getCmpRect(PRECT npRc, PRECT pRc);
	void getCmpRect(PRECT npRc, D2D1_RECT_F* pRc);
	void getCmpRect(D2D1_RECT_F* npRc, PRECT pRc);
	void getCmpRect(D2D1_RECT_F* npRc, D2D1_RECT_F* pRc);

private:
	/*
		Static size behaviour will override all else
		Static margin behaviour will override aspect ratio and relative scaling
		Static aspect ratio behaviour will override relative scaling
		All other resizing behaviour will be handled using relative scaling
	*/
	BOOL StaticWidth;
	BOOL StaticHeight;

	BOOL StaticLeftMargin;
	BOOL StaticRightMargin;
	BOOL StaticTopMargin;
	BOOL StaticBottomMargin;

	BOOL StaticAspectRatio;

	FLOAT XSize;
	FLOAT YSize;

	FLOAT LMarg;
	FLOAT TMarg;
	FLOAT RMarg;
	FLOAT BMarg;

	FLOAT ARatio;

	FLOAT LProp;
	FLOAT TProp;
	FLOAT RProp;
	FLOAT BProp;
};

#endif