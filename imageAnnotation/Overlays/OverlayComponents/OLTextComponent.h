#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#ifndef OVERLAY_COMPONENTS_H
#include "OLBaseComponent.h"
#endif

#include <string>

namespace OLCMP {

	class TextComponent :
		public BaseComponent
	{
	public:
		TextComponent(const RECT& rc, const WCHAR* text);

		// user inputs
		void MouseMove(const WPARAM& wparam, const POINT& p) override;
		void LDown(const WPARAM& wparam, const POINT& p) override;
		void LUp(const WPARAM& wparam, const POINT& p) override;

		// display the text component to the screen
		void display() override;

	private:
		std::wstring text;
	};

}

#endif
