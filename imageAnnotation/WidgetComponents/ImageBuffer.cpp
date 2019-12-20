#include "ImageBuffer.h"



namespace WCMP {

	ImageBuffer::ImageBuffer(D2D1_RECT_F* pRc, ID2D1HwndRenderTarget*& pRenderTarget, IWICImagingFactory*& pWicFactory, std::string target, UINT bufferSize)
		: Buffer(target, "", bufferSize, &LoadElem), ImageBaseComponent(pRenderTarget, pWicFactory)
	{
		this->pRc = pRc;
		this->pMouseLoc = NULL;

		this->zoom = 1;
		this->pTrans = NULL;
	}

	void ImageBuffer::MouseMove(POINT p)
	{
		InteractiveComponent::MouseMove(p);

		if (!pMouseLoc)
			pMouseLoc = new POINT(p);

		else {
			pMouseLoc->x = p.x;
			pMouseLoc->y = p.y;
		}
	}

	void ImageBuffer::LDown(POINT p)
	{
		
	}

	void ImageBuffer::LUp(POINT p)
	{

	}

	void ImageBuffer::MouseLeave()
	{
		InteractiveComponent::MouseLeave();

		if (pMouseLoc)
			delete pMouseLoc;
	}

	void ImageBuffer::MouseWheel(POINT p, WORD lWord)
	{

	}

	void ImageBuffer::display(ID2D1HwndRenderTarget* pRenderTarget) {}

	ID2D1Bitmap* ImageBuffer::LoadElem(std::wstring* path)
	{
		
		return NULL;
	}

	void ImageBuffer::m_MouseLeave() {}

}