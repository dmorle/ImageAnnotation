#include "ImageBuffer.h"



namespace WCMP {

	ImageBuffer::ImageBuffer(D2D1_RECT_F* pRc, PRECT parentpRc, ID2D1HwndRenderTarget* pRenderTarget, IWICImagingFactory* pWicFactory, std::string target, UINT bufferSize)
		: BaseComponent(pRc, parentpRc), InteractiveComponent(pRc, parentpRc), Buffer(target, "", bufferSize, &LoadElem), ImageBaseComponent(pRenderTarget, pWicFactory)
	{
		this->pMouseLoc = NULL;

		this->zoom = 1;
		this->pTrans = NULL;

		this->pRenderTarget = pRenderTarget;
		this->pWicFactory = pWicFactory;
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

	BaseComponent* ImageBuffer::clone(PRECT npRc)
	{
		releaseThread();

		ImageBuffer* npBuffer = new ImageBuffer(*this);
		npBuffer->parentpRc = npRc;
		D2D1_POINT_2U point = D2D1_POINT_2U{ 0, 0 };

		// creating the new buffer
		for (auto e : buffer) {
			// creating the copy bitmap
			ID2D1Bitmap* npBmp;
			FLOAT dpiX;
			FLOAT dpiY;
			e->GetDpi(&dpiX, &dpiY);
			pRenderTarget->CreateBitmap(
				e->GetPixelSize(),
				D2D1_BITMAP_PROPERTIES{ e->GetPixelFormat(), dpiX, dpiY },
				&npBmp
			);

			// copying the old bitmap
			D2D1_SIZE_U size = e->GetPixelSize();
			D2D1_RECT_U src = D2D1_RECT_U{ 0, 0, size.width, size.height };
			npBmp->CopyFromBitmap(&point, e, &src);

			// building the new buffer
			npBuffer->buffer.push_back(npBmp);
		}

		// getting the active element
		npBuffer->active = new std::list<ID2D1Bitmap*>::iterator(npBuffer->buffer.begin());
		std::advance(npBuffer->active, bufferSize + 1);

		return npBuffer;
	}

	void ImageBuffer::m_MouseLeave() {}

}