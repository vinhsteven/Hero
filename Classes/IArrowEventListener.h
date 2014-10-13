
#ifndef _I_ARROW_EVENT_LISTENER_H_
#define _I_ARROW_EVENT_LISTENER_H_

class Arrow;

class IArrowEventListener
{
public:
    
    /** On arrow finished */
    virtual void onArrowFinished(Arrow *pArrow) {}
    
    /** On arrow exited */
    virtual void onArrowExited(Arrow *pArrow) {}
};

// Null Object
extern IArrowEventListener theNullArrowEventListener;

#endif // _I_ARROW_EVENT_LISTENER_H_
