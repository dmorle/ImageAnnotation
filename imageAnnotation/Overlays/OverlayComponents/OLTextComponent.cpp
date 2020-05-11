#include "OLTextComponent.h"



namespace OLCMP {

	TextComponent::TextComponent(const RECT& rc, const WCHAR* text)
		: BaseComponent(rc)
	{
		this->text = std::wstring(text);
	}

	void TextComponent::display()
	{
		D2D1_RECT_F rc;
		getGlobalRect(rc);
		pRenderTarget->DrawText(text.c_str(), text.length(), pTextFormat, rc, pBrushes->text);
	}

	void TextComponent::MouseMove(const WPARAM& wparam, const POINT& p)
	{

	}

	void TextComponent::LDown(const WPARAM& wparam, const POINT& p)
	{

	}

	void TextComponent::LUp(const WPARAM& wparam, const POINT& p)
	{

	}

}
