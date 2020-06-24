#ifndef OLCMP_BUTTON_COMPONENT_H
#define OLCMP_BUTTON_COMPONENT_H

#ifndef OVERLAY_COMPONENTS_H
#include "OLInteractiveComponent.h"
#endif

namespace OLCMP {

	class ButtonComponent :
		public InteractiveComponent
	{
	public:
		ButtonComponent(const RECT& rc, void (*onClick)());

		virtual ~ButtonComponent();

		// user inputs
		virtual void MouseMove(const WPARAM& wparam, const POINT& p) override;
		virtual void LDown(const WPARAM& wparam, const POINT& p) override;
		virtual void LUp(const WPARAM& wparam, const POINT& p) override;

		virtual void display() override;

	protected:
		BUTTONSTATE state;

	private:
		void (*onClick)();
	};

}

#endif
