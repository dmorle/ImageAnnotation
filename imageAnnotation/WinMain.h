#ifndef WINMAIN_H
#define WINMAIN_H

#include "Widget.h"

class MainWindow : public BaseWindow<MainWindow>
{
	friend class Widget;

	ID2D1Factory			*pFactory;
	ID2D1HwndRenderTarget	*pRenderTarget;
	
	appPalette	palette;
	stdBrushes	brushes;
	stdCursors	cursors;

	std::vector<Widget*> widgets;
	Widget* activeWidget = NULL;

	void	savePalette(std::string);
	void	loadPalette(std::string);

	void    CalculateLayout(D2D1_SIZE_F prev);
	HRESULT CreateGraphicsResources();
	void    DiscardGraphicsResources();

	void    Paint();
	void    Resize();
	void	MouseMove(WPARAM, LPARAM);
	void	MouseLeave(WPARAM, LPARAM);
	void	LUp(WPARAM, LPARAM);
	void	LDown(WPARAM, LPARAM);
	void	RUp(WPARAM, LPARAM);
	void	RDown(WPARAM, LPARAM);
	void	ncPaint(WPARAM, LPARAM);

	void	createDefaultLayout();

public:

	MainWindow() : pFactory(NULL), pRenderTarget(NULL) {}

	PCWSTR  ClassName() const { return L"MainWindow Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif