
#include "gd.h"
#include "AbstractButton.h"

#define TOUCH_PRIORITY  -1
#define TOUCH_ENABLED   true

#ifdef DEBUG
//#define SHOW_BACKGROUND
#endif

USING_NS_CC;

AbstractButton::AbstractButton()
: m_pListener(NULL)
, m_pfnSelector(NULL)
, m_nTouchPriority(TOUCH_PRIORITY)
, m_bTouchEnabled(TOUCH_ENABLED)
, m_bSelected(false)
{
    
}

bool AbstractButton::init(CCObject *pListener, SEL_ButtonHandler pfnSelector)
{
    if (CCNode::init())
    {
//        GD_ASSERT(pListener != NULL, "E98987876655");
//        GD_ASSERT(pfnSelector != NULL, "E98987876656");
        
        // Sets listener
        m_pListener = pListener;
        
        // Sets selector
        m_pfnSelector = pfnSelector;
        
        // Sets touch priority
        m_nTouchPriority = TOUCH_PRIORITY;
        
        // Sets touch enabled
        m_bTouchEnabled = TOUCH_ENABLED;
        
        //
        m_bSelected = false;
        
#ifdef SHOW_BACKGROUND
        setShaderProgram(pTheShaderCache->programForKey(kCCShader_PositionTextureColor));
#endif
        
        return true;
    }
    
    return false;
}

void AbstractButton::onEnter()
{
//    if (m_bTouchEnabled)
    {
        this->registerWithTouchDispatcher();
    }
    
    CCNode::onEnter();
}

void AbstractButton::onExit()
{
//    if (m_bTouchEnabled)
    {
        this->unregisterWithTouchDispatcher();
    }
    
    CCNode::onExit();
}

void AbstractButton::setTouchPriority(int nTouchPriority)
{
    if (m_nTouchPriority != nTouchPriority)
    {
        m_nTouchPriority = nTouchPriority;
        
        if (m_bRunning)
        {
//            if (m_bTouchEnabled)
            {
                this->unregisterWithTouchDispatcher();
                this->registerWithTouchDispatcher();
            }
        }
    }
}

void AbstractButton::setTouchEnabled(bool bTouchEnabled)
{
    if (m_bTouchEnabled != bTouchEnabled)
    {
        m_bTouchEnabled = bTouchEnabled;
        
//        if (m_bRunning)
//        {
//            if (bTouchEnabled)
//            {
//                this->registerWithTouchDispatcher();
//            }
//            else
//            {
//                this->unregisterWithTouchDispatcher();
//            }
//        }
    }
}

void AbstractButton::setPositionByAttach(const CCPoint &origin, const CCSize &size, int nAttach)
{
    float fX = 0;
    float fY = 0;
    
    // Top
    if (nAttach == kAttachTopLeft)
    {
        fX = getLeftAttach(origin, size, m_obAnchorPointInPoints);
        fY = getTopAttach(origin, size, m_obContentSize, m_obAnchorPointInPoints);
    }
    else if (nAttach == kAttachTopCenter)
    {
        fX = getCenterAttach(origin, size);
        fY = getTopAttach(origin, size, m_obContentSize, m_obAnchorPointInPoints);
    }
    else if (nAttach == kAttachTopRight)
    {
        fX = getRightAttach(origin, size, m_obContentSize, m_obAnchorPointInPoints);
        fY = getTopAttach(origin, size, m_obContentSize, m_obAnchorPointInPoints);
    }
    
    // Middle
    else if (nAttach == kAttachMiddleLeft)
    {
        fX = getLeftAttach(origin, size, m_obAnchorPointInPoints);
        fY = getMiddleAttach(origin, size);
    }
    else if (nAttach == kAttachCenter)
    {
        fX = getCenterAttach(origin, size);
        fY = getMiddleAttach(origin, size);
    }
    else if (nAttach == kAttachMiddleRight)
    {
        fX = getRightAttach(origin, size, m_obContentSize, m_obAnchorPointInPoints);
        fY = getMiddleAttach(origin, size);
    }
    
    // Bottom
    else if (nAttach == kAttachBottomLeft)
    {
        fX = getLeftAttach(origin, size, m_obAnchorPointInPoints);
        fY = getBottomAttach(origin, size, m_obAnchorPointInPoints);
    }
    else if (nAttach == kAttachBottomCenter)
    {
        fX = getCenterAttach(origin, size);
        fY = getBottomAttach(origin, size, m_obAnchorPointInPoints);
    }
    else if (nAttach == kAttachBottomRight)
    {
        fX = getRightAttach(origin, size, m_obContentSize, m_obAnchorPointInPoints);
        fY = getBottomAttach(origin, size, m_obAnchorPointInPoints);
    }
    
    // Not supported
    else
    {
        GD_NOT_SUPPORTED("E111222333");
        
        return;
    }
    
    setPosition(fX, fY);
}

