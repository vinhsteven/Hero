
#ifndef _GD_CONTROLS_CRAZY_BUTTON_H_
#define _GD_CONTROLS_CRAZY_BUTTON_H_

#include "AbstractButton.h"

USING_NS_CC;

typedef void (CCObject::*SEL_CrazyButtonHandler)(CCTouch *pTouch, int);

class CrazyButton : public AbstractButton
{
public:

    CrazyButton();
    
    virtual bool init(CCObject *pListener, SEL_CrazyButtonHandler pfnPressedSelector, SEL_CrazyButtonHandler pfnReleasedSelector);
    
    static CrazyButton* create(CCObject *pListener, SEL_CrazyButtonHandler pfnPressedSelector, SEL_CrazyButtonHandler pfnReleasedSelector);
    
public:
    
    //
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {}
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {}
    
protected:
    
    // The pressed selector
    SEL_CrazyButtonHandler m_pfnPressedSelector;
    
    // The released selector
    SEL_CrazyButtonHandler m_pfnReleasedSelector;
};

#endif  // _GD_CONTROLS_CRAZY_BUTTON_H_
