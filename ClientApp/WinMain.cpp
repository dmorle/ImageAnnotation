#include "WinMain.h"
#include <cassert>



namespace WFunc {	// Creating a namespace local to this file to handle widget component painting

	HWND hwnd;

	void paintSelf(PRECT pRc)
	{
		InvalidateRect(hwnd, pRc, FALSE);
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
		Parameters::pAO = new FileMenu();
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

void MainWindow::CreateDefaultLayout(LONG width, LONG height)
{
	Container* widgetContainer = new Container(NULL, new RECT{ edgeSpace, edgeSpace, width - edgeSpace, height - edgeSpace - top_off });

	width -= 2 * edgeSpace;
	height -= 2 * edgeSpace + top_off;

	widgetContainer->addPanel(new WidgetPanel(widgetContainer, new RECT{ 0, 0, width - 600, height }, 1, 50, 25));

	Container* rightContainer = new Container(widgetContainer, new RECT{ width - 600, 0, width, height });
	rightContainer->addPanel(new WidgetPanel(rightContainer, new RECT{ 0, 0, 600, 300 }, 2, 50, 25));
	rightContainer->addPanel(new WidgetPanel(rightContainer, new RECT{ 0, 300, 600, height }, 3, 50, 25));

	widgetContainer->addPanel(rightContainer);

	pAP = pMainPanel = widgetContainer;
}

void MainWindow::CreateNCButtons()
{
	RECT rcWin;
	GetWindowRect(m_hwnd, &rcWin);

	{
		// creating the File button

		RECT rc{
			50 + edgeSpace,
			edgeSpace,
			100 - edgeSpace,
			top_off
		};

		ncCmp.push_back(new
			NCCMP::NCTextButton(
				(COLORREF)NULL,
				TOCOLORREF(pPalette->mainCmp1),
				TOCOLORREF(pPalette->mainActive1),
				TOCOLORREF(pPalette->mainPressed),
				TOCOLORREF(pPalette->mainText1),
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
			100 + edgeSpace,
			edgeSpace,
			150 - edgeSpace,
			top_off
		};

		ncCmp.push_back(new
			NCCMP::NCTextButton(
				(COLORREF)NULL,
				TOCOLORREF(pPalette->mainCmp1),
				TOCOLORREF(pPalette->mainActive1),
				TOCOLORREF(pPalette->mainPressed),
				TOCOLORREF(pPalette->mainText1),
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
			150 + edgeSpace,
			edgeSpace,
			250 - edgeSpace,
			top_off
		};

		ncCmp.push_back(new
			NCCMP::NCTextButton(
				(COLORREF)NULL,
				TOCOLORREF(pPalette->mainCmp1),
				TOCOLORREF(pPalette->mainActive1),
				TOCOLORREF(pPalette->mainPressed),
				TOCOLORREF(pPalette->mainText1),
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
			rcWin.right - rcWin.left - 50 + edgeSpace,
			edgeSpace,
			rcWin.right - rcWin.left - 2 * edgeSpace,
			top_off
		};


		ncCmp.push_back(new
			NCCMP::CloseButton(
				(COLORREF)NULL,
				TOCOLORREF(pPalette->mainCmp1),
				TOCOLORREF(pPalette->mainActive1),
				TOCOLORREF(pPalette->mainPressed),
				TOCOLORREF(pPalette->mainText1),
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
			rcWin.right - rcWin.left - 100 + edgeSpace,
			edgeSpace,
			rcWin.right - rcWin.left - 50 - edgeSpace,
			top_off
		};


		ncCmp.push_back(new
			NCCMP::MaxButton(
				(COLORREF)NULL,
				TOCOLORREF(pPalette->mainCmp1),
				TOCOLORREF(pPalette->mainActive1),
				TOCOLORREF(pPalette->mainPressed),
				TOCOLORREF(pPalette->mainText1),
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
			rcWin.right - rcWin.left - 150 + edgeSpace,
			edgeSpace,
			rcWin.right - rcWin.left - 100 - edgeSpace,
			top_off
		};


		ncCmp.push_back(new
			NCCMP::MinButton(
				(COLORREF)NULL,
				TOCOLORREF(pPalette->mainCmp1),
				TOCOLORREF(pPalette->mainActive1),
				TOCOLORREF(pPalette->mainPressed),
				TOCOLORREF(pPalette->mainText1),
				(COLORREF)NULL,
				(COLORREF)NULL,
				(COLORREF)NULL,
				&NCFunc::onMinClick,
				rc
			)
		);
	}

	minNCWidth =
		150 + // min + max + close
		50 +  // free space
		250;  // file + edit + preferences
}

void MainWindow::DiscardNCButtons()
{
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
			&pRenderTarget
		);
	}

	if (!pBrushes)
		pBrushes = new stdBrushes();

	// main brushes
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->mainBack, &pBrushes->mainBack);
	if (SUCCEEDED(hr)) {
		D2D1_COLOR_F delColor = pPalette->mainBack;
		delColor.a = 0.3f;
		hr = pRenderTarget->CreateSolidColorBrush(delColor, &pBrushes->mainPredel);
	}
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->mainBorder, &pBrushes->mainBorder);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->mainText1, &pBrushes->mainText1);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->mainText2, &pBrushes->mainText2);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->mainText3, &pBrushes->mainText3);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->mainCmp1, &pBrushes->mainCmp1);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->mainCmp2, &pBrushes->mainCmp2);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->mainCmp3, &pBrushes->mainCmp3);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->mainActive1, &pBrushes->mainActive1);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->mainActive2, &pBrushes->mainActive2);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->mainActive3, &pBrushes->mainActive3);
	if (SUCCEEDED(hr)) {
		D2D1_COLOR_F delColor = pPalette->mainActive1;
		delColor.a = 0.3f;
		hr = pRenderTarget->CreateSolidColorBrush(delColor, &pBrushes->mainPresel1);
	}
	if (SUCCEEDED(hr)) {
		D2D1_COLOR_F delColor = pPalette->mainActive2;
		delColor.a = 0.3f;
		hr = pRenderTarget->CreateSolidColorBrush(delColor, &pBrushes->mainPresel2);
	}
	if (SUCCEEDED(hr)) {
		D2D1_COLOR_F delColor = pPalette->mainActive3;
		delColor.a = 0.3f;
		hr = pRenderTarget->CreateSolidColorBrush(delColor, &pBrushes->mainPresel3);
	}
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->mainPressed, &pBrushes->mainPressed);

	// widget brushes
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->widgetBack, &pBrushes->widgetBack);
	if (SUCCEEDED(hr)) {
		D2D1_COLOR_F delColor = pPalette->widgetBack;
		delColor.a = 0.3f;
		hr = pRenderTarget->CreateSolidColorBrush(delColor, &pBrushes->widgetPredel);
	}
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->widgetBorder, &pBrushes->widgetBorder);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->widgetText1, &pBrushes->widgetText1);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->widgetText2, &pBrushes->widgetText2);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->widgetText3, &pBrushes->widgetText3);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->widgetCmp1, &pBrushes->widgetCmp1);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->widgetCmp2, &pBrushes->widgetCmp2);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->widgetCmp3, &pBrushes->widgetCmp3);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->widgetActive1, &pBrushes->widgetActive1);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->widgetActive2, &pBrushes->widgetActive2);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->widgetActive3, &pBrushes->widgetActive3);
	if (SUCCEEDED(hr)) {
		D2D1_COLOR_F delColor = pPalette->widgetActive1;
		delColor.a = 0.3f;
		hr = pRenderTarget->CreateSolidColorBrush(delColor, &pBrushes->widgetPresel1);
	}
	if (SUCCEEDED(hr)) {
		D2D1_COLOR_F delColor = pPalette->widgetActive2;
		delColor.a = 0.3f;
		hr = pRenderTarget->CreateSolidColorBrush(delColor, &pBrushes->widgetPresel2);
	}
	if (SUCCEEDED(hr)) {
		D2D1_COLOR_F delColor = pPalette->widgetActive3;
		delColor.a = 0.3f;
		hr = pRenderTarget->CreateSolidColorBrush(delColor, &pBrushes->widgetPresel3);
	}
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->widgetPressed, &pBrushes->widgetPressed);

	// overlay brushes
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->overlayBack, &pBrushes->overlayBack);
	if (SUCCEEDED(hr)) {
		D2D1_COLOR_F delColor = pPalette->overlayBack;
		delColor.a = 0.3f;
		hr = pRenderTarget->CreateSolidColorBrush(delColor, &pBrushes->overlayPredel);
	}
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->overlayBorder, &pBrushes->overlayBorder);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->overlayText1, &pBrushes->overlayText1);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->overlayText2, &pBrushes->overlayText2);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->overlayText3, &pBrushes->overlayText3);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->overlayCmp1, &pBrushes->overlayCmp1);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->overlayCmp2, &pBrushes->overlayCmp2);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->overlayCmp3, &pBrushes->overlayCmp3);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->overlayActive1, &pBrushes->overlayActive1);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->overlayActive2, &pBrushes->overlayActive2);
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->overlayActive3, &pBrushes->overlayActive3);
	if (SUCCEEDED(hr)) {
		D2D1_COLOR_F delColor = pPalette->overlayActive1;
		delColor.a = 0.3f;
		hr = pRenderTarget->CreateSolidColorBrush(delColor, &pBrushes->overlayPresel1);
	}
	if (SUCCEEDED(hr)) {
		D2D1_COLOR_F delColor = pPalette->overlayActive2;
		delColor.a = 0.3f;
		hr = pRenderTarget->CreateSolidColorBrush(delColor, &pBrushes->overlayPresel2);
	}
	if (SUCCEEDED(hr)) {
		D2D1_COLOR_F delColor = pPalette->overlayActive3;
		delColor.a = 0.3f;
		hr = pRenderTarget->CreateSolidColorBrush(delColor, &pBrushes->overlayPresel3);
	}
	if (SUCCEEDED(hr))
		hr = pRenderTarget->CreateSolidColorBrush(pPalette->overlayPressed, &pBrushes->overlayPressed);

	pStdGs = new GRAPHICSTRUCT();

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
	if (FAILED(DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(pDWriteFactory),
		reinterpret_cast<IUnknown**>(&pDWriteFactory)
	)))
		return -1;

	hwnd = m_hwnd;

	// filling the Parameters class

	// appPalette
	if (!pPalette)
		pPalette = new appPalette();

	// stdCursors
	if (!pCursors)
		pCursors = new stdCursors();

	if (!pCursors->arrow)
		pCursors->arrow = LoadCursor(NULL, IDC_ARROW);
	if (!pCursors->sizens)
		pCursors->sizens = LoadCursor(NULL, IDC_SIZENS);
	if (!pCursors->sizewe)
		pCursors->sizewe = LoadCursor(NULL, IDC_SIZEWE);

	if (!pTextFormats)
		pTextFormats = new TextFormat();

	if (FAILED(pTextFormats->init()))
		return -1;

	if (FAILED(CreateGraphicsResources()))
		return -1;

	// creating the non client components
	NCFunc::hwnd = m_hwnd;
	CreateNCButtons();

	// Creating the widget componenets
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

		if (fullPaint) {
			pRenderTarget->Clear(pPalette->mainBack);
			pMainPanel->display();
			fullPaint = FALSE;
		}
		else
			pAP->display();

		if (pAO)
			pAO->display();

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
	BOOL result = GetWindowRect(m_hwnd, &rect);
	assert(result);
	rgn = CreateRectRgn(0, 0, rect.right, rect.bottom);
	SetWindowRgn(m_hwnd, rgn, TRUE);
	DeleteObject(rgn);

	if (pRenderTarget != NULL)
	{
		D2D1_RECT_L rc;
		GetClientRect(m_hwnd, &rc);

		D2D1_SIZE_U size{ (UINT32)rc.right, (UINT32)rc.bottom };

		if (!pAP)
			CreateDefaultLayout(rc.right, rc.bottom);

		pRenderTarget->Resize(size);

		pMainPanel->resizeX(edgeSpace, rc.right - edgeSpace);
		pMainPanel->resizeY(edgeSpace, rc.bottom - edgeSpace);

		for (int i = 3; i < 6; i++)
			ncCmp[i]->setTrans(rc.right - 50 * (i - 2));

		fullPaint = TRUE;
		InvalidateRect(m_hwnd, NULL, FALSE);
	}
}

