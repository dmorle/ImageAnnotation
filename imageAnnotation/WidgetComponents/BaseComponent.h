#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include <windows.h>
#include <windowsx.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#ifndef SAFERELEASE
#define SAFERELEASE

template <class T> void SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

#endif

#define TOCOLORREF(c) RGB(c.r * 255, c.g * 255, c.b * 255)

#define TOD2DRECTF(rc)  D2D1_RECT_F{ rc.left, rc.top, rc.right, rc.bottom }
#define TORECT(rc)      RECT       { rc.left, rc.top, rc.right, rc.bottom }

#define RESIZE_DEFAULT(pRc, pParent)     new WCMP::ResizeBehaviour(FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, pRc, pParent)
#define RESIZE_FULL(pParent)            new WCMP::ResizeBehaviour(TRUE , TRUE , TRUE , TRUE , FALSE, FALSE, FALSE, pParent, pParent)
#define RESIZE_STATIC_MARG(pRc, pParent) new WCMP::ResizeBehaviour(TRUE , TRUE , TRUE , TRUE , FALSE, FALSE, FALSE, pRc, pParent)
#define RESIZE_STATIC_SIZE(pRc, pParent) new WCMP::ResizeBehaviour(FALSE, FALSE, FALSE, FALSE, TRUE , TRUE , FALSE, pRc, pParent)

#define RESIZE_STATIC_LT(pRc, pParent)   new WCMP::ResizeBehaviour(TRUE , TRUE , FALSE, FALSE, FALSE, FALSE, FALSE, pRc, pParent)
#define RESIZE_STATIC_LB(pRc, pParent)   new WCMP::ResizeBehaviour(TRUE , FALSE, FALSE, TRUE , FALSE, FALSE, FALSE, pRc, pParent)
#define RESIZE_STATIC_RT(pRc, pParent)   new WCMP::ResizeBehaviour(FALSE, TRUE , TRUE , FALSE, FALSE, FALSE, FALSE, pRc, pParent)
#define RESIZE_STATIC_RB(pRc, pParent)   new WCMP::ResizeBehaviour(FALSE, FALSE, TRUE , TRUE , FALSE, FALSE, FALSE, pRc, pParent)

#define RESIZE_STATIC_LR(pRc, pParent)   new WCMP::ResizeBehaviour(TRUE , FALSE, TRUE , FALSE, FALSE, FALSE, FALSE, pRc, pParent)
#define RESIZE_STATIC_TB(pRc, pParent)   new WCMP::ResizeBehaviour(FALSE, TRUE , FALSE, TRUE , FALSE, FALSE, FALSE, pRc, pParent)

namespace WCMP {

	struct ResizeBehaviour {
		ResizeBehaviour(BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, const D2D1_RECT_F*, const D2D1_RECT_F*);
		ResizeBehaviour(BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, BOOL, const D2D1_RECT_F*, PRECT);
		ResizeBehaviour(ResizeBehaviour* pThis);

		void getCmpRect(D2D1_RECT_F* npRc, D2D1_RECT_F* pRc);
		void getCmpRect(PRECT npRc, D2D1_RECT_F* pRc);

	private:
		/*
			Static size behaviour will override all else
			Static margin behaviour will override aspect ratio and relative scaling
			Static aspect ratio behaviour will override relative scaling
			All other resizing behaviour will be handled using relative scaling
		*/
		BOOL StaticLeftMargin;
		BOOL StaticRightMargin;
		BOOL StaticTopMargin;
		BOOL StaticBottomMargin;

		BOOL StaticWidth;
		BOOL StaticHeight;

		BOOL StaticAspectRatio;

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

	class BaseComponent
	{
	public:
		BaseComponent(D2D1_RECT_F* pRc, PRECT parentpRc, ResizeBehaviour* pRB);
		BaseComponent(BaseComponent* pThis, PRECT npRc);

		virtual ~BaseComponent();

		BOOL contains(POINT p);

		virtual void MouseMove(POINT p) = 0;
		virtual void LDown(POINT p) = 0;
		virtual void LUp(POINT p) = 0;
		virtual void MouseLeave() = 0;

		void resize(PRECT npRc = NULL);
		virtual void display(ID2D1HwndRenderTarget* pRenderTarget) = 0;

		virtual BaseComponent* clone(PRECT nparentpRc) = 0;

	protected:
		D2D1_RECT_F* pRc;
		PRECT parentpRc;

		ResizeBehaviour* pRB;

		void getGlobalRect(RECT& nrc);
		void getGlobalRect(D2D1_RECT_F& nrc);

		void getGlobalRect(PRECT npRc);
		void getGlobalRect(D2D1_RECT_F* npRc);

		BOOL IsValidRect();
	};

	typedef BaseComponent* PBaseComponent;

}

#endif