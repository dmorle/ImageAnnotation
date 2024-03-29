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
		pRenderTarget->DrawText(text.c_str(), text.length(), pTextFormats->pText1, rc, pBrushes->overlayText1);
	}

}
