#ifndef CONTAINER_H
#define CONTAINER_H

#include "Panel.h"

class Container :
	public Panel
{
public:
	~Container();

	// append this->cmp (The components of the panel)
	BOOL addPanel(Panel* npPanel);

	void MouseMove(const WPARAM& wparam, const POINT& p) override;
	void LDown(const WPARAM& wparam, const POINT& p) override;
	void LUp(const WPARAM& wparam, const POINT& p) override;

	void resizeX(LONG left, LONG right) override;
	void resizeY(LONG top, LONG bottom) override;

	void display() override;

	// maximum of all child->pMal if this->pMal is 0
	BYTE getPanelMaliability() override;

private:
	enum class PANEL_ORIENTATION {
		NONE,
		VERTICAL,
		HORIZONTAL
	};

	typedef struct {
		Panel* p1;
		Panel* p2;
	}_resizeInfo, *_pResizeInfo;

	// the orintation of component panels
	PANEL_ORIENTATION orientation;

	// contains all child components of the panel
	std::vector<Panel*> cmp;
	
	void m_MouseMove(const WPARAM& wparam, const POINT& p);
	void m_LDown(const WPARAM& wparam, const POINT& p);
	void m_LUp(const WPARAM& wparam, const POINT& p);

	// flags for how to handle user inputs
	static _pResizeInfo pResizingInfo;
	static BOOL f_widgetEdit;
};

#endif