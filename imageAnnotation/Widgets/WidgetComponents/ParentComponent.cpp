#include "ParentComponent.h"



namespace WCMP {

	ParentComponent::ParentComponent(D2D1_RECT_F* pRc, PRECT parentpRc, Resizable* pRB)
		: BaseComponent(pRc, parentpRc, pRB) {}

	ParentComponent::ParentComponent(ParentComponent* pThis, PRECT npRc)
		: BaseComponent(pThis, npRc)
	{
		pRB = new Resizable(pThis->pRB);
		for (auto e : children)
			if (e)
				children.push_back(e->clone(npRc));
	}

	ParentComponent::~ParentComponent()
	{
		for (auto e : children)
			if (e)
				delete e;
	}

	void ParentComponent::MouseMove(POINT p)
	{
		auto it = children.begin();
		for (; it != children.end(); it++)
			if ((*it)->contains(p))
				break;

		(*it)->MouseMove(p);
		activateElement(it);
	}

	void ParentComponent::LDown(POINT p)
	{
		auto it = children.begin();
		for (; it != children.end(); it++)
			if ((*it)->contains(p))
				break;

		(*it)->LUp(p);
		activateElement(it);
	}

	void ParentComponent::LUp(POINT p)
	{
		auto it = children.begin();
		for (; it != children.end(); it++)
			if ((*it)->contains(p))
				break;

		(*it)->LDown(p);
		activateElement(it);
	}

	void ParentComponent::MouseLeave()
	{
		for (auto it = children.begin(); it != children.end(); it++)
			(*it)->MouseLeave();
	}

	void ParentComponent::display(ID2D1HwndRenderTarget* pRenderTarget)
	{
		if (IsValidRect())
			for (auto it = children.end(); it != children.begin(); it--)
				(*it)->display(pRenderTarget);
	}

	BaseComponent* ParentComponent::clone(PRECT npRc)
	{
		return new ParentComponent(this, npRc);
	}

	void ParentComponent::activateElement(std::list<PBaseComponent>::iterator it)
	{
		if (it != children.begin()) {
			PBaseComponent e = *it;
			children.erase(it);
			children.push_front(e);
		}
	}

}