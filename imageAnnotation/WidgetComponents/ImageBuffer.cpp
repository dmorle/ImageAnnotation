#include "ImageBuffer.h"



namespace WCMP {

	ImageBuffer::ImageBuffer(D2D1_RECT_F* pRc, PRECT parentpRc, ID2D1HwndRenderTarget* pRenderTarget, IWICImagingFactory* pWicFactory, std::string target, UINT bufferSize)
		: BaseComponent(pRc, parentpRc), InteractiveComponent(pRc, parentpRc), Buffer(target, "", bufferSize, &LoadItem, &CopyItem, &ReleaseItem), ImageBaseComponent(pRenderTarget, pWicFactory)
	{
		this->pMouseLoc = NULL;

		this->zoom = 1;
		this->pTrans = NULL;
	}

	ImageBuffer::ImageBuffer(ImageBuffer* pThis)
		: BaseComponent(pRc, parentpRc), InteractiveComponent(pRc, parentpRc), Buffer(pThis), ImageBaseComponent()
	{
		this->pMouseLoc = new POINT(*pThis->pMouseLoc);
		
		this->zoom = pThis->zoom;
		this->pTrans = new POINT(*pThis->pTrans);
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

	ID2D1Bitmap* ImageBuffer::LoadItem(std::wstring* path)
	{
		ID2D1Bitmap* npBmp;
		if (SUCCEEDED(LoadBitmapFromFile(path->c_str(), &npBmp)))
			return npBmp;
		return NULL;
	}

	ID2D1Bitmap* ImageBuffer::CopyItem(ID2D1Bitmap* pBmp)
	{
		pBmp->AddRef();
		return pBmp;
	}

	void ImageBuffer::ReleaseItem(ID2D1Bitmap* pBmp)
	{
		SafeRelease(&pBmp);
	}

	BaseComponent* ImageBuffer::clone(PRECT npRc)
	{
		return new ImageBuffer(this);
	}

	void ImageBuffer::m_MouseLeave() {}

}