#ifndef CMP_OVERLAY_H
#define CMP_OVERLAY_H

#include "BaseOverlay.h"

class CmpOverlay :
	virtual public BaseOverlay
{
public:
	virtual ~CmpOverlay();

	// user actions

	virtual void MouseMove(const WPARAM& wparam, const POINT& p) override;
	virtual void LDown(const WPARAM& wparam, const POINT& p) override;
	virtual void LUp(const WPARAM& wparam, const POINT& p) override;

	// displays the overlay to the screen
	virtual void display() override;

	// only to be used during overlay construction
	// adds any overlay component overlay to the overlay instance
	void addComponent(OLCMP::BaseComponent* pCmp);

protected:
	CmpOverlay();
	CmpOverlay(const RECT& rc);
	CmpOverlay(BaseOverlay* pParent);
	CmpOverlay(const RECT& rc, BaseOverlay* pParent);

	// contains all of the overlays components
	std::vector<OLCMP::BaseComponent*> cmp;
};

#endif
