#include "WinMain.h"



// Recalculate drawing layout when the size of the window changes.
void MainWindow::CalculateLayout()
{
	FLOAT spacing = 2;

	if (pRenderTarget != NULL)
	{
		D2D1_SIZE_F size = pRenderTarget->GetSize();

		if (!widgets.size()) {
			// create default layout
			widgets.push_back(Widget(spacing, spacing, size.width - spacing, size.height - spacing, brushes));
		}

		else {
			// resize current layout
			widgets[0].resize(spacing, spacing, size.width - spacing, size.height - spacing);
		}
	}
}

HRESULT MainWindow::CreateGraphicsResources()
{
	HRESULT hr = S_OK;
	if (pRenderTarget == NULL)
	{
		D2D1_RECT_L rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		hr = pFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_hwnd, size),
			&pRenderTarget);
	}

	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(palette.background, &brushes.background);

	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(palette.widgetBack, &brushes.widgetBack);

	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(palette.passive, &brushes.passive);

	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(palette.active, &brushes.active);

	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(palette.text, &brushes.text);
	return hr;
}

void MainWindow::DiscardGraphicsResources()
{
	SafeRelease(&pRenderTarget);
	brushes.release();
}

void MainWindow::Paint()
{
	HRESULT hr = CreateGraphicsResources();
	if (SUCCEEDED(hr) && widgets.size() == 0)
		Resize();
	if (SUCCEEDED(hr))
	{
		PAINTSTRUCT ps;
		BeginPaint(m_hwnd, &ps);

		pRenderTarget->BeginDraw();

		pRenderTarget->Clear(palette.background);

		for (auto& e : widgets)
			e.render(pRenderTarget);

		hr = pRenderTarget->EndDraw();
		if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
		{
			DiscardGraphicsResources();
		}
		EndPaint(m_hwnd, &ps);
	}
}

void MainWindow::Resize()
{
	if (pRenderTarget != NULL)
	{
		D2D1_RECT_L rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		pRenderTarget->Resize(size);
		CalculateLayout();
		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}

void MainWindow::MouseMove(WPARAM wparam, LPARAM lparam)
{
	POINT p { GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };
	for (auto& e : widgets)
		if (e.contains(p)) {
			e.MouseMove(wparam, p);
			break;
		}
}

void MainWindow::LUp()
{
}

void MainWindow::LDown()
{
}

void MainWindow::RUp()
{
}

void MainWindow::RDown()
{
}

void MainWindow::createDefaultLayout()
{
	
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
	MainWindow win;

	if (!win.Create(L"Circle", WS_OVERLAPPEDWINDOW))
	{
		return 0;
	}

	ShowWindow(win.Window(), nCmdShow);

	// Run the message loop.

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
			return -1;  // Fail CreateWindowEx.
		
		return 0;

	case WM_DESTROY:
		DiscardGraphicsResources();
		SafeRelease(&pFactory);
		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
		Paint();
		return 0;

	case WM_SIZE:
		Resize();
		return 0;

	case WM_MOUSEMOVE:
		MouseMove();
		return 0;

	case WM_LBUTTONUP:
		return 0;

	case WM_LBUTTONDOWN:
		return 0;

	case WM_RBUTTONUP:
		return 0;

	case WM_RBUTTONDOWN:
		return 0;
	}
	return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
}