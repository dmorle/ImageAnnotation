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
	/*
	
	This structure does not use dynamic memory allocation => deconstructor not nessisary

	*/
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

typedef struct basicBrushes basicBrushes;
struct basicBrushes
{
	ID2D1SolidColorBrush* background;
	ID2D1SolidColorBrush* passive;
	ID2D1SolidColorBrush* active;
	ID2D1SolidColorBrush* text;

	basicBrushes() :
		background(NULL),
		passive(NULL),
		active(NULL),
		text(NULL)
	{}

	~basicBrushes() {
		SafeRelease(&background);
		SafeRelease(&passive);
		SafeRelease(&active);
		SafeRelease(&text);
	}

	static basicBrushes none;
};

class MainWindow : public BaseWindow<MainWindow>
{
	ID2D1Factory			*pFactory;
	ID2D1HwndRenderTarget	*pRenderTarget;
	
	appPalette		palette;
	basicBrushes	brushes;

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

	MainWindow() : pFactory(NULL), pRenderTarget(NULL) {}

	PCWSTR  ClassName() const { return L"MainWindow Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif