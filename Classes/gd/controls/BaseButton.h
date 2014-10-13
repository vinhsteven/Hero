
#ifndef _GD_CONTROLS_BASE_BUTTON_H_
#define _GD_CONTROLS_BASE_BUTTON_H_

#include "AbstractButton.h"

class BaseButton : public AbstractButton
{
public:
    
    BaseButton();
    
    virtual bool init(CCObject *pListener, SEL_ButtonHandler pfnSelector);
    
    /** Sets touch extra */
    virtual void setTouchExtra(float fTouchExtraLeft, float fTouchExtraTop, float fTouchExtraRight, float fTouchExtraBottom)
    {
        m_fTouchExtraLeft   = fTouchExtraLeft;
        m_fTouchExtraTop    = fTouchExtraTop;
        m_fTouchExtraRight  = fTouchExtraRight;
        m_fTouchExtraBottom = fTouchExtraBottom;
    }
    
    /** Sets touch extra */
    virtual void setTouchExtra(float fTouchExtra)
    {
        m_fTouchExtraLeft   =
        m_fTouchExtraTop    =
        m_fTouchExtraRight  =
        m_fTouchExtraBottom = fTouchExtra;
    }
    
    /** Sets touch horizontal extra */
    virtual void setTouchExtraHorizontal(float fTouchExtra)
    {
        m_fTouchExtraLeft = m_fTouchExtraRight = fTouchExtra;
    }
    
    /** Sets touch vertical extra */
    virtual void setTouchExtraVertical(float fTouchExtra)
    {
        m_fTouchExtraTop = m_fTouchExtraBottom = fTouchExtra;
    }
    
    GD_IMPLEMENT_GET_SET(TouchExtraLeft, float, fTouchExtraLeft);
    GD_IMPLEMENT_GET_SET(TouchExtraTop, float, fTouchExtraTop);
    GD_IMPLEMENT_GET_SET(TouchExtraRight, float, fTouchExtraRight);
    GD_IMPLEMENT_GET_SET(TouchExtraBottom, float, fTouchExtraBottom);
    
    /** Contains the given point? */
    virtual bool containsPoint(const CCPoint &point) const;
    
#ifdef DEBUG
    virtual void draw();
#endif
    
protected:
    
    // The touch extra left
    float m_fTouchExtraLeft;
    
    // The touch extra top
    float m_fTouchExtraTop;
    
    // The touch extra right
    float m_fTouchExtraRight;
    
    // The touch extra bottom
    float m_fTouchExtraBottom;
};

#endif  // _GD_CONTROLS_BASE_BUTTON_H_
