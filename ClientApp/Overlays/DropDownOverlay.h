#ifndef DROPDOWN_OVERLAY_H
#define DROPDOWN_OVERLAY_H

#include <vector>
#include <string>
#include "SolidOverlay.h"
#include "OverlayComponents/OLTextComponent.h"

struct OLDDElem
{
    wchar_t label[32];                   // NUll terminated string
    void (*LDown) (BaseOverlay* pThis);
    void (*LUp)   (BaseOverlay* pThis);
    void (*RDown) (BaseOverlay* pThis);
    void (*RUp)   (BaseOverlay* pThis);
};

class DropDownOverlay :
    public SolidOverlay
{
public:
    DropDownOverlay(const POINT& p, LONG width, const std::vector<OLDDElem>& elements);
    DropDownOverlay(BaseOverlay* pParent, const POINT& p, LONG width, const std::vector<OLDDElem>& elements);

    virtual ~DropDownOverlay();

    // user actions

    virtual void MouseMove(const WPARAM& wparam, const POINT& p) override;
    virtual void LDown(const WPARAM& wparam, const POINT& p) override;
    virtual void LUp(const WPARAM& wparam, const POINT& p) override;

    // displays the overlay to the screen
    virtual void display() override;

protected:
    const static LONG lSize = 20;

private:
    OLDDElem* pLabels;

    UINT8 lblNum;
    INT8 currLbl;
    BUTTONSTATE state;

    INT8 getLabelNum(const POINT& p);
};

#endif
