#ifndef MSG_OVERLAY_H
#define MSG_OVERLAY_H

#include "SolidOverlay.h"

class MsgOverlay :
    public SolidOverlay
{
public:
    MsgOverlay(PCWSTR msg, const POINT& p);
    MsgOverlay(BaseOverlay* pParent, PCWSTR msg, const POINT& p);
    MsgOverlay(PCWSTR msg, const POINT& p, LONG width, LONG height);
    MsgOverlay(BaseOverlay* pParent, PCWSTR msg, const POINT& p, LONG width, LONG height);

    virtual ~MsgOverlay();

    // user actions

    virtual void MouseMove(const WPARAM& wparam, const POINT& p) override;
    virtual void LDown(const WPARAM& wparam, const POINT& p) override;
    virtual void LUp(const WPARAM& wparam, const POINT& p) override;

    // displays the overlay to the screen
    virtual void display() override;

    const LONG getWidth() const;
    const LONG getHeight() const;

    const static LONG getStdWidth();
    const static LONG getStdHeight();

protected:
    LONG width;
    LONG height;

private:
    std::wstring msg;

    const static LONG stdWidth = 200L;
    const static LONG stdHeight = 100L;
};

#endif
