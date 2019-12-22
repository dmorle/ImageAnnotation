#include "WinMain.h"



#define TOCOLORREF(c) RGB(c.r * 255, c.g * 255, c.b * 255)
#define TOD2D1RECTF(rc) D2D1::RectF(rc.left, rc.top, rc.right, rc.bottom)

namespace NCFunc{
	HWND hwnd;

	/**********************************
	**								 **
	** Start of non-client functions **
	**								 **
	**********************************/

	void onCloseClick()
	{
		PostMessage(hwnd, WM_CLOSE, 0, 0);
	}

	void onMaxClick()
	{
		PostMessage(hwnd, WM_SIZE, SIZE_MAXIMIZED, 0); // TODO: check if LPARAM needs to be set for this message
	}

	void onRestoreDownClick()
	{
		PostMessage(hwnd, WM_SIZE, SIZE_RESTORED, 0); // TODO: check if LPARAM needs to be set for this message
	}

	void onMinClick()
	{
		PostMessage(hwnd, WM_SIZE, SIZE_MINIMIZED, 0); // TODO: check if LPARAM needs to be set for this message
	}

	void onFileClick()
	{

	}

	void onEditClick()
	{

	}

	void onPreferencesClick()
	{

	}
}

namespace WFunc{	// Creating a namespace local to this file to handle widget component painting

	HWND hwnd;

	void paintSelf(PRECT pRc)
	{
		InvalidateRect(hwnd, pRc, TRUE);
	}

}

void MainWindow::savePalette(std::string path)
{

}

void MainWindow::loadPalette(std::string path)
{

}

void MainWindow::CreateDefaultLayout(D2D1_SIZE_F size)
{
	PRECT pRc = new RECT{ 0, 0, (LONG)size.width, (LONG)size.height };
	Widget* npWidget = new Widget(pRc, this);

	// creating a test component
	npWidget->addComponent(
		new WCMP::EmptyButton(
			this->pRenderTarget,
			new D2D1_RECT_F{ 10, 10, 30, 30 },
			pRc,
			this->palette,
			NULL,
			WFunc::paintSelf
		)
	);

	// adding the widget to the window
	widgets.push_back(npWidget);
}

// Recalculate drawing layout when the size of the window changes.
void MainWindow::CalculateLayout(D2D1_SIZE_F prev)
{
	if (pRenderTarget != NULL)
	{
		D2D1_SIZE_F size = pRenderTarget->GetSize();

		if (!widgets.size()) {
			CreateDefaultLayout(size);
		}

		else {
			// resize current layout
			widgets[0]->resize(0, 0, size.width, size.height);
		}
	}
}

