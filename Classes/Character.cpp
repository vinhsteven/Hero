
#include "gd.h"
#include "Character.h"
#include "ICharacterEventListener.h"

#ifdef DEBUG
//#define SHOW_BOUNDING_BOX
//#define SHOW_WARNING_BOX
#endif

#define BOUNDING_BOX_LEFT       -20.0f
#define BOUNDING_BOX_RIGHT      20.0f
#define BOUNDING_BOX_TOP        113.0f
#define BOUNDING_BOX_BOTTOM     0.0f

#define SPEED           250.0f
#define ACCELERATION    10.0f
#define MIN_SPEED       3.0f
#define ACC_FACTOR      2.5f

#define CHARACTER       "character.png"
#define CHARACTER_DIE   "character_die.png"

#define setCurrentState(state)  m_pfnUpdate = &Character::update##state

USING_NS_CC;

/////////////////////////////////////////////////////////////////
// ICharacterEventListener
/////////////////////////////////////////////////////////////////

// Null Object
ICharacterEventListener theNullCharacterEventListener;

/////////////////////////////////////////////////////////////////
// Character
/////////////////////////////////////////////////////////////////

Character::Character()
: m_pListener(&theNullCharacterEventListener)
{
    
}

bool Character::init(float fBoundaryLeft, float fBoundaryRight)
{
    if (CCSprite::initWithFile(CHARACTER))
    {
        // Sets bounding box
        m_boundingBox.construct(BOUNDING_BOX_LEFT, BOUNDING_BOX_TOP, BOUNDING_BOX_RIGHT, BOUNDING_BOX_BOTTOM);
        
        // Sets boundary left
        m_fBoundaryLeft = fBoundaryLeft;
        
        // Sets boundary right
        m_fBoundaryRight = fBoundaryRight;
        
        // Sets listener to null
        m_pListener = &theNullCharacterEventListener;
        
        //
        m_fSpeed        = SPEED;
        m_fAcceleration = ACCELERATION;
        
        //
        m_bPressed = false;
        
        // Updates for idle
        setCurrentState(Idle);
        
        // Sets anchor point
        setAnchorPoint(ccp(0.5f, 0.0f));
        
        setShaderProgram(pTheShaderCache->programForKey(kCCShader_PositionTextureColor));
        
        return true;
    }
    
    return false;
}

GD_IMPLEMENT_CREATE_2_ARGS(Character, float, fBoundaryLeft, float, fBoundaryRight);

AABB Character::getBoundingBox(void) const
{
    return AABB(m_obPosition, m_boundingBox);
}

void Character::setCharacterEventListener(ICharacterEventListener *pListener)
{
    m_pListener = (pListener ? pListener : &theNullCharacterEventListener);
}

void Character::onUpdate(float fDeltaTime)
{
    (this->*m_pfnUpdate)(fDeltaTime);
}

void Character::updateIdle(float fDeltaTime)
{
    // Do nothing
}

void Character::updateMoveLeft(float fDeltaTime)
{
    float fAcceleration = m_fAcceleration * (fDeltaTime / FRAME_DURATION);
    
    if (m_bPressed)
    {
        m_fSpeed += fAcceleration;
    }
    else
    {
        m_fSpeed -= fAcceleration * ACC_FACTOR;
    }
    
    float fX = m_obPosition.x - m_fSpeed * fDeltaTime;
    
    if (fX < m_fBoundaryLeft)
    {
        fX = m_fBoundaryLeft;
        
        setCurrentState(Idle);
    }
    else if (m_fSpeed < MIN_SPEED)
    {
        setCurrentState(Idle);
    }
    
    setPosition(ccp(fX, m_obPosition.y));
    
    // Sends event to the listener
    m_pListener->onCharacterPositionChanged(this);
}

void Character::updateMoveRight(float fDeltaTime)
{
    float fAcceleration = m_fAcceleration * (fDeltaTime / FRAME_DURATION);
    
    if (m_bPressed)
    {
        m_fSpeed += fAcceleration;
    }
    else
    {
        m_fSpeed -= fAcceleration * ACC_FACTOR;
    }
    
    float fX = m_obPosition.x + m_fSpeed * fDeltaTime;
    
    if (fX > m_fBoundaryRight)
    {
        fX = m_fBoundaryRight;
        
        setCurrentState(Idle);
    }
    else if (m_fSpeed < MIN_SPEED)
    {
        setCurrentState(Idle);
    }
    
    setPosition(ccp(fX, m_obPosition.y));
    
    // Sends event to the listener
    m_pListener->onCharacterPositionChanged(this);
}

void Character::updateDie(float fDeltaTime)
{
    
}

void Character::onPressed(bool bLeft)
{
    m_fSpeed = SPEED;
    
    m_bPressed = true;
    
    if (bLeft)
    {
        setCurrentState(MoveLeft);
    }
    else
    {
        setCurrentState(MoveRight);
    }
}

void Character::onReleased()
{
    m_bPressed = false;
}

void Character::onDied()
{
    //
    CCTexture2D *pTexture = pTheTextureCache->addImage(CHARACTER_DIE);
    setTexture(pTexture);
    
    // Creates action
    CCActionInterval *pZoomOut = CCScaleTo::create(0.2f, 1.2f);
    CCActionInterval *pZoomIn = CCScaleTo::create(0.1f, 1.0f);
    CCActionInterval *pZoom = CCSequence::create(pZoomOut, pZoomIn, NULL);
    
    CCActionInterval *pMoveUp = CCMoveBy::create(0.2f, ccp(0.0f, 20.0f));
    CCActionInterval *pMoveDown = pMoveUp->reverse();
    CCActionInterval *pMove = CCSequence::create(pMoveUp, pMoveDown, NULL);
    
    CCAction *pAction = CCSpawn::create(pZoom, pMove, NULL);
    
    // Runs action
    runAction(pAction);
    
    // Updates die
    setCurrentState(Die);
}

void Character::onReplay()
{
    // Stops all action
    stopAllActions();
    
    //
    CCTexture2D *pTexture = pTheTextureCache->addImage(CHARACTER);
    setTexture(pTexture);
    
    //
    m_fSpeed        = SPEED;
    m_fAcceleration = ACCELERATION;
    
    //
    m_bPressed = false;
    
    // Updates idle
    setCurrentState(Idle);
}

void Character::draw()
{
    CCSprite::draw();
    
#ifdef SHOW_BOUNDING_BOX
    ccDrawColor4F(0.0f, 0.0f, 1.0f, 1.0f);
    ccDrawRect(m_obAnchorPointInPoints + m_boundingBox.getBottomLeft(), m_boundingBox.getSize());
#endif
    
#ifdef SHOW_WARNING_BOX
    ccDrawColor4F(1.0f, 0.0f, 0.0f, 1.0f);
    ccDrawRect(m_obAnchorPointInPoints + m_warningBox.getBottomLeft(), m_warningBox.getSize());
#endif
    
#ifdef DEBUG
    ccDrawColor4F(0.0f, 1.0f, 0.0f, 1.0f);
    ccPointSize(5.0f);
    ccDrawPoint(m_obAnchorPointInPoints);
#endif
}
