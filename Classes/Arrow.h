
#ifndef _ARROW_H_
#define _ARROW_H_

USING_NS_CC;

class IArrowEventListener;

class Arrow : public CCSprite
{
public:
    
    Arrow();
    
    virtual bool init(const char *szFileName);
    
    static Arrow* create(const char *szFileName);
    
    virtual void construct(IArrowEventListener *pListener, const CCPoint &startPos, const CCPoint &endPos);
    
    /** On update */
    virtual void onUpdate(float fDeltaTime);
    
/////////////////////////////////////////////////////////////////
// States
/////////////////////////////////////////////////////////////////
protected:
    
    /** Updates enter */
    virtual void updateEnter(float fDeltaTime);
    
    /** Updates move */
    virtual void updateMove(float fDeltaTime);
    
    /** Updates move (slow) */
    virtual void updateMove2(float fDeltaTime);
    
    /** Updates disappear */
    virtual void updateDisappear(float fDeltaTime);
    
    /** Updates exit */
    virtual void updateExit(float fDeltaTime);
    
/////////////////////////////////////////////////////////////////
// Accessors
/////////////////////////////////////////////////////////////////
public:
    
    /** Gets bounding box */
    virtual void getBoundingBox(CCPoint *vertices) const;
    
    /** Is active? */
    virtual bool isActive() const;
    
    /** On warning */
    virtual void onWarning();
    
protected:
    
    /** Disappear */
    virtual void disappear();
    
    /** On disappeared */
    virtual void onDisappeared();
    
public:
    
    virtual void draw();
    
/////////////////////////////////////////////////////////////////
// Attributes
/////////////////////////////////////////////////////////////////
protected:
    
    // The arrow event listener
    IArrowEventListener *m_pListener;
    
    // The end position
    CCPoint m_endPos;
    
    // The direction
    CCPoint m_dir;
    
    // The speed
    float m_fSpeed;
    
    // The acceleration
    float m_fAcceleration;
    
    // The remaining length
    float m_fRemainLength;
    
    // Is active?
    bool m_bActive;
    
    // The function pointer for updating
    void (Arrow::*m_pfUpdate)(float);
};

#endif // _ARROW_H_
