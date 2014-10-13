
#include "gd.h"
#include "CrazyButton.h"

USING_NS_CC;

CrazyButton::CrazyButton()
: m_pfnReleasedSelector(NULL)
{
    
}

bool CrazyButton::init(CCObject *pListener, SEL_CrazyButtonHandler pfnPressedSelector, SEL_CrazyButtonHandler pfnReleasedSelector)
{
    if (AbstractButton::init(pListener, NULL))
    {
        // Sets pressed selector
        m_pfnPressedSelector = pfnPressedSelector;
        
        // Sets released selector
        m_pfnReleasedSelector = pfnReleasedSelector;
        
        return true;
    }
    
    return false;
}

GD_IMPLEMENT_CREATE_3_ARGS(CrazyButton, CCObject*, pListener, SEL_CrazyButtonHandler, pfnPressedSelector, SEL_CrazyButtonHandler, pfnReleasedSelector);

bool CrazyButton::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!(m_bVisible && m_bTouchEnabled))
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
        if (m_pListener && m_pfnPressedSelector)
        {
            (m_pListener->*m_pfnPressedSelector)(pTouch, m_nTag);
        }
        
        return true;
    }
    
    return false;
}

void CrazyButton::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!(m_bVisible && m_bTouchEnabled))
    {
        return;
    }
    
    if (m_pListener && m_pfnReleasedSelector)
    {
        (m_pListener->*m_pfnReleasedSelector)(pTouch, m_nTag);
    }
}
