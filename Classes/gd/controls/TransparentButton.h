
#ifndef _GD_CONTROLS_TRANSPARENT_BUTTON_H_
#define _GD_CONTROLS_TRANSPARENT_BUTTON_H_

#include "AbstractButton.h"

USING_NS_CC;

class TransparentButton : public AbstractButton
{
public:

    static TransparentButton* create(CCObject *pListener, SEL_ButtonHandler pfnSelector);
    
public:
    
    //
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent) {}
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent) {}
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent) {}
};

#endif  // _GD_CONTROLS_TRANSPARENT_BUTTON_H_
