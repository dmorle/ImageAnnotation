#include "ParentComponent.h"



namespace WCMP {

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

	void ParentComponent::display(ID2D1HwndRenderTarget* pRenderTarget, const D2D1_RECT_F& parent)
	{
		for (auto it = children.end(); it != children.begin(); it--)
			(*it)->display(pRenderTarget, parent);
	}

	BaseComponent* ParentComponent::clone()
	{
		ParentComponent* npCmp = new ParentComponent();

		npCmp->pRc = new D2D1_RECT_F(*pRc);
		for (auto e : children)
			if (e)
				npCmp->children.push_back(e->clone());

		return npCmp;
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