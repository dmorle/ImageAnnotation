#ifndef LAYOUT_H
#define LAYOUT_H

#include "Widget.h"
#include <vector>

class Layout
{
	enum Orientation {
		Vertical,
		Horizontal,
		None
	};

	Orientation dir;
	std::vector<Layout> children;
	Widget* w;

	Layout();
	void resize();
};

#endif