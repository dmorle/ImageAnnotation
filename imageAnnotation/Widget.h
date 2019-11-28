#ifndef WIDGET_H
#define WIDGET_H

#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

#include <vector>

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
	D2D1::ColorF widgetBack;
	D2D1::ColorF passive;
	D2D1::ColorF active;
	D2D1::ColorF text;

	appPalette() :
		background(0.0f, 0.8f, 0.0f),
		widgetBack(0.1f, 0.1f, 0.1f),
		passive(0.2f, 0.2f, 0.2f),
		active(0.4f, 0.4f, 0.4f),
		text(1.0f, 1.0f, 1.0f)
	{}
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
	D2D1_RECT_F rect;
	stdBrushes& brushes;

public:

	Widget(FLOAT left, FLOAT right, FLOAT top, FLOAT bottom, stdBrushes& brushes);
	Widget(D2D1_RECT_F rect, stdBrushes& brushes);

	~Widget();

	void resize(FLOAT left, FLOAT top, FLOAT right, FLOAT bottom);
	void render(ID2D1HwndRenderTarget* pRenderTarget);
};

#endif