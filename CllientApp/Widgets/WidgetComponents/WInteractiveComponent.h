#ifndef WCMP_INTERACTIVE_COMPONENT_H
#define WCMP_INTERACTIVE_COMPONENT_H

#ifndef WIDGET_CMP_H
#include "WBaseComponent.h"
#endif

#ifndef StateUpdateFunc

#define paintSelf_SU { PRECT pRcSU = new RECT(); getGlobalRect(pRcSU); paintSelf(pRcSU); }

#define getOld_SU enum class STATE old = state
#define runFunc_SU(func, arg) func(arg)
#define checkPaint_SU(old, state) if (old != state) paintSelf_SU

// calls paintSelf if the state has been updated
#define StateUpdateFunc(func, arg) { getOld_SU; runFunc_SU(func, arg); checkPaint_SU(old, state); }

#endif

namespace WCMP {

	enum class STATE {
		PASSIVE,
		ACTIVE,
		PRESSED
	};

	class InteractiveComponent :
		virtual public BaseComponent
	{
	public:
		InteractiveComponent(
			D2D1_RECT_F* pRc,
			PRECT parentpRc,
			Resizable* pRB,
			void (*onClick)(),
			void (*paintSelf)(PRECT)
		);

		void MouseMove(POINT p) override;
		void LDown(POINT p) override;
		void LUp(POINT p) override;
		void MouseLeave() override;

	protected:
		InteractiveComponent(InteractiveComponent* pThis, PRECT npRc);

		enum class STATE state;

		void (*onClick)();
		void (*paintSelf)(PRECT);

	private:
		void m_MouseMove(POINT p);
		void m_LDown(POINT p);
		void m_LUp(POINT p);
		void m_MouseLeave();
	};

}

#endif