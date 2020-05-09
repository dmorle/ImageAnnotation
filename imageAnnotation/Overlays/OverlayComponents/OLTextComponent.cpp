#include "OLTextComponent.h"



namespace OLCMP {

	TextComponent::TextComponent(BaseOverlay* pParent, const RECT& rc, const WCHAR* text)
		: BaseComponent(pParent, rc)
	{
		this->text = std::wstring(text);
	}

	void TextComponent::display()
	{
		D2D1_RECT_F rc;
		getGlobalRect(rc);
		pRenderTarget->DrawText(text.c_str(), text.length, pTextFormat, rc, pBrushes->text);
	}

}