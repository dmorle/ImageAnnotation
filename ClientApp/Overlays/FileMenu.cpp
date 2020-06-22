#include "FileMenu.h"



void Label1Down(BaseOverlay* pThis)
{
	printf("Label 1 LDown\n");
}

void Label2Down(BaseOverlay* pThis)
{
	printf("Label 2 LDown\n");
}

void Label3Down(BaseOverlay* pThis)
{
	printf("Label 3 LDown\n");
}

void Label1Up(BaseOverlay* pThis)
{
	printf("Label 1 LUp\n");
}

void Label2Up(BaseOverlay* pThis)
{
	printf("Label 2 LUp\n");
}

void Label3Up(BaseOverlay* pThis)
{
	printf("Label 3 LUp\n");
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
