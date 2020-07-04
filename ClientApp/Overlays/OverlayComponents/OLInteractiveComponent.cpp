#include "OLInteractiveComponent.h"



namespace OLCMP
{
	InteractiveComponent::InteractiveComponent(const RECT& rc) :
		BaseComponent(rc)
	{
		interactive = TRUE;
	}

	InteractiveComponent::~InteractiveComponent()
	{
	}
}
