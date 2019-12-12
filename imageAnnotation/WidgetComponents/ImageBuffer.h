#ifndef IMAGEBUFFER_H
#define IMAGEBUFFER_H

#include "ImageBaseComponent.h"
#include "Buffer.h"

#include <list>
#include <string>

namespace WCMP {

	class ImageBuffer :
		public ImageBaseComponent, public Buffer<ID2D1Bitmap>
	{
	public:
		virtual void MouseMove(POINT p);
		virtual void LDown(POINT p);
		virtual void LUp(POINT p);
		virtual void MouseLeave();

		virtual void display(ID2D1HwndRenderTarget* pRenderTarget);

	protected:
		ImageBuffer(PRECT pRc, ID2D1HwndRenderTarget*& pRenderTarget, std::string target, UINT bufferSize);

		static ID2D1Bitmap* LoadElem(std::wstring* path);

	private:
		ID2D1HwndRenderTarget*& pRenderTarget;
	};

}

#endif