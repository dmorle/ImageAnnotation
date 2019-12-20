#include "InteractiveComponent.h"



namespace WCMP {

	InteractiveComponent::InteractiveComponent(D2D1_RECT_F* pRc, PRECT parentpRc)
		: BaseComponent(pRc, parentpRc) {}

	void InteractiveComponent::MouseMove(POINT p)
	{
		StateUpdateFunc(m_MouseMove, p)
	}

	void InteractiveComponent::LDown(POINT p)
	{
		StateUpdateFunc(m_LDown, p)
	}

	void InteractiveComponent::LUp(POINT p)
	{
		StateUpdateFunc(m_LUp, p)
	}

	void InteractiveComponent::MouseLeave()
	{
		StateUpdateFunc(m_MouseLeave, )
	}

	void InteractiveComponent::m_MouseMove(POINT p)
	{
		if (contains(p)) {
			if (state != PRESSED)
				state = ACTIVE;
		}
		else
			state = PASSIVE;
	}

	void InteractiveComponent::m_LDown(POINT p)
	{
		if (contains(p))
			state = PRESSED;
	}

	void InteractiveComponent::m_LUp(POINT p)
	{
		if (contains(p) && state == PRESSED) {
			state = ACTIVE;
			onClick();
		}
	}

	void InteractiveComponent::m_MouseLeave()
	{
		state = PASSIVE;
	}

}