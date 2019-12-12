#ifndef MAXBUTTON_H
#define MAXBUTTON_H

#include "NCButton.h"

namespace NCCMP {

	class MaxButton :
		public NCButton
	{
	public:
		MaxButton(
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
		MaxButton(
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