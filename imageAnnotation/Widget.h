#ifndef WIDGET_H
#define WIDGET_H

#include <vector>
#include <string>
#include <string.h>

#include "WidgetComponents/WidgetCmp.h"
#include "Panel.h"

class MainWindow;

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



class Widget :
	private Panel
{
public:
	Widget(Panel* pParent, PRECT pRc);

	~Widget();

	Widget* operator>>(WCMP::BaseComponent* npCmp);

	void resize(const RECT& rc) override;
	void display() override;

	// actions the user can do
	void MouseMove(const WPARAM& wparam, const POINT& p) override;
	void LDown(const WPARAM& wparam, const POINT& p) override;
	void LUp(const WPARAM& wparam, const POINT& p) override;

private:
	// Contains all widget compoenents for the widget
	std::vector<WCMP::BaseComponent*> cmp;
};

#include "basewin.h"
#include "WinMain.h"

#endif