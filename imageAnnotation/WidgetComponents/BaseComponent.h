#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include <windows.h>
#include <windowsx.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "../ResizeBehaviour.h"

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

namespace WCMP {

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