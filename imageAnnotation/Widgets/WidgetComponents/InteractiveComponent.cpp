#include "InteractiveComponent.h"



namespace WCMP {

	InteractiveComponent::InteractiveComponent(
		D2D1_RECT_F* pRc,
		PRECT parentpRc,
		Resizable* pRB,
		void (*onClick)(),
		void (*paintSelf)(PRECT)
	) :
		BaseComponent(pRc, parentpRc, pRB)
	{
		this->state = STATE::PASSIVE;
		this->onClick = onClick;
		this->paintSelf = paintSelf;
	}

	InteractiveComponent::InteractiveComponent(InteractiveComponent* pThis, PRECT npRc)
		: BaseComponent(pThis, npRc)
	{
		state = STATE::PASSIVE;
		onClick = pThis->onClick;
		paintSelf = pThis->paintSelf;
	}

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
			if (state != STATE::PRESSED)
				state = STATE::ACTIVE;
		}
		else
			state = STATE::PASSIVE;
	}

	void InteractiveComponent::m_LDown(POINT p)
	{
		if (contains(p))
			state = STATE::PRESSED;
	}

	void InteractiveComponent::m_LUp(POINT p)
	{
		if (onClick)
			if (contains(p) && state == STATE::PRESSED) {
				state = STATE::ACTIVE;
				onClick();
			}
	}

	void InteractiveComponent::m_MouseLeave()
	{
		state = STATE::PASSIVE;
	}

}