void MainWindow::MouseMove(WPARAM wparam, LPARAM lparam)
{
	SetCursor(pCursors->arrow);

	POINT p { GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };

	// client region code

	if (!pResizingInfo) {
		// TODO: figure out a way to handle top resizing
		if (passMouse) {
			if (pAO)
				pAO->MouseMove(wparam, p);
			else
				pAP->MouseMove(wparam, p);
		}
		else {
			if (
				p.x <= 2 * edgeSpace ||
				p.x >= pRenderTarget->GetSize().width - 2 * edgeSpace
				)
				SetCursor(pCursors->sizewe);
			else if (
				p.y >= pRenderTarget->GetSize().height - 2 * edgeSpace
				)
				SetCursor(pCursors->sizens);
			else {
				if (pAO)
					pAO->MouseMove(wparam, p);
				else
					pAP->MouseMove(wparam, p);
			}
		}
	}
	else {
		RECT rc;
		BOOL result = GetWindowRect(m_hwnd, &rc);
		assert(result);
		SIZE size{ rc.right - rc.left, rc.bottom - rc.top };

		LONG nDim;
		switch (pResizingInfo->edge) {
		case resizeInfo::LEFT:
			nDim = max(
				minNCWidth,
				max(
					size.cx - p.x + pResizingInfo->edgeDist,
					pMainPanel->getMinWidth() + 2 * edgeSpace
				)
			);
			SetWindowPos(m_hwnd, NULL, rc.right - nDim, rc.top, nDim, size.cy, NULL);
			break;
		case resizeInfo::TOP:
			nDim = max(size.cy - p.y + pResizingInfo->edgeDist, pMainPanel->getMinHeight() + top_off + 2 * edgeSpace);
			SetWindowPos(m_hwnd, NULL, rc.left, rc.bottom - nDim, size.cx, nDim, NULL);
			break;
		case resizeInfo::RIGHT:
			nDim = max(
				minNCWidth,
				max(
					p.x + pResizingInfo->edgeDist,
					pMainPanel->getMinWidth() + 2 * edgeSpace
				)
			);
			SetWindowPos(m_hwnd, NULL, rc.left, rc.top, nDim, size.cy, NULL);
			break;
		case resizeInfo::BOTTOM:
			nDim = max(p.y + pResizingInfo->edgeDist, pMainPanel->getMinHeight() + top_off + 2 * edgeSpace);
			SetWindowPos(m_hwnd, NULL, rc.left, rc.top, size.cx, nDim, NULL);
			break;
		}

		PostMessage(m_hwnd, WM_NCACTIVATE, 0, 0);
	}
	
	// non client region code

	BOOL redraw = FALSE;

	for (auto e : ncCmp)
		if (e->mouseleave())
			redraw = TRUE;

	if (redraw)
		SetWindowPos(m_hwnd, 0, 0, 0, 0, 0,
			SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void MainWindow::LDown(WPARAM wparam, LPARAM lparam)
{
	POINT p{ GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };

	// checking for window resizing
	// TODO: figure out a way to handle top resizing
	if (p.x <= 2 * edgeSpace) {
		pResizingInfo = new resizeInfo{ resizeInfo::LEFT, p.x };
		SetCapture(m_hwnd);
		SetCursor(pCursors->sizewe);
	}
	else if (p.x >= pRenderTarget->GetSize().width - 2 * edgeSpace) {
		pResizingInfo = new resizeInfo{ resizeInfo::RIGHT, (LONG)pRenderTarget->GetSize().width - p.x };
		SetCapture(m_hwnd);
		SetCursor(pCursors->sizewe);
	}
	else if (p.y >= pRenderTarget->GetSize().height - 2 * edgeSpace) {
		pResizingInfo = new resizeInfo{ resizeInfo::BOTTOM, (LONG)pRenderTarget->GetSize().height + top_off - p.y };
		SetCapture(m_hwnd);
		SetCursor(pCursors->sizens);
	}

	// normal functionality
	else {
		SetCursor(pCursors->arrow);

		if (pAO)
			pAO->LDown(wparam, p);
		else
			pAP->LDown(wparam, p);
	}
}

void MainWindow::LUp(WPARAM wparam, LPARAM lparam)
{
	POINT p { GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };
	
	if (!pResizingInfo) {
		SetCursor(pCursors->arrow);

		if (pAO)
			pAO->LUp(wparam, p);
		else
			pAP->LUp(wparam, p);
	}
	else {
		RECT rc;
		BOOL result = GetWindowRect(m_hwnd, &rc);
		assert(result);
		SIZE size{ rc.right - rc.left, rc.bottom - rc.top };

		LONG nDim;
		switch (pResizingInfo->edge) {
		case resizeInfo::LEFT:
			nDim = max(
				minNCWidth,
				max(
					size.cx - p.x + pResizingInfo->edgeDist,
					pMainPanel->getMinWidth() + 2 * edgeSpace
				)
			);
			SetWindowPos(m_hwnd, HWND_TOP, rc.right - nDim, rc.top, nDim, size.cy, NULL);
			break;
		case resizeInfo::TOP:
			nDim = max(size.cy - p.y + pResizingInfo->edgeDist, pMainPanel->getMinHeight() + top_off + 2 * edgeSpace);
			SetWindowPos(m_hwnd, HWND_TOP, rc.left, rc.bottom - nDim, size.cx, nDim, NULL);
			break;
		case resizeInfo::RIGHT:
			nDim = max(
				minNCWidth,
				max(
					p.x + pResizingInfo->edgeDist,
					pMainPanel->getMinWidth() + 2 * edgeSpace
				)
			);
			SetWindowPos(m_hwnd, HWND_TOP, rc.left, rc.top, nDim, size.cy, NULL);
			break;
		case resizeInfo::BOTTOM:
			nDim = max(p.y + pResizingInfo->edgeDist, pMainPanel->getMinHeight() + top_off + 2 * edgeSpace);
			SetWindowPos(m_hwnd, HWND_TOP, rc.left, rc.top, size.cx, nDim, NULL);
			break;
		}

		delete pResizingInfo;
		pResizingInfo = NULL;
		ReleaseCapture();

		PostMessage(m_hwnd, WM_NCACTIVATE, 0, 0);
	}
}

void MainWindow::RDown(WPARAM wparam, LPARAM lparam)
{
}

void MainWindow::RUp(WPARAM wparam, LPARAM lparam)
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

		HBRUSH hbr = CreateSolidBrush(TOCOLORREF(pPalette->mainBack));
		FillRect(hbuffer, &rc, hbr);
		DeleteObject(hbr);

		for (auto e : ncCmp)
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

	for (auto e : ncCmp)
		e->mousemove(p);

	RedrawWindow(m_hwnd, NULL, NULL, RDW_INVALIDATE | RDW_FRAME | RDW_NOERASE | RDW_UPDATENOW);
}

void MainWindow::ncLDown(WPARAM wparam, LPARAM lparam)
{
	RECT rcWin;
	GetWindowRect(m_hwnd, &rcWin);

	POINT p{ GET_X_LPARAM(lparam) - rcWin.left, GET_Y_LPARAM(lparam) - rcWin.top };

	for (auto e : ncCmp)
		e->LDown(p);

	SetWindowPos(m_hwnd, 0, 0, 0, 0, 0,
		SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void MainWindow::ncLUp(WPARAM wparam, LPARAM lparam)
{
	RECT rcWin;
	GetWindowRect(m_hwnd, &rcWin);

	POINT p{ GET_X_LPARAM(lparam) - rcWin.left, GET_Y_LPARAM(lparam) - rcWin.top };

	for (auto e : ncCmp)
		e->LUp(p);

	SetWindowPos(m_hwnd, 0, 0, 0, 0, 0,
		SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void MainWindow::RepaintRect(PRECT pRc, BOOL erase)
{
	InvalidateRect(m_hwnd, pRc, erase);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow)
{
	MainWindow win;

	if (!win.Create(L"Image Annotator", WS_OVERLAPPEDWINDOW))
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
