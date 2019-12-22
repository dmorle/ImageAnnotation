#ifndef IMAGEBUFFER_H
#define IMAGEBUFFER_H

#include "InteractiveComponent.h"
#include "ImageBaseComponent.h"
#include "Buffer.h"

#include <list>
#include <string>

namespace WCMP {

	class ImageBuffer :
		public InteractiveComponent, public ImageBaseComponent, public Buffer<ID2D1Bitmap>
	{
	public:
		ImageBuffer(D2D1_RECT_F* pRc, PRECT parentpRc, ID2D1HwndRenderTarget* pRenderTarget, IWICImagingFactory* pWicFactory, std::string target, UINT bufferSize);

		virtual void MouseMove(POINT p) override;
		virtual void LDown(POINT p) override;
		virtual void LUp(POINT p) override;
		virtual void MouseLeave() override;

		virtual void MouseWheel(POINT p, WORD lOrder);

		virtual void display(ID2D1HwndRenderTarget* pRenderTarget) override;

		virtual BaseComponent* clone(PRECT nparentpRc);

	protected:
		ImageBuffer(ImageBuffer* pThis);

		// the current zoom level for the image
		FLOAT zoom;
		// the current translation of the image
		POINT* pTrans;

	private:
		// the current location of the mouse when on the component
		POINT* pMouseLoc;

		static ID2D1Bitmap* LoadItem(std::wstring* path);
		static ID2D1Bitmap* CopyItem(ID2D1Bitmap* pBmp);
		static void ReleaseItem(ID2D1Bitmap* pBmp);

		void m_MouseLeave();
	};

}

#endif