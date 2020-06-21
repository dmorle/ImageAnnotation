#include "FileMenu.h"



FileMenu::FileMenu() :
	BaseOverlay(fileRc),
	SolidCmpOverlay(fileRc)
{
	this->addComponent(
		new OLCMP::TextComponent(
			RECT{edgeSpace, edgeSpace, 100 - edgeSpace, 10 + edgeSpace },
			L"I'm an overlay        gfdgfd"
		)
	);
}
