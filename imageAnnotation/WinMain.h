#ifndef WINMAIN_H
#define WINMAIN_H

#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include "basewin.h"

template <class T> void SafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}

class MainWindow : public BaseWindow<MainWindow>
{
	ID2D1Factory* pFactory;
	ID2D1HwndRenderTarget* pRenderTarget;
	ID2D1SolidColorBrush* pBrush;
	D2D1_ELLIPSE            ellipse;

	void    CalculateLayout();
	HRESULT CreateGraphicsResources();
	void    DiscardGraphicsResources();
	void    Paint();
	void    Resize();
	void	MouseMove();
	void	LUp();
	void	LDown();
	void	RUp();
	void	RDown();

public:

	MainWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL)
	{
	}

	PCWSTR  ClassName() const { return L"Circle Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif