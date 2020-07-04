#include "Parameters.h"



HWND Parameters::hwnd = NULL;

ID2D1Factory* Parameters::pFactory = NULL;
IDWriteFactory* Parameters::pDWriteFactory = NULL;
IWICImagingFactory* Parameters::pWicFactory = NULL;
ID2D1HwndRenderTarget* Parameters::pRenderTarget = NULL;

IDWriteTextFormat* Parameters::pTextFormat = NULL;

Parameters::appPalette* Parameters::pPalette = NULL;
Parameters::stdBrushes* Parameters::pBrushes = NULL;
Parameters::stdCursors* Parameters::pCursors = NULL;

GRAPHICSTRUCT* Parameters::pStdGs = NULL;

Panel* Parameters::pAP = NULL;

BOOL Parameters::fullPaint = TRUE;
BOOL Parameters::passMouse = FALSE;

BaseOverlay* Parameters::pAO = NULL;

Parameters::_appPalette::_appPalette() :
	mainBack       (0.00f, 0.00f, 0.60f),
	mainBorder     (0.15f, 0.15f, 0.15f),
	mainText1      (1.00f, 1.00f, 1.00f),
	mainText2      (0.00f, 0.00f, 0.00f),
	mainText3      (0.00f, 0.00f, 0.00f),
	mainCmp1       (0.15f, 0.15f, 0.15f),
	mainCmp2       (0.00f, 0.00f, 0.00f),
	mainCmp3       (0.00f, 0.00f, 0.00f),
	mainActive1    (0.30f, 0.30f, 0.30f),
	mainActive2    (0.00f, 0.00f, 0.00f),
	mainActive3    (0.00f, 0.00f, 0.00f),
	mainPressed    (0.40f, 0.40f, 0.40f),
	
	widgetBack     (0.00f, 0.00f, 0.60f),
	widgetBorder   (0.15f, 0.15f, 0.15f),
	widgetText1    (1.00f, 1.00f, 1.00f),
	widgetText2    (0.00f, 0.00f, 0.00f),
	widgetText3    (0.00f, 0.00f, 0.00f),
	widgetCmp1     (0.15f, 0.15f, 0.15f),
	widgetCmp2     (0.00f, 0.00f, 0.00f),
	widgetCmp3     (0.00f, 0.00f, 0.00f),
	widgetActive1  (0.30f, 0.30f, 0.30f),
	widgetActive2  (0.00f, 0.00f, 0.00f),
	widgetActive3  (0.00f, 0.00f, 0.00f),
	widgetPressed  (0.40f, 0.40f, 0.40f),

	overlayBack    (0.10f, 0.10f, 0.10f),
	overlayBorder  (0.00f, 0.00f, 0.60f),
	overlayText1   (1.00f, 1.00f, 1.00f),
	overlayText2   (0.00f, 0.00f, 0.00f),
	overlayText3   (0.00f, 0.00f, 0.00f),
	overlayCmp1    (0.15f, 0.15f, 0.15f),
	overlayCmp2    (0.00f, 0.00f, 0.00f),
	overlayCmp3    (0.00f, 0.00f, 0.00f),
	overlayActive1 (0.30f, 0.30f, 0.30f),
	overlayActive2 (0.00f, 0.00f, 0.00f),
	overlayActive3 (0.00f, 0.00f, 0.00f),
	overlayPressed (0.40f, 0.40f, 0.40f)
{}

Parameters::_stdBrushes::_stdBrushes() :
	mainBack       (NULL),
	mainPredel     (NULL),
	mainBorder     (NULL),
	mainText1      (NULL),
	mainText2      (NULL),
	mainText3      (NULL),
	mainCmp1       (NULL),
	mainCmp2       (NULL),
	mainCmp3       (NULL),
	mainActive1    (NULL),
	mainActive2    (NULL),
	mainActive3    (NULL),
	mainPresel1    (NULL),
	mainPresel2    (NULL),
	mainPresel3    (NULL),
	mainPressed    (NULL),
	
	widgetBack     (NULL),
	widgetPredel   (NULL),
	widgetBorder   (NULL),
	widgetText1    (NULL),
	widgetText2    (NULL),
	widgetText3    (NULL),
	widgetCmp1     (NULL),
	widgetCmp2     (NULL),
	widgetCmp3     (NULL),
	widgetActive1  (NULL),
	widgetActive2  (NULL),
	widgetActive3  (NULL),
	widgetPresel1  (NULL),
	widgetPresel2  (NULL),
	widgetPresel3  (NULL),
	widgetPressed  (NULL),
	
	overlayBack    (NULL),
	overlayPredel  (NULL),
	overlayBorder  (NULL),
	overlayText1   (NULL),
	overlayText2   (NULL),
	overlayText3   (NULL),
	overlayCmp1    (NULL),
	overlayCmp2    (NULL),
	overlayCmp3    (NULL),
	overlayActive1 (NULL),
	overlayActive2 (NULL),
	overlayActive3 (NULL),
	overlayPresel1 (NULL),
	overlayPresel2 (NULL),
	overlayPresel3 (NULL),
	overlayPressed (NULL)
{}

void Parameters::_stdBrushes::release() {
	SafeRelease(&mainBack      );
	SafeRelease(&mainPredel    );
	SafeRelease(&mainBorder    );
	SafeRelease(&mainText1     );
	SafeRelease(&mainText2     );
	SafeRelease(&mainText3     );
	SafeRelease(&mainCmp1      );
	SafeRelease(&mainCmp2      );
	SafeRelease(&mainCmp3      );
	SafeRelease(&mainActive1   );
	SafeRelease(&mainActive2   );
	SafeRelease(&mainActive3   );
	SafeRelease(&mainPresel1   );
	SafeRelease(&mainPresel2   );
	SafeRelease(&mainPresel3   );
	SafeRelease(&mainPressed   );

	SafeRelease(&widgetBack    );
	SafeRelease(&widgetPredel  );
	SafeRelease(&widgetBorder  );
	SafeRelease(&widgetText1   );
	SafeRelease(&widgetText2   );
	SafeRelease(&widgetText3   );
	SafeRelease(&widgetCmp1    );
	SafeRelease(&widgetCmp2    );
	SafeRelease(&widgetCmp3    );
	SafeRelease(&widgetActive1 );
	SafeRelease(&widgetActive2 );
	SafeRelease(&widgetActive3 );
	SafeRelease(&widgetPresel1 );
	SafeRelease(&widgetPresel2 );
	SafeRelease(&widgetPresel3 );
	SafeRelease(&widgetPressed );

	SafeRelease(&overlayBack   );
	SafeRelease(&overlayPredel );
	SafeRelease(&overlayBorder );
	SafeRelease(&overlayText1  );
	SafeRelease(&overlayText2  );
	SafeRelease(&overlayText3  );
	SafeRelease(&overlayCmp1   );
	SafeRelease(&overlayCmp2   );
	SafeRelease(&overlayCmp3   );
	SafeRelease(&overlayActive1);
	SafeRelease(&overlayActive2);
	SafeRelease(&overlayActive3);
	SafeRelease(&overlayPresel1);
	SafeRelease(&overlayPresel2);
	SafeRelease(&overlayPresel3);
	SafeRelease(&overlayPressed);
}
