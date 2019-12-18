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
		ImageBuffer(PRECT pRc, ID2D1HwndRenderTarget*& pRenderTarget, IWICImagingFactory*& pWicFactory, std::string target, UINT bufferSize);

		virtual void MouseMove(POINT p);
		virtual void LDown(POINT p);
		virtual void LUp(POINT p);
		virtual void MouseLeave();

		virtual void MouseWheel(POINT p, WORD lOrder);

		virtual void display(ID2D1HwndRenderTarget* pRenderTarget = NULL);

	protected:
		FLOAT zoom;
		POINT* pTrans;

	private:
		POINT* pMouseLoc;

		static ID2D1Bitmap* LoadElem(std::wstring* path);
		void m_MouseLeave();
	};

}

#endif