bool AbstractButton::containsPoint(const CCPoint &point) const
{
    return (point.x >= 0 &&
            point.y >= 0 &&
            point.x <= m_obContentSize.width &&
            point.y <= m_obContentSize.height);
}

void AbstractButton::registerWithTouchDispatcher(void)
{
    // Gets the touch dispatcher
    CCTouchDispatcher *pTouchDispatcher = pTheDirector->getTouchDispatcher();
    
    //
    pTouchDispatcher->addTargetedDelegate(this, m_nTouchPriority, true);
}

void AbstractButton::unregisterWithTouchDispatcher(void)
{
    // Gets the touch dispatcher
    CCTouchDispatcher *pTouchDispatcher = pTheDirector->getTouchDispatcher();
    
    //
    pTouchDispatcher->removeDelegate(this);
}

void AbstractButton::onActivate(void)
{
    if (m_pListener && m_pfnSelector)
    {
        (m_pListener->*m_pfnSelector)(m_nTag);
    }
}

void AbstractButton::onSelected(void)
{
    
}

void AbstractButton::onUnselected(void)
{
    
}

bool AbstractButton::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!m_bVisible)
    {
        return false;
    }
    
    for (CCNode *pParent = this->m_pParent; pParent != NULL; pParent = pParent->getParent())
    {
        if (!pParent->isVisible())
        {
            return false;
        }
    }
    
    // Gets touch location
    CCPoint location = pTouch->getLocation();
    
    // Gets local
    CCPoint local = this->convertToNodeSpace(location);
    
    if (this->containsPoint(local))
    {
        if (m_bTouchEnabled)
        {
            m_bSelected = true;
            
            this->onSelected();
        }
        else
        {
            m_bSelected = false;
        }
        
        return true;
    }
    
    m_bSelected = false;
    
    return false;
}

void AbstractButton::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!m_bTouchEnabled)
    {
        return;
    }
    
    // Gets touch location
    CCPoint location = pTouch->getLocation();
    
    // Gets local
    CCPoint local = this->convertToNodeSpace(location);
    
    //
    bool bSelected = this->containsPoint(local);
    
    if (m_bSelected != bSelected)
    {
        m_bSelected = bSelected;
        
        if (m_bSelected)
        {
            this->onSelected();
        }
        else
        {
            this->onUnselected();
        }
    }
}

void AbstractButton::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!m_bTouchEnabled)
    {
        return;
    }
    
    if (m_bSelected)
    {
        m_bSelected = false;
        
        this->onUnselected();
        
        this->onActivate();
    }
}

void AbstractButton::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!m_bTouchEnabled)
    {
        return;
    }
    
    if (m_bSelected)
    {
        m_bSelected = false;
        
        this->onUnselected();
    }
}

#ifdef DEBUG
void AbstractButton::draw()
{
#ifdef SHOW_BACKGROUND
    CC_NODE_DRAW_SETUP();
    
    ccDrawSolidRect(CCPointZero, m_obContentSize, makeColor4F(0.75f, 0.75f, 0.75f, 0.25f));
#endif
}
#endif
