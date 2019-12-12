#ifndef NCTEXTBUTTON_H
#define NCTEXTBUTTON_H

#include "NCButton.h"

namespace NCCMP {

	class NCTextButton :
		public NCButton
	{
	public:
		NCTextButton(
			COLORREF back,
			COLORREF back_passive,
			COLORREF back_active,
			COLORREF back_pressed,
			COLORREF comp,
			COLORREF comp_passive,
			COLORREF comp_active,
			COLORREF comp_pressed,
			void (*onClick)(),
			RECT rc,
			LPCSTR msg,
			UINT fontSize = 15
		);
		NCTextButton(
			COLORREF back_passive,
			COLORREF back_active,
			COLORREF back_pressed,
			COLORREF comp_passive,
			COLORREF comp_active,
			COLORREF comp_pressed,
			void (*onClick)(),
			RECT rc,
			LPCSTR msg,
			UINT fontSize = 15
		);

		void display(HDC hdc);

	private:
		UINT fontSize;
		HFONT hfont;
		LPCSTR msg;
	};

}

#endif