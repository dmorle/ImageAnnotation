#include "FileMenu.h"
#include "MsgOverlay.h"



void Label1Down(BaseOverlay* pThis)
{
}

void Label1Up(BaseOverlay* pThis)
{
	Parameters::pAO = new MsgOverlay(pThis, L"Label 1 LUp", POINT{ 600, 300 });
	// MessageBox(pThis->hwnd, "Label 1 LDown", "File Menu Action", MB_OK);
}

void Label2Down(BaseOverlay* pThis)
{
}

void Label2Up(BaseOverlay* pThis)
{
	Parameters::pAO = new MsgOverlay(pThis, L"Label 2 LUp", POINT{ 600, 300 });
	// MessageBox(pThis->hwnd, "Label 2 LUp", "File Menu Action", MB_OK);
}

void Label3Down(BaseOverlay* pThis)
{
}

void Label3Up(BaseOverlay* pThis)
{
	Parameters::pAO = new MsgOverlay(pThis, L"Label 2 LUp", POINT{ 600, 300 });
	// MessageBox(pThis->hwnd, "Label 3 LUp", "File Menu Action", MB_OK);
}

FileMenu::FileMenu() :
	BaseOverlay(
		RECT{
			50,
			edgeSpace * 2,
			150,
			lSize * 3 + edgeSpace * 6
		}
	),
	DropDownOverlay(
		POINT{
			50,
			edgeSpace * 2
		},
		100,
		std::vector<OLDDElem>{
			OLDDElem{
				L"First Label",
				Label1Down,
				Label1Up,
				NULL,
				NULL
			},
			OLDDElem{
				L"Second Label",
				Label2Down,
				Label2Up,
				NULL,
				NULL
			},
			OLDDElem{
				L"Third Label",
				Label3Down,
				Label3Up,
				NULL,
				NULL
			}
		}
	)
{}
