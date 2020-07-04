#ifndef MSG_OVERLAY_H
#define MSG_OVERLAY_H

#include "SolidOverlay.h"

class MsgOverlay :
    public SolidOverlay
{
public:
    MsgOverlay(PCWSTR msg, const POINT& p);
    MsgOverlay(BaseOverlay* pParent, PCWSTR msg, const POINT& p);

    virtual ~MsgOverlay();

    // user actions

    virtual void MouseMove(const WPARAM& wparam, const POINT& p) override;
    virtual void LDown(const WPARAM& wparam, const POINT& p) override;
    virtual void LUp(const WPARAM& wparam, const POINT& p) override;

    // displays the overlay to the screen
    virtual void display() override;

protected:
    const static LONG width = 200L;
    const static LONG height = 100L;

private:
    std::wstring msg;
};

#endif
