
#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "ICharacterEventListener.h"
#include "IArrowEventListener.h"

USING_NS_CC;

class GameScene
: public CCLayer
, public ICharacterEventListener
, public IArrowEventListener
{
public:
    
    virtual bool init();
    
    static GameScene* create();
    
    static CCScene* scene();
    
    /** On update */
    virtual void onUpdate(float fDeltaTime);
    
    //
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    //
    virtual void onActionPerformed(int nTag);
    
    virtual void onTouchPressed(CCTouch *pTouch, int nTag);
    virtual void onTouchReleased(CCTouch *pTouch, int nTag);
    
    /** Throws arrows */
    void throwArrows(int nArrow);
    
    /** Game over */
    void gameOver();
    
    /** On game over callback */
    void onGameOverCallback();
    
    /** Replay */
    void replay();
    
    /////////////////////////////////////////////////////////////////
    // ICharacterEventListener
    /////////////////////////////////////////////////////////////////
public:
    
    /** On character position changed */
    virtual void onCharacterPositionChanged(Character *pCharacter);
    
    /////////////////////////////////////////////////////////////////
    // IArrowEventListener
    /////////////////////////////////////////////////////////////////
public:
    
    /** On arrow finished */
    virtual void onArrowFinished(Arrow *pArrow);
    
    /** On arrow exited */
    virtual void onArrowExited(Arrow *pArrow);
    
public:
    
    virtual void draw();
};

#endif  // _GAME_SCENE_H_
