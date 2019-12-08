#ifndef IMAGEBASECOMPONENT_H
#define IMAGEBASECOMPONENT_H

#include "BaseComponent.h"
#include <wincodec.h>

class ImageBaseComponent :
	public BaseComponent
{
public:
protected:
    HRESULT LoadBitmapBrush(
        ID2D1HwndRenderTarget*,
        IWICImagingFactory*,
        PCWSTR,
        ID2D1BitmapBrush**,
        ID2D1Bitmap**
    );

private:
    HRESULT LoadBitmapFromFile(
        ID2D1RenderTarget*,
        IWICImagingFactory*,
        PCWSTR,
        ID2D1Bitmap**
    );
};

#endif