#include "FileMenu.h"
#include "MsgOverlay.h"



void Label1Down(BaseOverlay* pThis)
{
}

void Label1Up(BaseOverlay* pThis)
{
	RECT rc;
	GetClientRect(Parameters::hwnd, &rc);
	POINT p{
		(rc.right - MsgOverlay::getStdWidth()) / 2,
		(rc.bottom - MsgOverlay::getStdHeight()) / 2
	};

	if (p.x < 0 || p.y < 0)
		return;

	Parameters::pAO = new MsgOverlay(pThis, L"Label 1 LUp", p);
}

void Label2Down(BaseOverlay* pThis)
{
}

void Label2Up(BaseOverlay* pThis)
{
	RECT rc;
	GetClientRect(Parameters::hwnd, &rc);
	POINT p{
		(rc.right - MsgOverlay::getStdWidth()) / 2,
		(rc.bottom - MsgOverlay::getStdHeight()) / 2
	};

	if (p.x < 0 || p.y < 0)
		return;

	Parameters::pAO = new MsgOverlay(pThis, L"Label 2 LUp", p);
}

void Label3Down(BaseOverlay* pThis)
{
}

void Label3Up(BaseOverlay* pThis)
{
	RECT rc;
	GetClientRect(Parameters::hwnd, &rc);
	POINT p{
		(rc.right - MsgOverlay::getStdWidth()) / 2,
		(rc.bottom - MsgOverlay::getStdHeight()) / 2
	};

	if (p.x < 0 || p.y < 0)
		return;

	Parameters::pAO = new MsgOverlay(pThis, L"Label 2 LUp", p);
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
