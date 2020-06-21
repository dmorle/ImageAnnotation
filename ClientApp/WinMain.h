#ifndef WINMAIN_H
#define WINMAIN_H

#include "Parameters.h"

#include "basewin.h"
#include "Widgets.h"
#include "Overlays.h"
#include "NCComponents.h"

class MainWindow :
	public BaseWindow<MainWindow>
{
public:

	MainWindow() {}

	PCWSTR  ClassName() const { return L"MainWindow Class"; }
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	typedef struct _resizeInfo {
		enum resizeEdge {
			LEFT,
			TOP,
			RIGHT,
			BOTTOM
		};

		resizeEdge edge;
		LONG edgeDist;
	} resizeInfo;

	LONG left_off = 0;
	LONG top_off = 27;
	LONG right_off = 0;
	LONG bottom_off = 0;

	LONG minNCWidth;

	BOOL        isMax = FALSE;
	resizeInfo* pResizingInfo = NULL;
	Panel*      pMainPanel = NULL;

	std::vector<NCCMP::NCButton*> ncCmp;

	void	savePalette(std::string);
	void	loadPalette(std::string);

	void	CreateDefaultLayout(LONG width, LONG height);

	void	CreateNCButtons();
	void	DiscardNCButtons();
	HRESULT CreateGraphicsResources();
	void    DiscardGraphicsResources();

	LRESULT onCreate();
	void    Paint();
	void    Resize();
	void	MouseMove(WPARAM, LPARAM);
	void	LDown(WPARAM, LPARAM);
	void	LUp(WPARAM, LPARAM);
	void	RDown(WPARAM, LPARAM);
	void	RUp(WPARAM, LPARAM);

	void	ncPaint(WPARAM, LPARAM);
	void	ncMoveMove(WPARAM, LPARAM);
	void	ncLDown(WPARAM, LPARAM);
	void	ncLUp(WPARAM, LPARAM);

	void	RepaintRect(PRECT pRc, BOOL erase = TRUE);
};

#endif
