#include "WinMain.h"
#include <cassert>



namespace WFunc {	// Creating a namespace local to this file to handle widget component painting

	HWND hwnd;

	void paintSelf(PRECT pRc)
	{
		InvalidateRect(hwnd, pRc, TRUE);
	}

}

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
		if (IsMaximized(hwnd))
			PostMessage(hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
		else
			PostMessage(hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	}

	void onMinClick()
	{
		PostMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
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

void MainWindow::savePalette(std::string path)
{

}

void MainWindow::loadPalette(std::string path)
{

}

void MainWindow::CreateDefaultLayout(D2D1_SIZE_U size)
{
	Container* widgetContainer = new Container(NULL, new RECT{ 0, 0, (LONG)size.width, (LONG)size.height });
	widgetContainer->addPanel(new WidgetPanel(widgetContainer, new RECT{ 0, 0, (LONG)size.width, (LONG)size.height }, 1));

	pAP = widgetContainer;
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
				TOCOLORREF(pPalette->widgetBack),
				TOCOLORREF(pPalette->passive),
				TOCOLORREF(pPalette->active),
				TOCOLORREF(pPalette->text),
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
				TOCOLORREF(pPalette->widgetBack),
				TOCOLORREF(pPalette->passive),
				TOCOLORREF(pPalette->active),
				TOCOLORREF(pPalette->text),
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
				TOCOLORREF(pPalette->widgetBack),
				TOCOLORREF(pPalette->passive),
				TOCOLORREF(pPalette->active),
				TOCOLORREF(pPalette->text),
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
				TOCOLORREF(pPalette->widgetBack),
				TOCOLORREF(pPalette->passive),
				TOCOLORREF(pPalette->active),
				TOCOLORREF(pPalette->text),
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
				TOCOLORREF(pPalette->widgetBack),
				TOCOLORREF(pPalette->passive),
				TOCOLORREF(pPalette->active),
				TOCOLORREF(pPalette->text),
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
				TOCOLORREF(pPalette->widgetBack),
				TOCOLORREF(pPalette->passive),
				TOCOLORREF(pPalette->active),
				TOCOLORREF(pPalette->text),
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
	if (!pPalette)
		pPalette = new appPalette();

	if (!pCursors)
		pCursors = new stdCursors();

	if (!pCursors->arrow)
		pCursors->arrow = LoadCursor(NULL, IDC_ARROW);
	if (!pCursors->sizens)
		pCursors->sizens = LoadCursor(NULL, IDC_SIZENS);
	if (!pCursors->sizewe)
		pCursors->sizewe = LoadCursor(NULL, IDC_SIZEWE);

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

	if (!pBrushes)
		pBrushes = new stdBrushes();

	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->background, &pBrushes->background);

	if (SUCCEEDED(hr)) {
		D2D1_COLOR_F delColor = pPalette->background;
		delColor.a = 0.3f;
		hr = pRenderTarget->CreateSolidColorBrush(delColor, &pBrushes->preDeletion);
	}

	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->widgetBack, &pBrushes->widgetBack);

	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->passive, &pBrushes->passive);

	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->active, &pBrushes->active);

	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->text, &pBrushes->text);
	return hr;
}

void MainWindow::DiscardGraphicsResources()
{
	SafeRelease(&pRenderTarget);
	pBrushes->release();
}

LRESULT MainWindow::onCreate()
{
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &pFactory)))
		return -1;  // Fail CreateWindowEx.

	if (FAILED(CoInitializeEx(NULL, COINIT_MULTITHREADED)))
		return -1;
	if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, (LPVOID*)&pWicFactory)))
		return -1;

	if (FAILED(CreateGraphicsResources()))
		return -1;

	// creating the non client components
	NCFunc::hwnd = m_hwnd;
	CreateNCButtons();

	// Creating the widget componenetss
	WFunc::hwnd = m_hwnd;

	InvalidateRect(m_hwnd, NULL, FALSE);

	return 0;
}

