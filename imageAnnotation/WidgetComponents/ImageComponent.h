#ifndef IMAGECOMPONENT_H
#define IMAGECOMPONENT_H

#include "BaseComponent.h"
#include <wincodec.h>

class ImageComponent :
	public BaseComponent
{
public:
protected:
    HRESULT LoadBitmapFromFile(
        ID2D1RenderTarget* pRenderTarget,
        IWICImagingFactory* pIWICFactory,
        PCWSTR uri,
        UINT destinationWidth,
        UINT destinationHeight,
        ID2D1Bitmap** ppBitmap
    );
};

#endif