#include "ImageBuffer.h"



namespace WCMP {

	ImageBuffer::ImageBuffer(
		ID2D1HwndRenderTarget* pRenderTarget,
		IWICImagingFactory* pWicFactory,
		D2D1_RECT_F* pRc,
		PRECT parentpRc,
		void (*onClick)(),
		void (*paintSelf)(PRECT),
		std::string target,
		UINT bufferSize
	) :
		BaseComponent(pRc, parentpRc),
		InteractiveComponent(pRc, parentpRc, onClick, paintSelf),
		Buffer(target, "", bufferSize, &LoadItem, &ReleaseItem),
		ImageBaseComponent(pRenderTarget, pWicFactory)
	{
		this->pMouseLoc = NULL;

		this->zoom = 1;
		this->pTrans = NULL;
	}

	ImageBuffer::ImageBuffer(
		ImageBuffer* pThis,
		PRECT parentpRc
	) :
		BaseComponent(NULL, NULL),
		InteractiveComponent(NULL, NULL, onClick, pThis->paintSelf),
		Buffer(pThis),
		ImageBaseComponent()
	{
		this->pRc = new D2D1_RECT_F(*pThis->pRc);
		this->parentpRc = parentpRc;

		this->pMouseLoc = NULL;
		
		this->zoom = pThis->zoom;
		if (pThis->pTrans)
			this->pTrans = new POINT(*pThis->pTrans);
	}

	ImageBuffer::~ImageBuffer()
	{
		if (pTrans)
			delete pTrans;

		if (pMouseLoc)
			delete pMouseLoc;
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

		if (pMouseLoc) {
			delete pMouseLoc;
			pMouseLoc = NULL;
		}
	}

	void ImageBuffer::MouseWheel(POINT p, WORD lWord)
	{

	}

	void ImageBuffer::resize(PRECT npRc)
	{
		if (!npRc)
			npRc = parentpRc;
		
		// TODO: resize to npRc
	}

	void ImageBuffer::display(ID2D1HwndRenderTarget* pRenderTarget)
	{
		D2D1_RECT_F rc;
		getGlobalRect(rc);
		ID2D1Bitmap* pBmp = getActiveItem();
		D2D1_SIZE_F size = pBmp->GetSize();
		pRenderTarget->DrawBitmap(pBmp, rc, 1, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, D2D1_RECT_F{ 0, 0, size.width, size.height });
	}

	ID2D1Bitmap* ImageBuffer::LoadItem(std::wstring* path)
	{
		ID2D1Bitmap* npBmp;
		if (SUCCEEDED(LoadBitmapFromFile(path->c_str(), &npBmp)))
			return npBmp;
		return NULL;
	}

	void ImageBuffer::ReleaseItem(ID2D1Bitmap* pBmp)
	{
		SafeRelease(&pBmp);
	}

	BaseComponent* ImageBuffer::clone(PRECT npRc)
	{
		return new ImageBuffer(this, npRc);
	}

	void ImageBuffer::m_MouseLeave() {}

}