#ifndef CLOSEBUTTON_H
#define CLOSEBUTTON_H

#include "NCButton.h"

namespace NCCMP {

	class CloseButton :
		public NCButton
	{
	public:
		CloseButton(
			COLORREF back,
			COLORREF back_passive,
			COLORREF back_active,
			COLORREF back_pressed,
			COLORREF comp,
			COLORREF comp_passive,
			COLORREF comp_active,
			COLORREF comp_pressed,
			void (*onClick)(),
			RECT rc
		);
		CloseButton(
			COLORREF back_passive,
			COLORREF back_active,
			COLORREF back_pressed,
			COLORREF comp_passive,
			COLORREF comp_active,
			COLORREF comp_pressed,
			void (*onClick)(),
			RECT rc
		);

		void translate(LONG dx, LONG dy);

		void display(HDC hdc);
	};

}

#endif