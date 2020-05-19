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

class Parameters {
public:

	// contains all the colors which will be used by the program
	typedef struct _appPalette
	{
		_appPalette();

		D2D1::ColorF background;
		D2D1::ColorF widgetBack;
		D2D1::ColorF overlayBack;
		D2D1::ColorF passive;
		D2D1::ColorF active;
		D2D1::ColorF text;
	}
	appPalette;

	// Contains all the brushes which will be used by the program
	typedef struct _stdBrushes
	{
		ID2D1SolidColorBrush* background;
		ID2D1SolidColorBrush* preDeletion;
		ID2D1SolidColorBrush* widgetBack;
		ID2D1SolidColorBrush* overlayBack;
		ID2D1SolidColorBrush* passive;
		ID2D1SolidColorBrush* active;
		ID2D1SolidColorBrush* text;

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
};

#endif
