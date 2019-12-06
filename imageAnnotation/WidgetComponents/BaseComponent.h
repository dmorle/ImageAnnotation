#ifndef BASECOMPONENT_H
#define BASECOMPONENT_H

#include <windows.h>
#include <windowsx.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

class BaseComponent
{
public:
	BOOL contains(POINT p);

protected:
	RECT rc;

	virtual void display(ID2D1HwndRenderTarget* pRenderTarget) = 0;
};

#endif