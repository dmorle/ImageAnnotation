#include "Widget.h"



Widget::Widget(double xLoc, double yLoc, double xSize, double ySize, stdBrushes& brushes) : 
	brushes(stdBrushes::none)
{
	this->pBlock = new widgetBlock();
	this->pBlock->xLoc = xLoc;
	this->pBlock->yLoc = yLoc;
	this->pBlock->xSize = xSize;
	this->pBlock->ySize = ySize;

	this->brushes = brushes;
}

Widget::Widget(widgetBlock* pBlock, stdBrushes& brushes) :
	brushes(stdBrushes::none)
{
	this->pBlock = pBlock;

	this->brushes = brushes;
}

Widget::~Widget()
{
	delete this->pBlock;
}

Widget::render(ID2D1HwndRenderTarget* pRenderTarget)
{
}
