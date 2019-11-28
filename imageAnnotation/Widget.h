#include <windows.h>
#include <d2d1.h>
#pragma comment(lib, "d2d1")

struct widgetBlock {
	double xloc;
	double yloc;
	double xSize;
	double ySize;

	bool contains(POINT p) {
		if (
			p.x < xloc + xSize && p.x > xloc - xSize &&
			p.y < yloc + ySize && p.y > yloc - ySize
			)
			return true;
		return false;
	}

};

class Widget
{
	double xLoc;
	double yLoc;
	double xSize;
	double ySize;

	Widget(double xLoc, double yLoc, double xSize, double ySize);

};

