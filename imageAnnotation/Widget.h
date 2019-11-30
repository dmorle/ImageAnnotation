#ifndef WIDGET_H
#define WIDGET_H

#include <windows.h>
#include <windowsx.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include <vector>
#include <string>
#include <string.h>

const static std::vector<std::string> appColors
{
	"background",
	"widgetBack",
	"passive",
	"active",
	"text"
};

class MainWindow;

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
	typedef int PALETTE_COLOR;

	enum {
		BACKGROUND,
		WIDGET_BACK,
		PASSIVE,
		ACTIVE,
		TEXT
	};

	appPalette() :
		background(0.0f, 0.8f, 0.0f),
		widgetBack(0.1f, 0.1f, 0.1f),
		passive(0.2f, 0.2f, 0.2f),
		active(0.4f, 0.4f, 0.4f),
		text(1.0f, 1.0f, 1.0f)
	{}

	D2D1::ColorF& operator [](std::string arg)
	{
		for (int i = 0; i < appColors.size(); i++)
			if (arg == appColors[i])
				return (*this)[i];
	}

	D2D1::ColorF& operator [](const char* arg)
	{
		for (int i = 0; i < appColors.size(); i++)
			if (!strcmp(arg, appColors[i].c_str()))
				return (*this)[i];
	}

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
		case TEXT:
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

typedef struct stdBrushes basicBrushes;
struct stdBrushes
{
	ID2D1SolidColorBrush* background;
	ID2D1SolidColorBrush* widgetBack;
	ID2D1SolidColorBrush* passive;
	ID2D1SolidColorBrush* active;
	ID2D1SolidColorBrush* text;

	stdBrushes() :
		background(NULL),
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

static stdBrushes noBrushes;

class Widget
{
	HWND hwnd;
	MainWindow* mw;

	RECT rect;
	stdBrushes& brushes;
	FLOAT edgeSpace = 2;

	BOOL dupStart = FALSE;
	FLOAT minSize = edgeSpace * 12;
	Widget* npWidget = NULL;

public:
	Widget(HWND hwnd, LONG left, LONG right, LONG top, LONG bottom, stdBrushes& brushes, MainWindow* mw);
	Widget(HWND hwnd, RECT rect, stdBrushes& brushes, MainWindow* mw);

	~Widget();

	void resize(LONG left, LONG top, LONG right, LONG bottom);
	void render(ID2D1HwndRenderTarget* pRenderTarget);

	Widget* MouseMove(WPARAM& wparam, POINT& p);
	Widget* LUp(WPARAM& wparam, POINT& p, MainWindow *mw);
	Widget* LDown(WPARAM& wparam, POINT& p);

	BOOL contains(POINT p);
};

#include "basewin.h"
#include "WinMain.h"

#endif