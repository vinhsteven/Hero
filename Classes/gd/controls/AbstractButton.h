
#ifndef _GD_CONTROLS_ABSTRACT_BUTTON_H_
#define _GD_CONTROLS_ABSTRACT_BUTTON_H_

#define button_selector(selector)   (SEL_ButtonHandler)(&selector)

USING_NS_CC;

class AbstractButton;

typedef void (CCObject::*SEL_ButtonHandler)(int);

class AbstractButton : public CCNode, public CCTouchDelegate
{
public:
    
    AbstractButton();
    
    virtual bool init(CCObject *pListener, SEL_ButtonHandler pfnSelector);
    
    virtual void onEnter();
    virtual void onExit();
    
    /** Gets touch priority */
    virtual int getTouchPriority() const { return m_nTouchPriority; }
    
    /** Sets touch priority */
    virtual void setTouchPriority(int nTouchPriority);
    
    /** Is touch enabled? */
    virtual bool isTouchEnabled() const { return m_bTouchEnabled; }
    
    /** Sets touch enabled or not */
    virtual void setTouchEnabled(bool bTouchEnabled);
    
    /** Sets position by attach */
    virtual void setPositionByAttach(const CCPoint &origin, const CCSize &size, int nAttach);
    
    /** Contains the given point? */
    virtual bool containsPoint(const CCPoint &point) const;
    
protected:
    
    virtual void registerWithTouchDispatcher(void);
    virtual void unregisterWithTouchDispatcher(void);
    
    /** On activate */
    virtual void onActivate(void);
    
    /** On selected */
    virtual void onSelected(void);
    
    /** On unselected */
    virtual void onUnselected(void);
    
public:
    
    //
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
#ifdef DEBUG
    virtual void draw();
#endif
    
protected:
    
    // The listener
    CCObject *m_pListener;
    
    // The selector
    SEL_ButtonHandler m_pfnSelector;
    
    // The touch priority
    int m_nTouchPriority;
    
    // Is touch enabled?
    bool m_bTouchEnabled;
    
    // Is selected?
    bool m_bSelected;
};

#endif  // _GD_CONTROLS_ABSTRACT_BUTTON_H_
