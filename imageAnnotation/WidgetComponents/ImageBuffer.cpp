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
		Buffer(target, "", bufferSize, &LoadItem, &CopyItem, &ReleaseItem),
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
		
		// TODO: resize to tempRc
	}

	void ImageBuffer::display(ID2D1HwndRenderTarget* pRenderTarget)
	{
		ID2D1SolidColorBrush* pBrush;
		pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0), &pBrush);
		D2D1_RECT_F rc;
		getGlobalRect(rc);
		pRenderTarget->FillRectangle(rc, pBrush);
		pBrush->Release();
	}

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
		return new ImageBuffer(this, npRc);
	}

	void ImageBuffer::m_MouseLeave() {}

}