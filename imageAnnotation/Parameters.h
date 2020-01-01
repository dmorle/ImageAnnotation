#ifndef PARAMETERS_H
#define PARAMETERS_H

namespace {
	// private structures / logic
	struct _appPalette
	{
		typedef int PALETTE_COLOR;

		enum {
			BACKGROUND,
			WIDGET_BACK,
			PASSIVE,
			ACTIVE,
			TEXT_COLOR
		};

		_appPalette() :
			background(0.0f, 0.0f, 0.6f),
			widgetBack(0.15f, 0.15f, 0.15f),
			passive(0.3f, 0.3f, 0.3f),
			active(0.4f, 0.4f, 0.4f),
			text(1.0f, 1.0f, 1.0f)
		{}

		D2D1::ColorF& operator [](PALETTE_COLOR arg)
		{
			switch (arg) {
			case BACKGROUND:
				return background;
			case WIDGET_BACK:
				return widgetBack;
			case PASSIVE:
				return passive;
			case ACTIVE:
				return active;
			case TEXT_COLOR:
				return text;
			}
		}

	private:

		D2D1::ColorF background;
		D2D1::ColorF widgetBack;
		D2D1::ColorF passive;
		D2D1::ColorF active;
		D2D1::ColorF text;

	};

	struct _stdBrushes
	{
		ID2D1SolidColorBrush* background;
		ID2D1SolidColorBrush* preDeletion;
		ID2D1SolidColorBrush* widgetBack;
		ID2D1SolidColorBrush* passive;
		ID2D1SolidColorBrush* active;
		ID2D1SolidColorBrush* text;

		_stdBrushes() :
			background(NULL),
			preDeletion(NULL),
			widgetBack(NULL),
			passive(NULL),
			active(NULL),
			text(NULL)
		{}

		void release() {
			SafeRelease(&background);
			SafeRelease(&widgetBack);
			SafeRelease(&passive);
			SafeRelease(&active);
			SafeRelease(&text);
		}
	};

	struct _stdCursors
	{
		HCURSOR arrow;
		HCURSOR sizens;
		HCURSOR sizewe;
	};
}

typedef struct _appPalette appPalette;   // contains all the colors which will be used by the program
typedef struct _stdBrushes stdBrushes;   // Contains all the brushes which will be used by the program
typedef struct _stdCursors stdCursors;   // contains all cursors which will be used by the program

stdBrushes noBrushes; // NULL brush

ID2D1Factory* pFactory;
IWICImagingFactory* pWicFactory;
ID2D1HwndRenderTarget* pRenderTarget;

appPalette palette;
stdBrushes brushes;
stdCursors cursors;

// pointer to the active panel
Panel* pAP;

// basic widget dimensions
FLOAT edgeSpace = 2;
FLOAT minSize = edgeSpace * 12;

#include "WinMain.h"

#endif