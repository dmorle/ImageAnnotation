#ifndef WINMAIN_H
#define WINMAIN_H

#include "Widget.h"
#include "NCComponents/NCCmp.h"

class MainWindow : public BaseWindow<MainWindow>
{
	LONG left_off = 0;
	LONG top_off = 27;
	LONG right_off = 0;
	LONG bottom_off = 0;

	BOOL isMax = FALSE;

	Panel* cPanel;

	std::vector<NCCMP::NCButton*> ncComponents;

	void	savePalette(std::string);
	void	loadPalette(std::string);

	void	CreateDefaultLayout(D2D1_SIZE_F size);

	void    CalculateLayout();
	void	CreateNCButtons();
	void	DiscardNCButtons();
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
	void	ncMoveMove(WPARAM, LPARAM);
	void	ncLUp(WPARAM, LPARAM);
	void	ncLDown(WPARAM, LPARAM);

	void	RepaintRect(PRECT pRc, BOOL erase = TRUE);

public:

	MainWindow() : pFactory(NULL), pRenderTarget(NULL) {}

	PCWSTR  ClassName() const { return L"MainWindow Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

#endif