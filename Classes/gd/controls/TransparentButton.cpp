
#include "gd.h"
#include "TransparentButton.h"

USING_NS_CC;

GD_IMPLEMENT_CREATE_2_ARGS(TransparentButton, CCObject*, pListener, SEL_ButtonHandler, pfnSelector);

bool TransparentButton::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
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
        this->onActivate();
        
        return true;
    }
    
    return false;
}
