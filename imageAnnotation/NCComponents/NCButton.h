#ifndef NCBUTTON_H
#define NCBUTTON_H

#include <Windows.h>
#include <wingdi.h>

enum BUTTONSTATE
{
	PASSIVE,
	ACTIVE,
	PRESSED
};

typedef struct HBRSTRUCT HBRSTRUCT;
struct HBRSTRUCT;

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
	~NCButton();

	void LDown(POINT p);
	void LUp(POINT p);
	void mousemove(POINT p);

	virtual void display(HDC hdc);

protected:
	RECT rc;
	
	void (*onClick)();

	HBRSTRUCT *pBrushes;
	BUTTONSTATE state;

	BOOL contains(POINT p);
};

#endif