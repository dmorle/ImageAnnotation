#include "ImageBuffer.h"



ImageBuffer::ImageBuffer(PRECT pRc, ID2D1HwndRenderTarget*& pRenderTarget, std::string target, UINT bufferSize)
	: Buffer(target, "", bufferSize), pRenderTarget(pRenderTarget)
{
	this->pRc = pRc;
}

void ImageBuffer::MouseMove(POINT p) {}
void ImageBuffer::LDown(POINT p) {}
void ImageBuffer::LUp(POINT p) {}
void ImageBuffer::MouseLeave() {}

void ImageBuffer::display(ID2D1HwndRenderTarget* pRenderTarget) {}

ID2D1Bitmap* ImageBuffer::LoadElem()
{
	return NULL;
}