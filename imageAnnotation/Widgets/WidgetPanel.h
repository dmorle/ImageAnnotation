#ifndef WIDGETPANEL_H
#define WIDGETPANEL_H

#ifndef WIDGETS_H
#include "Panel.h"
#endif

class WidgetPanel :
	public Panel
{
public:
	WidgetPanel(Panel* pParent, PRECT pRc, BYTE pMal);

	~WidgetPanel();

	WidgetPanel* operator>>(WCMP::BaseComponent* npCmp);

	// actions the user can do
	void MouseMove(const WPARAM& wparam, const POINT& p) override;
	void LDown(const WPARAM& wparam, const POINT& p) override;
	void LUp(const WPARAM& wparam, const POINT& p) override;

	void resizeX(LONG left, LONG right);
	void resizeY(LONG top, LONG bottom);

	void widgetEdit(WidgetPanel* pWidget) override;

	void display() override;

	BYTE getPanelMaliability() override;

private:
	// Contains all widget compoenents for the widget
	std::vector<WCMP::BaseComponent*> cmp;
};

#endif