void MainWindow::CreateNCButtons()
{
	RECT rcWin;
	GetWindowRect(m_hwnd, &rcWin);

	{
		// creating the File button

		RECT rc{
			51,
			2,
			99,
			top_off
		};

		ncComponents.push_back(new
			NCCMP::NCTextButton(
				(COLORREF)NULL,
				TOCOLORREF(palette[appPalette::WIDGET_BACK]),
				TOCOLORREF(palette[appPalette::PASSIVE]),
				TOCOLORREF(palette[appPalette::ACTIVE]),
				TOCOLORREF(palette[appPalette::TEXT_COLOR]),
				(COLORREF)NULL,
				(COLORREF)NULL,
				(COLORREF)NULL,
				&NCFunc::onFileClick,
				rc,
				(LPCSTR)"File"
			)
		);
	}

	{
		// creating the Edit button

		RECT rc{
			101,
			2,
			149,
			top_off
		};

		ncComponents.push_back(new
			NCCMP::NCTextButton(
			(COLORREF)NULL,
				TOCOLORREF(palette[appPalette::WIDGET_BACK]),
				TOCOLORREF(palette[appPalette::PASSIVE]),
				TOCOLORREF(palette[appPalette::ACTIVE]),
				TOCOLORREF(palette[appPalette::TEXT_COLOR]),
				(COLORREF)NULL,
				(COLORREF)NULL,
				(COLORREF)NULL,
				&NCFunc::onEditClick,
				rc,
				(LPCSTR)"Edit"
			)
		);
	}

	{
		// creating the Preferences button

		RECT rc{
			151,
			2,
			249,
			top_off
		};

		ncComponents.push_back(new
			NCCMP::NCTextButton(
			(COLORREF)NULL,
				TOCOLORREF(palette[appPalette::WIDGET_BACK]),
				TOCOLORREF(palette[appPalette::PASSIVE]),
				TOCOLORREF(palette[appPalette::ACTIVE]),
				TOCOLORREF(palette[appPalette::TEXT_COLOR]),
				(COLORREF)NULL,
				(COLORREF)NULL,
				(COLORREF)NULL,
				&NCFunc::onPreferencesClick,
				rc,
				(LPCSTR)"Preferences"
			)
		);
	}

	{
		// creating the close button

		RECT rc{
			rcWin.right - rcWin.left - 49,
			2,
			rcWin.right - rcWin.left - 2,
			top_off
		};


		ncComponents.push_back(new
			NCCMP::CloseButton(
				(COLORREF)NULL,
				TOCOLORREF(palette[appPalette::WIDGET_BACK]),
				TOCOLORREF(palette[appPalette::PASSIVE]),
				TOCOLORREF(palette[appPalette::ACTIVE]),
				TOCOLORREF(palette[appPalette::TEXT_COLOR]),
				(COLORREF)NULL,
				(COLORREF)NULL,
				(COLORREF)NULL,
				&NCFunc::onCloseClick,
				rc
			)
		);
	}

	{
		// creating the max button

		RECT rc{
			rcWin.right - rcWin.left - 99,
			2,
			rcWin.right - rcWin.left - 51,
			top_off
		};


		ncComponents.push_back(new
			NCCMP::MaxButton(
				(COLORREF)NULL,
				TOCOLORREF(palette[appPalette::WIDGET_BACK]),
				TOCOLORREF(palette[appPalette::PASSIVE]),
				TOCOLORREF(palette[appPalette::ACTIVE]),
				TOCOLORREF(palette[appPalette::TEXT_COLOR]),
				(COLORREF)NULL,
				(COLORREF)NULL,
				(COLORREF)NULL,
				&NCFunc::onMaxClick,
				rc
			)
		);
	}

	{
		// creating the min button

		RECT rc{
			rcWin.right - rcWin.left - 149,
			2,
			rcWin.right - rcWin.left - 101,
			top_off
		};


		ncComponents.push_back(new
			NCCMP::MinButton(
				(COLORREF)NULL,
				TOCOLORREF(palette[appPalette::WIDGET_BACK]),
				TOCOLORREF(palette[appPalette::PASSIVE]),
				TOCOLORREF(palette[appPalette::ACTIVE]),
				TOCOLORREF(palette[appPalette::TEXT_COLOR]),
				(COLORREF)NULL,
				(COLORREF)NULL,
				(COLORREF)NULL,
				&NCFunc::onMinClick,
				rc
			)
		);
	}
}

