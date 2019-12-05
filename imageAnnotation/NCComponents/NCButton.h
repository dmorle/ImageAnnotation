#ifndef NCBUTTON_H
#define NCBUTTON_H

#include <Windows.h>
#include <wingdi.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

class MainWindow;

enum BUTTONSTATE
{
	PASSIVE,
	ACTIVE,
	PRESSED
};

typedef struct GRAPHICSTRUCT GRAPHICSTRUCT;
struct GRAPHICSTRUCT {
public:
	GRAPHICSTRUCT(
		COLORREF back,
		COLORREF back_passive,
		COLORREF back_active,
		COLORREF back_pressed,
		COLORREF comp,
		COLORREF comp_passive,
		COLORREF comp_active,
		COLORREF comp_pressed
	);
	~GRAPHICSTRUCT();

	HBRUSH getBack(BUTTONSTATE state);
	COLORREF getComp(BUTTONSTATE state);

private:
	HBRUSH hbr_back;			// default for back of button
	HBRUSH hbr_back_passive;	// color for back of button passively
	HBRUSH hbr_back_active;		// color for back of button when active
	HBRUSH hbr_back_pressed;	// color for back of button when pressed

	COLORREF crf_comp;			// default for button colors
	COLORREF crf_comp_passive;	// color for components passively
	COLORREF crf_comp_active;	// color for components when active
	COLORREF crf_comp_pressed;	// color for components when pressed
};

class NCButton
{
public:
	NCButton(
		COLORREF back,
		COLORREF back_passive,
		COLORREF back_active,
		COLORREF back_pressed,
		COLORREF comp,
		COLORREF comp_passive,
		COLORREF comp_active,
		COLORREF comp_pressed,
		void (*onClick)()
	);
	NCButton(
		COLORREF back_passive,
		COLORREF back_active,
		COLORREF back_pressed,
		COLORREF comp_passive,
		COLORREF comp_active,
		COLORREF comp_pressed,
		void (*onClick)()
	);
	virtual ~NCButton();

	void LDown(POINT p);
	void LUp(POINT p);
	void mousemove(POINT p);

	virtual void display(HDC hdc);

protected:
	RECT rc;
	
	void (*onClick)();

	GRAPHICSTRUCT *pAssets;
	BUTTONSTATE state;

	BOOL contains(POINT p);
};

#endif