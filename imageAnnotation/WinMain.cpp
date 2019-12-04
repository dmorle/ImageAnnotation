#include "WinMain.h"



#define TOCOLORREF(c) RGB(c.r * 255, c.g * 255, c.b * 255)
#define TOD2D1RECTF(rc) D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom)

void MainWindow::savePalette(std::string path)
{

}

void MainWindow::loadPalette(std::string path)
{

}

// Recalculate drawing layout when the size of the window changes.
void MainWindow::CalculateLayout(D2D1_SIZE_F prev)
{
	if (pRenderTarget != NULL)
	{
		D2D1_SIZE_F size = pRenderTarget->GetSize();

		if (!widgets.size()) {
			// create default layout
			widgets.push_back(new Widget(m_hwnd, 0, 0, size.width, size.height, this));
		}

		else {
			// resize current layout
			widgets[0]->resize(0, 0, size.width, size.height);
		}
	}
}

HRESULT MainWindow::CreateGraphicsResources()
{
	if (!cursors.arrow)
		cursors.arrow = LoadCursor(NULL, IDC_ARROW);

	if (!cursors.sizens)
		cursors.sizens = LoadCursor(NULL, IDC_SIZENS);

	if (!cursors.sizewe)
		cursors.sizewe = LoadCursor(NULL, IDC_SIZEWE);

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
		hr = pRenderTarget->CreateSolidColorBrush(palette[appPalette::BACKGROUND], &brushes.background);

	if (SUCCEEDED(hr)) {
		D2D1_COLOR_F delColor = palette[appPalette::BACKGROUND];
		delColor.a = 0.3f;
		hr = pRenderTarget->CreateSolidColorBrush(delColor, &brushes.preDeletion);
	}

	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(palette[appPalette::WIDGET_BACK], &brushes.widgetBack);

	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(palette[appPalette::PASSIVE], &brushes.passive);

	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(palette[appPalette::ACTIVE], &brushes.active);

	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(palette[appPalette::TEXT], &brushes.text);
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

		pRenderTarget->Clear(palette[appPalette::BACKGROUND]);

		/*for (auto& e : widgets)
			e->render(pRenderTarget);

		if (activeWidget)
			activeWidget->render(pRenderTarget);*/

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
	RECT rect;
	HRGN rgn;
	GetWindowRect(m_hwnd, &rect);
	rgn = CreateRectRgn(0, 0, rect.right, rect.bottom);
	SetWindowRgn(m_hwnd, rgn, TRUE);
	DeleteObject(rgn);

	if (pRenderTarget != NULL)
	{
		D2D1_SIZE_F prev = pRenderTarget->GetSize();

		D2D1_RECT_L rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

		pRenderTarget->Resize(size);
		CalculateLayout(prev);
		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}

void MainWindow::MouseMove(WPARAM wparam, LPARAM lparam)
{
	SetCursor(cursors.arrow);

	POINT p { GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };

	if (activeWidget)
		activeWidget = activeWidget->MouseMove(wparam, p);
	else
		for (auto& e : widgets)
			if (e->contains(p)) {
				activeWidget = e->MouseMove(wparam, p);
				break;
			}
}

void MainWindow::MouseLeave(WPARAM wparam, LPARAM lparam)
{
	if (activeWidget) {
		POINT p{ GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };
		activeWidget = activeWidget->MouseMove(wparam, p);
	}
}

void MainWindow::LUp(WPARAM wparam, LPARAM lparam)
{
	POINT p{ GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };
	
	if (activeWidget)
		activeWidget = activeWidget->LUp(wparam, p);
	else
		for (auto& e : widgets)
			if (e->contains(p)) {
				activeWidget = e->LUp(wparam, p);
				break;
			}
}

void MainWindow::LDown(WPARAM wparam, LPARAM lparam)
{
	POINT p{ GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };
	
	if (activeWidget)
		activeWidget = activeWidget->LDown(wparam, p);
	else
		for (auto& e : widgets)
			if (e->contains(p)) {
				activeWidget = e->LDown(wparam, p);
				break;
			}
}

void MainWindow::RUp(WPARAM wparam, LPARAM lparam)
{
}

void MainWindow::RDown(WPARAM wparam, LPARAM lparam)
{
}

void MainWindow::ncPaint(WPARAM wparam, LPARAM lparam)
{
	RECT rcWin;
	GetWindowRect(m_hwnd, &rcWin);
	RECT rc{
		0,
		0,
		rcWin.right - rcWin.left,
		rcWin.bottom - rcWin.top
	};

	HDC hdc;
	if (wparam == 0 || wparam == 1)
		hdc = GetWindowDC(m_hwnd);
	else
		hdc = GetDCEx(m_hwnd, (HRGN)wparam, DCX_WINDOW | DCX_CACHE | DCX_LOCKWINDOWUPDATE | DCX_INTERSECTRGN);

	HBRUSH hbr = CreateSolidBrush(TOCOLORREF(palette[appPalette::WIDGET_BACK]));
	FillRect(hdc, &rc, hbr);
	DeleteObject(hbr);

	ReleaseDC(m_hwnd, hdc);
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

LRESULT MainWindow::HandleMessage(UINT uMsg, WPARAM wparam, LPARAM lparam)
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
		MouseMove(wparam, lparam);
		return 0;

	case WM_MOUSELEAVE:
		MouseLeave(wparam, lparam);
		return 0;

	case WM_LBUTTONUP:
		LUp(wparam, lparam);
		return 0;

	case WM_LBUTTONDOWN:
		LDown(wparam, lparam);
		return 0;

	case WM_RBUTTONUP:
		return 0;

	case WM_RBUTTONDOWN:
		return 0;

	case WM_NCPAINT:
		ncPaint(wparam, lparam);
		return 0;

	case WM_NCACTIVATE:
		SetWindowPos(m_hwnd, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE | SWP_FRAMECHANGED);
		return 0;

	case WM_NCCALCSIZE:
	{
		if (wparam)
		{
			NCCALCSIZE_PARAMS* ncparams = (NCCALCSIZE_PARAMS*)lparam;
			printf("WM_NCCALCSIZE wparam:True\n");
			// ncparams->rgrc[0].left += left_off;
			ncparams->rgrc[0].top += 27;
			// ncparams->rgrc[0].right -= right_off;
			// ncparams->rgrc[0].bottom -= bottom_off;
			return 0;
		}
		break;
	}

	case WM_NCHITTEST:
	{
		INT x = GET_X_LPARAM(lparam);
		INT y = GET_Y_LPARAM(lparam);
		//return HTCLOSE;
		//return HTMAXBUTTON;
		//return HTMINBUTTON;
		x = 2;
		break;
	}
	}
	return DefWindowProc(m_hwnd, uMsg, wparam, lparam);
}