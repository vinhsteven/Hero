
#include "gd.h"
#include "BaseButton.h"

#define TOUCH_EXTRA     10.0f

#ifdef DEBUG
//#define SHOW_BACKGROUND
#endif

USING_NS_CC;

BaseButton::BaseButton()
: m_fTouchExtraLeft(TOUCH_EXTRA)
, m_fTouchExtraTop(TOUCH_EXTRA)
, m_fTouchExtraRight(TOUCH_EXTRA)
, m_fTouchExtraBottom(TOUCH_EXTRA)
{
    
}

bool BaseButton::init(CCObject *pListener, SEL_ButtonHandler pfnSelector)
{
    if (AbstractButton::init(pListener, pfnSelector))
    {
        m_fTouchExtraLeft   =
        m_fTouchExtraTop    =
        m_fTouchExtraRight  =
        m_fTouchExtraBottom = TOUCH_EXTRA;
        
#ifdef SHOW_BACKGROUND
        setShaderProgram(pTheShaderCache->programForKey(kCCShader_PositionTextureColor));
#endif
        
        return true;
    }
    
    return false;
}

bool BaseButton::containsPoint(const CCPoint &point) const
{
    return (point.x >= -m_fTouchExtraLeft   &&
            point.y >= -m_fTouchExtraBottom &&
            point.x <= m_obContentSize.width  + m_fTouchExtraRight &&
            point.y <= m_obContentSize.height + m_fTouchExtraTop);
}

#ifdef DEBUG
void BaseButton::draw()
{
#ifdef SHOW_BACKGROUND
    CC_NODE_DRAW_SETUP();
    
    CCPoint origin(-m_fTouchExtraLeft, -m_fTouchExtraBottom);
    CCSize  destination(m_obContentSize.width + m_fTouchExtraRight, m_obContentSize.height + m_fTouchExtraTop);
    
    ccDrawSolidRect(origin, destination, makeColor4F(0.0f, 0.75f, 0.0f, 0.25f));
    
    ccDrawSolidRect(CCPointZero, m_obContentSize, makeColor4F(0.75f, 0.75f, 0.75f, 0.25f));
#else
    AbstractButton::draw();
#endif
}
#endif
