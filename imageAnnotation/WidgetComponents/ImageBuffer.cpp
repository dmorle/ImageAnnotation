#include "ImageBuffer.h"



namespace WCMP {

	ImageBuffer::ImageBuffer(PRECT pRc, ID2D1HwndRenderTarget*& pRenderTarget, std::string target, UINT bufferSize)
		: Buffer(target, "", bufferSize, &LoadElem), pRenderTarget(pRenderTarget)
	{
		this->pRc = pRc;
	}

	void ImageBuffer::MouseMove(POINT p) {}
	void ImageBuffer::LDown(POINT p) {}
	void ImageBuffer::LUp(POINT p) {}
	void ImageBuffer::MouseLeave() {}

	void ImageBuffer::display(ID2D1HwndRenderTarget* pRenderTarget) {}

	ID2D1Bitmap* ImageBuffer::LoadElem(std::wstring* path)
	{
		return NULL;
	}

}