void MainWindow::DiscardNCButtons()
{
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
		hr = pRenderTarget->CreateSolidColorBrush(palette[appPalette::TEXT_COLOR], &brushes.text);
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

		for (auto& e : widgets)
			e->render(pRenderTarget);

		if (activeWidget)
			activeWidget->render(pRenderTarget);

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

	BOOL redraw = FALSE;

	for (auto e : ncComponents)
		if (e->mouseleave())
			redraw = TRUE;

	if (redraw)
		SetWindowPos(m_hwnd, 0, 0, 0, 0, 0,
			SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);
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
		top_off
	};

	HDC hdc;
	if (wparam == 0 || wparam == 1)
		hdc = GetWindowDC(m_hwnd);
	else
		hdc = GetDCEx(m_hwnd, (HRGN)wparam, DCX_WINDOW | DCX_CACHE | DCX_LOCKWINDOWUPDATE | DCX_INTERSECTRGN);

	if (hdc) {
		HDC hbuffer = CreateCompatibleDC(hdc);

		HBITMAP hbmp = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
		HBITMAP holdbmp = (HBITMAP)SelectObject(hbuffer, hbmp);

		HBRUSH hbr = CreateSolidBrush(TOCOLORREF(palette[appPalette::	BACKGROUND]));
		FillRect(hbuffer, &rc, hbr);
		DeleteObject(hbr);

		for (auto e : ncComponents)
			e->display(hbuffer);
		
		BitBlt(hdc, 0, 0, rc.right, rc.bottom, hbuffer, 0, 0, SRCCOPY);

		SelectObject(hbuffer, holdbmp);
		DeleteObject(hbmp);

		DeleteDC(hbuffer);
		ReleaseDC(m_hwnd, hdc);
	}
}

void MainWindow::ncMoveMove(WPARAM wparam, LPARAM lparam)
{
	RECT rcWin;
	GetWindowRect(m_hwnd, &rcWin);

	POINT p{ GET_X_LPARAM(lparam) - rcWin.left, GET_Y_LPARAM(lparam) - rcWin.top };

	for (auto e : ncComponents)
		e->mousemove(p);

	RedrawWindow(m_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_NOERASE | RDW_UPDATENOW);
}

void MainWindow::ncLDown(WPARAM wparam, LPARAM lparam)
{
	RECT rcWin;
	GetWindowRect(m_hwnd, &rcWin);

	POINT p{ GET_X_LPARAM(lparam) - rcWin.left, GET_Y_LPARAM(lparam) - rcWin.top };

	for (auto e : ncComponents)
		e->LDown(p);

	SetWindowPos(m_hwnd, 0, 0, 0, 0, 0,
		SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void MainWindow::RepaintRect(PRECT pRc, BOOL erase)
{
	InvalidateRect(m_hwnd, pRc, erase);
}

void MainWindow::ncLUp(WPARAM wparam, LPARAM lparam)
{
	RECT rcWin;
	GetWindowRect(m_hwnd, &rcWin);

	POINT p{ GET_X_LPARAM(lparam) - rcWin.left, GET_Y_LPARAM(lparam) - rcWin.top };

	for (auto e : ncComponents)
		e->LUp(p);

	SetWindowPos(m_hwnd, 0, 0, 0, 0, 0,
		SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);
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

		// creating the non client components
		NCFunc::hwnd = m_hwnd;
		CreateNCButtons();

		// Creating the widget componenetss
		WFunc::hwnd = m_hwnd;
		
		return 0;

	case WM_DESTROY:
		DiscardGraphicsResources();
		SafeRelease(&pFactory);
		PostQuitMessage(0);
		return 0;

	case WM_ERASEBKGND:
		return 1;

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
			ncparams->rgrc[0].left += left_off;
			ncparams->rgrc[0].top += top_off;
			ncparams->rgrc[0].right -= right_off;
			ncparams->rgrc[0].bottom -= bottom_off;
			return 0;
		}
		break;
	}

	case WM_NCHITTEST:
	{
		RECT rcWin;
		GetWindowRect(m_hwnd, &rcWin);

		INT x = GET_X_LPARAM(lparam);
		INT y = GET_Y_LPARAM(lparam);

		// temp code
		if (y < rcWin.top + top_off)
			return HTCAPTION;
		return HTCLIENT;
	}

	case WM_NCMOUSEMOVE:
		ncMoveMove(wparam, lparam);
		return 0;

	case WM_NCLBUTTONUP:
		ncLUp(wparam, lparam);
		return 0;

	case WM_NCLBUTTONDOWN:
		ncLDown(wparam, lparam);
		return 0;
	}
	return DefWindowProc(m_hwnd, uMsg, wparam, lparam);
}