#ifndef WINMAIN_H
#define WINMAIN_H

#include "basewin.h"
#include "Widget.h"

class MainWindow : public BaseWindow<MainWindow>
{
	ID2D1Factory			*pFactory;
	ID2D1HwndRenderTarget	*pRenderTarget;
	
	appPalette	palette;
	stdBrushes	brushes;

	std::vector<Widget> widgets;

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