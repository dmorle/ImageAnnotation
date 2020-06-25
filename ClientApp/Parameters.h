#ifndef PARAMETERS_H
#define PARAMETERS_H


#include <windows.h>
#include <windowsx.h>
#include <wincodec.h>
#include <d2d1.h>
#include <dwrite.h>
#pragma comment(lib, "d2d1")

#include <wingdi.h>

#include <vector>
#include <string>
#include <string.h>

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

class Panel;
class MainWindow;
class BaseOverlay;
struct GRAPHICSTRUCT;

class Parameters {
public:

	// contains all the colors which will be used by the program
	typedef struct _appPalette
	{
		_appPalette();

		D2D1::ColorF mainBack;
		D2D1::ColorF mainBorder;
		D2D1::ColorF mainText1;
		D2D1::ColorF mainText2;
		D2D1::ColorF mainText3;
		D2D1::ColorF mainCmp1;
		D2D1::ColorF mainCmp2;
		D2D1::ColorF mainCmp3;
		D2D1::ColorF mainActive1;
		D2D1::ColorF mainActive2;
		D2D1::ColorF mainActive3;
		D2D1::ColorF mainPressed;

		D2D1::ColorF widgetBack;
		D2D1::ColorF widgetBorder;
		D2D1::ColorF widgetText1;
		D2D1::ColorF widgetText2;
		D2D1::ColorF widgetText3;
		D2D1::ColorF widgetCmp1;
		D2D1::ColorF widgetCmp2;
		D2D1::ColorF widgetCmp3;
		D2D1::ColorF widgetActive1;
		D2D1::ColorF widgetActive2;
		D2D1::ColorF widgetActive3;
		D2D1::ColorF widgetPressed;

		D2D1::ColorF overlayBack;
		D2D1::ColorF overlayBorder;
		D2D1::ColorF overlayText1;
		D2D1::ColorF overlayText2;
		D2D1::ColorF overlayText3;
		D2D1::ColorF overlayCmp1;
		D2D1::ColorF overlayCmp2;
		D2D1::ColorF overlayCmp3;
		D2D1::ColorF overlayActive1;
		D2D1::ColorF overlayActive2;
		D2D1::ColorF overlayActive3;
		D2D1::ColorF overlayPressed;
	}
	appPalette;

	// Contains all the brushes which will be used by the program
	typedef struct _stdBrushes
	{
		ID2D1SolidColorBrush* mainBack;
		ID2D1SolidColorBrush* mainPredel;
		ID2D1SolidColorBrush* mainBorder;
		ID2D1SolidColorBrush* mainText1;
		ID2D1SolidColorBrush* mainText2;
		ID2D1SolidColorBrush* mainText3;
		ID2D1SolidColorBrush* mainCmp1;
		ID2D1SolidColorBrush* mainCmp2;
		ID2D1SolidColorBrush* mainCmp3;
		ID2D1SolidColorBrush* mainActive1;
		ID2D1SolidColorBrush* mainActive2;
		ID2D1SolidColorBrush* mainActive3;
		ID2D1SolidColorBrush* mainPresel1;
		ID2D1SolidColorBrush* mainPresel2;
		ID2D1SolidColorBrush* mainPresel3;
		ID2D1SolidColorBrush* mainPressed;

		ID2D1SolidColorBrush* widgetBack;
		ID2D1SolidColorBrush* widgetPredel;
		ID2D1SolidColorBrush* widgetBorder;
		ID2D1SolidColorBrush* widgetText1;
		ID2D1SolidColorBrush* widgetText2;
		ID2D1SolidColorBrush* widgetText3;
		ID2D1SolidColorBrush* widgetCmp1;
		ID2D1SolidColorBrush* widgetCmp2;
		ID2D1SolidColorBrush* widgetCmp3;
		ID2D1SolidColorBrush* widgetActive1;
		ID2D1SolidColorBrush* widgetActive2;
		ID2D1SolidColorBrush* widgetActive3;
		ID2D1SolidColorBrush* widgetPresel1;
		ID2D1SolidColorBrush* widgetPresel2;
		ID2D1SolidColorBrush* widgetPresel3;
		ID2D1SolidColorBrush* widgetPressed;

		ID2D1SolidColorBrush* overlayBack;
		ID2D1SolidColorBrush* overlayPredel;
		ID2D1SolidColorBrush* overlayBorder;
		ID2D1SolidColorBrush* overlayText1;
		ID2D1SolidColorBrush* overlayText2;
		ID2D1SolidColorBrush* overlayText3;
		ID2D1SolidColorBrush* overlayCmp1;
		ID2D1SolidColorBrush* overlayCmp2;
		ID2D1SolidColorBrush* overlayCmp3;
		ID2D1SolidColorBrush* overlayActive1;
		ID2D1SolidColorBrush* overlayActive2;
		ID2D1SolidColorBrush* overlayActive3;
		ID2D1SolidColorBrush* overlayPresel1;
		ID2D1SolidColorBrush* overlayPresel2;
		ID2D1SolidColorBrush* overlayPresel3;
		ID2D1SolidColorBrush* overlayPressed;

		_stdBrushes();
		void release();
	}
	stdBrushes;

	// contains all cursors which will be used by the program
	typedef struct _stdCursors
	{
		HCURSOR arrow;
		HCURSOR sizens;
		HCURSOR sizewe;
	}
	stdCursors;

	static HWND hwnd;

	static ID2D1Factory* pFactory;
	static IDWriteFactory* pDWriteFactory;
	static IWICImagingFactory* pWicFactory;
	static ID2D1HwndRenderTarget* pRenderTarget;

	static IDWriteTextFormat* pTextFormat;

	static appPalette* pPalette;
	static stdBrushes* pBrushes;
	static stdCursors* pCursors;

	// pointer to the active panel
	static Panel* pAP;

	// basic panel dimensions
	static const LONG edgeSpace = 2;

	// program flags

	// paint the entire window
	static BOOL fullPaint;
	// MainWindow does not check for window resizing
	static BOOL passMouse;

	// contains the active overlay
	static BaseOverlay *pAO;

	static GRAPHICSTRUCT* pStdGs;
};

static enum BUTTONSTATE
{
	PASSIVE, // The mouse is not over the button
	ACTIVE,  // The mouse is over the button, but the button is not pressed
	PRESSED  // The button has been pressed
};

#endif
