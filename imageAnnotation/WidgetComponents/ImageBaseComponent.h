#ifndef IMAGEBASECOMPONENT_H
#define IMAGEBASECOMPONENT_H

#include "BaseComponent.h"
#include <wincodec.h>

namespace WCMP {

    class ImageBaseComponent :
        virtual public BaseComponent
    {
    public:
        ImageBaseComponent(ID2D1HwndRenderTarget*& pRenderTarget, IWICImagingFactory*& pWicFactory);

    protected:
        ID2D1HwndRenderTarget*& pRenderTarget;
        IWICImagingFactory*& pWicFactory;

        HRESULT LoadBitmapBrush(
            PCWSTR,
            ID2D1BitmapBrush**,
            ID2D1Bitmap**
        );

    private:
        HRESULT LoadBitmapFromFile(
            PCWSTR,
            ID2D1Bitmap**
        );
    };

}

#endif