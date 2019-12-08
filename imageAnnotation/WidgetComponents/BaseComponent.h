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

class BaseComponent
{
public:
	~BaseComponent();

	BOOL contains(POINT p);

	virtual void MouseMove(POINT p) = 0;
	virtual void LDown(POINT p) = 0;
	virtual void LUp(POINT p) = 0;
	virtual void MouseLeave() = 0;

	virtual void display(ID2D1HwndRenderTarget* pRenderTarget) = 0;

protected:
	PRECT pRc;
};

typedef BaseComponent* PBaseComponent;

#endif