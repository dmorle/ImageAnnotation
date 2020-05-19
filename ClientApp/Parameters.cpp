#include "Parameters.h"



HWND Parameters::hwnd = NULL;

ID2D1Factory* Parameters::pFactory = NULL;
IDWriteFactory* Parameters::pDWriteFactory = NULL;
IWICImagingFactory* Parameters::pWicFactory = NULL;
ID2D1HwndRenderTarget* Parameters::pRenderTarget = NULL;

IDWriteTextFormat* Parameters::pTextFormat = NULL;

Parameters::appPalette* Parameters::pPalette = NULL;
Parameters::stdBrushes* Parameters::pBrushes = NULL;
Parameters::stdCursors* Parameters::pCursors = NULL;

Panel* Parameters::pAP = NULL;

BOOL Parameters::fullPaint = TRUE;
BOOL Parameters::passMouse = FALSE;

BaseOverlay* Parameters::pAO = NULL;

Parameters::_appPalette::_appPalette() :
	background(0.0f, 0.0f, 0.6f),
	widgetBack(0.15f, 0.15f, 0.15f),
	overlayBack(0.1f, 0.1f, 0.1f),
	passive(0.3f, 0.3f, 0.3f),
	active(0.4f, 0.4f, 0.4f),
	text(1.0f, 1.0f, 1.0f)
{}

Parameters::_stdBrushes::_stdBrushes() :
	background(NULL),
	preDeletion(NULL),
	widgetBack(NULL),
	overlayBack(NULL),
	passive(NULL),
	active(NULL),
	text(NULL)
{}

void Parameters::_stdBrushes::release() {
	SafeRelease(&background);
	SafeRelease(&widgetBack);
	SafeRelease(&overlayBack);
	SafeRelease(&passive);
	SafeRelease(&active);
	SafeRelease(&text);
}