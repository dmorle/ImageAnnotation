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

typedef struct appPalette appPalette;
struct appPalette
{
	D2D1::ColorF background;
	D2D1::ColorF passive;
	D2D1::ColorF active;
	D2D1::ColorF text;

	appPalette() :
		background(0.0f, 0.8f, 0.0f),
		passive(0.2f, 0.2f, 0.2f),
		active(0.4f, 0.4f, 0.4f),
		text(1.0f, 1.0f, 1.0f)
	{}
};

class MainWindow : public BaseWindow<MainWindow>
{
	ID2D1Factory			*pFactory;
	ID2D1HwndRenderTarget	*pRenderTarget;
	ID2D1SolidColorBrush	*pBrush;

	appPalette	palette;

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

	MainWindow() : pFactory(NULL), pRenderTarget(NULL), pBrush(NULL) {}

	PCWSTR  ClassName() const { return L"Circle Window Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif