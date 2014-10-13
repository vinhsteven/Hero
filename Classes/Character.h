
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

USING_NS_CC;

class ICharacterEventListener;

class Character : public CCSprite
{
public:
    
    Character();
    
    virtual bool init(float fBoundaryLeft, float fBoundaryRight);
    
    static Character* create(float fBoundaryLeft, float fBoundaryRight);
    
    /** Gets bounding box */
    virtual AABB getBoundingBox(void) const;
    
    /** Sets character event listener */
    virtual void setCharacterEventListener(ICharacterEventListener *pListener);
    
    /** On update */
    virtual void onUpdate(float fDeltaTime);
    
    /** Updates idle */
    virtual void updateIdle(float fDeltaTime);
    
    /** Updates move left */
    virtual void updateMoveLeft(float fDeltaTime);
    
    /** Updates move right */
    virtual void updateMoveRight(float fDeltaTime);
    
    /** Updates die */
    virtual void updateDie(float fDeltaTime);
    
    /** On pressed */
    virtual void onPressed(bool bLeft);
    
    /** On released */
    virtual void onReleased();
    
    /** On died */
    virtual void onDied();
    
    /** On replay */
    virtual void onReplay();
    
    virtual void draw();
    
protected:
    
    // The bounding box
    AABB m_boundingBox;
    
    // The boundary left
    float m_fBoundaryLeft;
    
    // The boundary right
    float m_fBoundaryRight;
    
    // The character event listener
    ICharacterEventListener *m_pListener;
    
    // The speed
    float m_fSpeed;
    
    // The acceleration
    float m_fAcceleration;
    
    // Is pressed?
    bool m_bPressed;
    
    // The function pointer for update
    void (Character::*m_pfnUpdate)(float);
};

#endif // _CHARACTER_H_
