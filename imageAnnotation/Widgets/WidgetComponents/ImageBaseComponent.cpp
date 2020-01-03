#include "ImageBaseComponent.h"



namespace WCMP {

    ImageBaseComponent::ImageBaseComponent(ID2D1HwndRenderTarget*& arg_pRenderTarget, IWICImagingFactory*& arg_pWicFactory)
    {
        pRenderTarget = arg_pRenderTarget;
        pWicFactory = arg_pWicFactory;
    }

    ImageBaseComponent::ImageBaseComponent() {}

	HRESULT ImageBaseComponent::LoadBitmapBrush(
        PCWSTR uri,
        ID2D1BitmapBrush** ppBrush,
        ID2D1Bitmap** ppBitmap
    )
    {
        HRESULT hr;

        // Create the bitmap to be used by the bitmap brush
        hr = LoadBitmapFromFile(
            uri,
            ppBitmap
        );

        if (SUCCEEDED(hr)) {
            D2D1_BITMAP_BRUSH_PROPERTIES propertiesXClampYClamp = D2D1::BitmapBrushProperties(
                D2D1_EXTEND_MODE_CLAMP,
                D2D1_EXTEND_MODE_CLAMP,
                D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR
            );

            hr = pRenderTarget->CreateBitmapBrush(
                *ppBitmap,
                propertiesXClampYClamp,
                ppBrush
            );
        }

        return hr;
    }

    HRESULT ImageBaseComponent::LoadBitmapFromFile(
        PCWSTR uri,
        ID2D1Bitmap** ppBitmap
    )
    {
        IWICBitmapDecoder* pDecoder = NULL;
        IWICBitmapFrameDecode* pSource = NULL;
        IWICStream* pStream = NULL;
        IWICFormatConverter* pConverter = NULL;
        IWICBitmapScaler* pScaler = NULL;

        HRESULT hr = pWicFactory->CreateDecoderFromFilename(
            uri,
            NULL,
            GENERIC_READ,
            WICDecodeMetadataCacheOnLoad,
            &pDecoder
        );

        if (SUCCEEDED(hr))
        {
            // Create the initial frame.
            hr = pDecoder->GetFrame(0, &pSource);
        }

        if (SUCCEEDED(hr))
        {

            // Convert the image format to 32bppPBGRA
            // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
            hr = pWicFactory->CreateFormatConverter(&pConverter);

        }

        if (SUCCEEDED(hr))
            hr = pConverter->Initialize(
                pSource,
                GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone,
                NULL,
                0.f,
                WICBitmapPaletteTypeMedianCut
            );

        if (SUCCEEDED(hr))
        {

            // Create a Direct2D bitmap from the WIC bitmap.
            hr = pRenderTarget->CreateBitmapFromWicBitmap(
                pConverter,
                NULL,
                ppBitmap
            );
        }

        SafeRelease(&pDecoder);
        SafeRelease(&pSource);
        SafeRelease(&pStream);
        SafeRelease(&pConverter);
        SafeRelease(&pScaler);

        return hr;
    }

    HRESULT ImageBaseComponent::TransformBitmap(ID2D1Bitmap* src, FLOAT zoom, POINT pTrans, ID2D1Bitmap** ppBitmap)
    {
        return E_NOTIMPL;
    }

}