#include "WinMain.h"

namespace {
	enum SIDE {
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};

	typedef struct widgetBlock widgetBlock;
	struct widgetBlock {
		double xLoc;
		double yLoc;
		double xSize;
		double ySize;

		bool contains(POINT p) {
			if (
				p.x < xLoc + xSize && p.x > xLoc - xSize &&
				p.y < yLoc + ySize && p.y > yLoc - ySize
				)
				return true;
			return false;
		}

		void moveSide(SIDE s, double val) {
			val /= 2;
			double dsize = val * (2 * (s % 2) - 1);
			if (s < 2) {
				xLoc += val;
				xSize += dsize;
			}
			else {
				yLoc += val;
				ySize += val;
			}
		}

		widgetBlock() {}

	};
}

class Widget
{
	widgetBlock* pBlock;
	stdBrushes& brushes;

public:

	Widget(double xLoc, double yLoc, double xSize, double ySize, stdBrushes& brushes);
	Widget(widgetBlock* pBlock, stdBrushes& brushes);

	~Widget();

	render(ID2D1HwndRenderTarget* pRenderTarget);
};

