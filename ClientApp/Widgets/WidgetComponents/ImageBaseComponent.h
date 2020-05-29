#ifndef WCMP_IMAGE_BASE_COMPONENT_H
#define WCMP_IMAGE_BASE_COMPONENT_H

#ifndef WIDGET_CMP_H
#include "BaseComponent.h"
#endif

namespace WCMP {

    namespace {
        ID2D1HwndRenderTarget* pRenderTarget;
        IWICImagingFactory* pWicFactory;
    }

    class ImageBaseComponent :
        virtual public BaseComponent
    {
    public:
        ImageBaseComponent(ID2D1HwndRenderTarget*& arg_pRenderTarget, IWICImagingFactory*& arg_pWicFactory);

    protected:
        ImageBaseComponent();

        static HRESULT LoadBitmapBrush(
            PCWSTR uri,
            ID2D1BitmapBrush** ppBrush,
            ID2D1Bitmap** ppBitmap
        );

        static HRESULT LoadBitmapFromFile(
            PCWSTR uri,
            ID2D1Bitmap** ppBitmap
        );

        static HRESULT TransformBitmap(
            ID2D1Bitmap* src,
            FLOAT zoom,
            POINT pTrans,
            ID2D1Bitmap** ppBitmap
        );
    };

}

#endif