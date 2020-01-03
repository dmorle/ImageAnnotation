#ifndef CONTAINER_H
#define CONTAINER_H

#ifndef WIDGETS_H
#include "Panel.h"
#endif

class Container :
	public Panel
{
public:
	Container(Panel* pParent, PRECT npRc);

	~Container();

	// append this->cmp (The components of the panel)
	void addPanel(Panel* npPanel);

	void MouseMove(const WPARAM& wparam, const POINT& p) override;
	void LDown(const WPARAM& wparam, const POINT& p) override;
	void LUp(const WPARAM& wparam, const POINT& p) override;

	void resizeX(LONG left, LONG right) override;
	void resizeY(LONG top, LONG bottom) override;

	void widgetEdit(WidgetPanel* pWidget) override;

	void display() override;

	// maximum of all child->pMal if this->pMal is 0
	BYTE getPanelMaliability() override;

private:
	enum class PANEL_ORIENTATION {
		NONE,
		VERTICAL,
		HORIZONTAL
	};

	typedef struct _resizeInfo {
		Panel* p1;
		Panel* p2;
	} resizeInfo, *pResizeInfo;

	// the orintation of component panels
	PANEL_ORIENTATION orientation;

	// contains all child components of the panel
	std::vector<Panel*> cmp;

	// flags for how to handle user inputs
	static pResizeInfo pResizingInfo;
	static BOOL f_widgetEdit;
};

#endif