void MainWindow::Paint()
{
	HRESULT hr = CreateGraphicsResources();
	if (SUCCEEDED(hr))
	{
		PAINTSTRUCT ps;
		BeginPaint(m_hwnd, &ps);
		pRenderTarget->BeginDraw();

		pRenderTarget->Clear(pPalette->background);
		pAP->display();

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
		D2D1_RECT_L rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size = D2D1_SIZE_U{ (UINT32)rc.right, (UINT32)rc.bottom };

		if (!pAP)
			CreateDefaultLayout(size);

		pRenderTarget->Resize(size);

		pAP->resizeX(0, size.width);
		pAP->resizeY(0, size.height);

		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}

void MainWindow::MouseMove(WPARAM wparam, LPARAM lparam)
{
	SetCursor(pCursors->arrow);

	POINT p { GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };

	// client region code
	if (resizingInfo == resizeInfo::NONE) {
		// TODO: figure out a way to handle top resizing
		if (
			p.x < edgeSpace ||
			p.x > pRenderTarget->GetSize().width - edgeSpace
			)
			SetCursor(pCursors->sizewe);
		else if (
			p.y > pRenderTarget->GetSize().height - edgeSpace
			)
			SetCursor(pCursors->sizens);
		else
			pAP->MouseMove(wparam, p);
	}
	else {
		RECT rc;
		BOOL result = GetWindowRect(m_hwnd, &rc);
		assert(!result);
		SIZE size{ rc.right - rc.left, rc.bottom - rc.top };

		LONG nDim;
		switch (resizingInfo) {
		case resizeInfo::LEFT:
			nDim = max(size.cx - p.x, pAP->getMinWidth());
			pAP->resizeX(0, nDim);
			SetWindowPos(m_hwnd, HWND_TOP, rc.right - nDim, rc.top, nDim, size.cy, NULL);
			break;
		case resizeInfo::TOP:
			nDim = max(size.cy - p.y, pAP->getMinHeight());
			pAP->resizeY(0, nDim);
			SetWindowPos(m_hwnd, HWND_TOP, rc.left, rc.bottom - nDim, size.cx, nDim, NULL);
			break;
		case resizeInfo::RIGHT:
			nDim = max(p.x, pAP->getMinWidth());
			pAP->resizeX(0, nDim);
			SetWindowPos(m_hwnd, HWND_TOP, rc.left, rc.top, nDim, size.cy, NULL);
			break;
		case resizeInfo::BOTTOM:
			nDim = max(p.y, pAP->getMinHeight());
			pAP->resizeY(0, nDim);
			SetWindowPos(m_hwnd, HWND_TOP, rc.left, rc.top, size.cx, nDim, NULL);
			break;
		}
	}
	
	// non client region code

	BOOL redraw = FALSE;

	for (auto e : ncComponents)
		if (e->mouseleave())
			redraw = TRUE;

	if (redraw)
		SetWindowPos(m_hwnd, 0, 0, 0, 0, 0,
			SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void MainWindow::LUp(WPARAM wparam, LPARAM lparam)
{
	POINT p { GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };
	
	if (resizingInfo == resizeInfo::NONE) {
		SetCursor(pCursors->arrow);
		pAP->LUp(wparam, p);
	}
	else {
		RECT rc;
		BOOL result = GetWindowRect(m_hwnd, &rc);
		assert(!result);
		SIZE size{ rc.right - rc.left, rc.bottom - rc.top };

		LONG nDim;
		switch (resizingInfo) {
		case resizeInfo::LEFT:
			nDim = max(size.cx - p.x, pAP->getMinWidth());
			pAP->resizeX(0, nDim);
			SetWindowPos(m_hwnd, HWND_TOP, rc.right - nDim, rc.top, nDim, size.cy, NULL);
			break;
		case resizeInfo::TOP:
			nDim = max(size.cy - p.y, pAP->getMinHeight());
			pAP->resizeY(0, nDim);
			SetWindowPos(m_hwnd, HWND_TOP, rc.left, rc.bottom - nDim, size.cx, nDim, NULL);
			break;
		case resizeInfo::RIGHT:
			nDim = max(p.x, pAP->getMinWidth());
			pAP->resizeX(0, nDim);
			SetWindowPos(m_hwnd, HWND_TOP, rc.left, rc.top, nDim, size.cy, NULL);
			break;
		case resizeInfo::BOTTOM:
			nDim = max(p.y, pAP->getMinHeight());
			pAP->resizeY(0, nDim);
			SetWindowPos(m_hwnd, HWND_TOP, rc.left, rc.top, size.cx, nDim, NULL);
			break;
		}

		resizingInfo = resizeInfo::NONE;
	}
}

void MainWindow::LDown(WPARAM wparam, LPARAM lparam)
{
	POINT p{ GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };

	// checking for window resizing
	// TODO: figure out a way to handle top resizing
	if (p.x < edgeSpace) {
		SetCursor(pCursors->sizewe);
		resizingInfo = resizeInfo::LEFT;
	}
	else if (p.x > pRenderTarget->GetSize().width - edgeSpace) {
		SetCursor(pCursors->sizens);
		resizingInfo = resizeInfo::RIGHT;
	}
	else if (p.y > pRenderTarget->GetSize().height - edgeSpace) {
		SetCursor(pCursors->sizewe);
		resizingInfo = resizeInfo::BOTTOM;
	}

	// normal functionality
	else {
		SetCursor(pCursors->arrow);
		pAP->LDown(wparam, p);
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

		HBRUSH hbr = CreateSolidBrush(TOCOLORREF(pPalette->background));
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
		return onCreate();

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