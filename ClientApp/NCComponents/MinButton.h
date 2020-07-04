#ifndef MINBUTTON_H
#define MINBUTTON_H

#ifndef NCCMP_H
#include "NCButton.h"
#endif

namespace NCCMP {

	class MinButton :
		public NCButton
	{
	public:
		MinButton(
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
		MinButton(
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