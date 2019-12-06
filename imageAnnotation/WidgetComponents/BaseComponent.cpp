#include "BaseComponent.h"

BOOL BaseComponent::contains(POINT p)
{
	if (
		p.x >= rc.left && p.x < rc.right &&
		p.y >= rc.top && p.y < rc.bottom
		)
		return TRUE;

	return FALSE;
}
