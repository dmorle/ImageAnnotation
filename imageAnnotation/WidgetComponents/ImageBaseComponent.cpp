#include "ImageBaseComponent.h"



HRESULT ImageBaseComponent::LoadBitmapBrush(
    ID2D1HwndRenderTarget* pRenderTarget,
    IWICImagingFactory* pIWICFactory,
    PCWSTR uri,
    ID2D1BitmapBrush** ppBrush,
    ID2D1Bitmap** ppBitmap
)
{
    HRESULT hr;

    // Create the bitmap to be used by the bitmap brush
    hr = LoadBitmapFromFile(
        pRenderTarget,
        pIWICFactory,
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
    ID2D1RenderTarget* pRenderTarget,
    IWICImagingFactory* pIWICFactory,
    PCWSTR uri,
    ID2D1Bitmap** ppBitmap
)
{
    IWICBitmapDecoder* pDecoder = NULL;
    IWICBitmapFrameDecode* pSource = NULL;
    IWICStream* pStream = NULL;
    IWICFormatConverter* pConverter = NULL;
    IWICBitmapScaler* pScaler = NULL;

    HRESULT hr = pIWICFactory->CreateDecoderFromFilename(
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
        hr = pIWICFactory->CreateFormatConverter(&pConverter);

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