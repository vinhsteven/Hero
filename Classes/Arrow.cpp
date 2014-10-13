
#include "gd.h"
#include "Arrow.h"
#include "IArrowEventListener.h"

#ifdef DEBUG
//#define SHOW_BOUNDING_BOX
#endif

#define BOUNDING_BOX_LEFT       -64.0f
#define BOUNDING_BOX_RIGHT      0.0f
#define BOUNDING_BOX_TOP        8.0f
#define BOUNDING_BOX_BOTTOM     -8.0f

#define SPEED           500.0f
#define MIN_SPEED       100.0f
#define ACCELERATION    5.0f
#define ACCELERATION_2  (ACCELERATION * 3.0f)
#define ACCELERATION_3  (ACCELERATION * 10.0f)
#define FADE_DURATION   0.5f

#define setCurrentState(state)  m_pfUpdate = &Arrow::update##state

USING_NS_CC;

/////////////////////////////////////////////////////////////////
// IArrowEventListener
/////////////////////////////////////////////////////////////////

// Null Object
IArrowEventListener theNullArrowEventListener;

/////////////////////////////////////////////////////////////////
// Arrow
/////////////////////////////////////////////////////////////////

Arrow::Arrow()
: m_pListener(&theNullArrowEventListener)
, m_endPos(CCPointZero)
, m_dir(CCPointZero)
, m_fSpeed(0.0f)
, m_fAcceleration(0.0f)
, m_fRemainLength(0.0f)
, m_bActive(false)
{
    setCurrentState(Exit);
}

bool Arrow::init(const char *szFileName)
{
    if (CCSprite::initWithFile(szFileName))
    {
        // Sets anchor point
        setAnchorPoint(ccp(1.0f, 0.5f));
        
        setShaderProgram(pTheShaderCache->programForKey(kCCShader_PositionTextureColor));
        
        return true;
    }
    
    return false;
}

GD_IMPLEMENT_CREATE_1_ARG(Arrow, const char*, szFileName);

void Arrow::construct(IArrowEventListener *pListener, const CCPoint &startPos, const CCPoint &endPos)
{
    // Sets listener
    m_pListener = (pListener ? pListener : &theNullArrowEventListener);
    
    // Sets position
    setPosition(startPos);
    
    // Sets end position
    m_endPos = endPos;
    
    // Gets delta position
    CCPoint deltaPos = endPos - startPos;
    
    // Gets angle
    float fAngle = deltaPos.getAngle();
    
    // Sets rotation
    setRotation(gdGetRotation(fAngle));
    
    // Sets opacity
    setOpacity(255);
    
    // Sets direction
    m_dir = ccp(cosf(fAngle), sinf(fAngle));
    
    // Sets speed
    m_fSpeed = SPEED;
    
    // Sets acceleration
    m_fAcceleration = ACCELERATION;
    
    // Sets remaining length
    m_fRemainLength = deltaPos.getLength();
    
    //
    m_bActive = false;
    
    // Updates for enter
    setCurrentState(Enter);
}

void Arrow::onUpdate(float fDeltaTime)
{
    (this->*m_pfUpdate)(fDeltaTime);
}

/////////////////////////////////////////////////////////////////
// States
/////////////////////////////////////////////////////////////////

void Arrow::updateEnter(float fDeltaTime)
{
    m_bActive = true;
    
    // Updates move
    setCurrentState(Move);
}

void Arrow::updateMove(float fDeltaTime)
{
    m_fSpeed += m_fAcceleration * (fDeltaTime / FRAME_DURATION);
    
    CCPoint deltaPos = m_dir * m_fSpeed * fDeltaTime;
    
    float fLength = deltaPos.getLength();
    
    if (fLength < m_fRemainLength)
    {
        m_fRemainLength -= fLength;
        
        setPosition(m_obPosition + deltaPos);
    }
    else
    {
        m_fRemainLength = 0.0f;
        
        setPosition(m_endPos);
        
        // Disappear
        disappear();
    }
}

void Arrow::updateMove2(float fDeltaTime)
{
    m_fSpeed -= ACCELERATION_2 * (fDeltaTime / FRAME_DURATION);
    
    if (m_fSpeed < MIN_SPEED)
    {
        // Sets acceleration
        m_fAcceleration = ACCELERATION_3;
        
        // Updates move
        setCurrentState(Move);
    }
    else
    {
        CCPoint deltaPos = m_dir * m_fSpeed * fDeltaTime;
        
        float fLength = deltaPos.getLength();
        
        if (fLength < m_fRemainLength)
        {
            m_fRemainLength -= fLength;
            
            setPosition(m_obPosition + deltaPos);
        }
        else
        {
            m_fRemainLength = 0.0f;
            
            setPosition(m_endPos);
            
            // Disappear
            disappear();
        }
    }
}

void Arrow::updateDisappear(float fDeltaTime)
{
    
}

void Arrow::updateExit(float fDeltaTime)
{
    // Do nothing
}

/////////////////////////////////////////////////////////////////
// Accessors
/////////////////////////////////////////////////////////////////

void Arrow::getBoundingBox(CCPoint *vertices) const
{
    static CCPoint topLeft(BOUNDING_BOX_LEFT, BOUNDING_BOX_TOP);
    static CCPoint topRight(BOUNDING_BOX_RIGHT, BOUNDING_BOX_TOP);
    static CCPoint bottomRight(BOUNDING_BOX_RIGHT, BOUNDING_BOX_BOTTOM);
    static CCPoint bottomLeft(BOUNDING_BOX_LEFT, BOUNDING_BOX_BOTTOM);
    
    vertices[0] = topLeft;
    vertices[1] = topRight;
    vertices[2] = bottomRight;
    vertices[3] = bottomLeft;
    
    gdRotatePoints(vertices, 4, m_obPosition, m_fRotationX);
}

bool Arrow::isActive() const
{
    return m_bActive;
}

void Arrow::onWarning()
{
    // Updates move (slow)
    setCurrentState(Move2);
}

void Arrow::disappear()
{
    m_bActive = false;
    
    // Updates for disappear
    setCurrentState(Disappear);
    
    // Sends event to listener
    m_pListener->onArrowFinished(this);
    
    // Creates action
    CCAction *pFadeOut = CCFadeOut::create(FADE_DURATION);
    CCAction *pCallFunc = CCCallFunc::create(this, callfunc_selector(Arrow::onDisappeared));
    CCAction *pAction = CCSequence::create((CCActionInterval*)pFadeOut, pCallFunc, NULL);
    
    // Runs action
    runAction(pAction);
}

void Arrow::onDisappeared()
{
    // Stops all action
    stopAllActions();
    
    // Update exit
    setCurrentState(Exit);
    
    // Sends event to listener
    m_pListener->onArrowExited(this);
}

void Arrow::draw()
{
    CCSprite::draw();
    
#ifdef SHOW_BOUNDING_BOX
    CCPoint position(m_obAnchorPointInPoints.x + BOUNDING_BOX_LEFT, m_obAnchorPointInPoints.y + BOUNDING_BOX_BOTTOM);
    CCSize size(BOUNDING_BOX_RIGHT - BOUNDING_BOX_LEFT, BOUNDING_BOX_TOP - BOUNDING_BOX_BOTTOM);
    
    ccDrawColor4F(1.0f, 0.0f, 0.0f, 1.0f);
    ccDrawRect(position, size);
#endif
}
