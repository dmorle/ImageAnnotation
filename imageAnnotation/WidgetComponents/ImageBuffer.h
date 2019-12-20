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
		FLOAT zoom;
		POINT* pTrans;

		ID2D1HwndRenderTarget* pRenderTarget;
		IWICImagingFactory* pWicFactory;

	private:
		POINT* pMouseLoc;

		static ID2D1Bitmap* LoadElem(std::wstring* path);
		void m_MouseLeave();
	};

}

#endif