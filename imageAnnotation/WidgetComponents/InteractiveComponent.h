#ifndef INTERACTIVECOMPONENT_H
#define INTERACTIVECOMPONENT_H

#include "BaseComponent.h"

enum STATE {
	PASSIVE,
	ACTIVE,
	PRESSED
};

#ifndef StateUpdateFunc

#define getOld_SU STATE old = state
#define runFunc_SU(func, arg) func(arg)
#define checkPaint_SU(old, state) if (old != state) paintSelf(&rc)

#define StateUpdateFunc(func, arg) getOld_SU; runFunc_SU(func, arg); checkPaint_SU(old, state);

#endif

class InteractiveComponent :
	public BaseComponent
{
public:
	void MouseMove(POINT p);
	void LDown(POINT p);
	void LUp(POINT p);
	void MouseLeave();

protected:
	STATE state;

	void (*onClick)();
	void (*paintSelf)(PRECT);

private:
	void m_MouseMove(POINT p);
	void m_LDown(POINT p);
	void m_LUp(POINT p);
	void m_MouseLeave();
};

#endif