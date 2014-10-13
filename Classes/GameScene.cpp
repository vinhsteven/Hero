
#include "gd.h"
#include "GameScene.h"
#include "TransparentButton.h"
#include "CrazyButton.h"
#include "StringButton.h"
#include "StringToggle.h"
#include "Arrow.h"
#include "Character.h"

#ifdef DEBUG
//#define SHOW_CHARACTER_BOX
//#define SHOW_ARROW_BOX
#define SHOW_CELL_BOX
#define SHOW_WARNING_LINE

#define SHOW_CHARACTER_BOUNDING_BOX

#define SHOW_VIEW

#define IMMORTAL
#endif

#define FONT_NAME   "Arial"
#define FONT_SIZE   64

#define BUTTON_FONT_SIZE    36
#define BUTTON_PRIORITY     3

#define CELL_COUNT      8
#define CELL_WIDTH      64.0f
#define CELL_GAP        48.0f
#define CELL_PADDING    32.0f

#define VIEW_HEIGHT 620.0f

#define ANGLE_COUNT     3
#define BLANK_COUNT     3
#define MAX_ARROWS      24

#define MIN_DIAGONAL_ARROW  s_nMinDiagonalArrow
#define MAX_DIAGONAL_ARROW  s_nMaxDiagonalArrow

#define CHARACTER_POS   ccp(s_viewCenter.x, s_fCharacterBottom)

#define THROW_DELAY_TIME    0.1f

#define SEL_UPDATE  schedule_selector(GameScene::onUpdate)

USING_NS_CC;

enum
{
    kTagControl,
    
    kTagPlay,
    kTagReplay,
    kTagGameOver,
    
    kTagPause,
    kTagResume,
    
#ifdef IMMORTAL
    kTagImmortal,
    kTagNormal,
#endif
    
    kTagArrows,
};

/////////////////////////////////////////////////////////////////
// Settings
/////////////////////////////////////////////////////////////////

static float s_fViewLeft   = 0.0f;
static float s_fViewTop    = 0.0f;
static float s_fViewRight  = 0.0f;
static float s_fViewBottom = 0.0f;

static CCPoint s_viewCenter;

static float s_fCharacterLeft   = 0.0f;
static float s_fCharacterTop    = 0.0f;
static float s_fCharacterRight  = 0.0f;
static float s_fCharacterBottom = 0.0f;

static float s_fArrowLeft   = 0.0f;
static float s_fArrowTop    = 0.0f;
static float s_fArrowRight  = 0.0f;
static float s_fArrowBottom = 0.0f;

static float s_fArrowMinCrossY = 0.0f;

static float s_fControlGap    = 0.0f;
static float s_fControlWidth  = 0.0f;
static float s_fControlHeight = 0.0f;

static float s_fWarningTop = 0.0f;

static void setup()
{
    float fViewWidth  = CELL_COUNT * (CELL_WIDTH + CELL_GAP) - CELL_GAP + CELL_PADDING * 2.0f;
    float fViewHeight = gdGetMin(theScreenSize.height, VIEW_HEIGHT);
    
    s_fViewLeft   = (theScreenSize.width - fViewWidth) * 0.5f;
    s_fViewRight  = theScreenSize.width - s_fViewLeft;
    s_fViewBottom = (theScreenSize.height - fViewHeight) * 0.5f;
    s_fViewTop    = theScreenSize.height - s_fViewBottom;
    
    s_viewCenter = ccp((s_fViewLeft + s_fViewRight) * 0.5f, (s_fViewTop + s_fViewBottom) * 0.5f);
    
    float fCharacterWidth = 80.0f;
    
    s_fCharacterLeft   = s_fViewLeft  + fCharacterWidth * 0.5f;
    s_fCharacterRight  = s_fViewRight - fCharacterWidth * 0.5f;
    s_fCharacterTop    = s_fViewTop;
    s_fCharacterBottom = s_fViewBottom;
    
    s_fArrowLeft   = s_fViewLeft  + CELL_PADDING;
    s_fArrowRight  = s_fViewRight - CELL_PADDING;
    s_fArrowTop    = s_fViewTop;
    s_fArrowBottom = s_fCharacterBottom + 10.0f;
    
    s_fArrowMinCrossY = s_fArrowTop - 50.0f;
    
    s_fControlGap = 0.0f;
    
    s_fControlWidth  = theScreenSize.width;
    s_fControlHeight = s_fViewBottom + fViewHeight * 0.5f;
    
    s_fWarningTop = s_fViewBottom + fViewHeight * 0.70f;
}

/////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////

// Array of available angles
static const float s_fAngles[ANGLE_COUNT] =
{
    CC_DEGREES_TO_RADIANS(60.0f),
    CC_DEGREES_TO_RADIANS(90.0f),
    CC_DEGREES_TO_RADIANS(120.0f),
};

// Sines
static const float s_fSines[ANGLE_COUNT] =
{
    sinf(s_fAngles[0]),
    sinf(s_fAngles[1]),
    sinf(s_fAngles[2]),
};

// Cosines
static const float s_fCosines[ANGLE_COUNT] =
{
    cosf(s_fAngles[0]),
    cosf(s_fAngles[1]),
    cosf(s_fAngles[2]),
};

// Angle indices
static int s_nAngleIndices[ANGLE_COUNT];

// Cell indices
static int s_nCellIndices[CELL_COUNT];

// The character
static Character *s_pCharacter = NULL;

// The pool of arrows
static CCArray *s_pArrowPool = NULL;

// The array of arrows
static CCArray *s_pArrows = NULL;

#ifdef SHOW_CHARACTER_BOUNDING_BOX
// The character bounding box
static RectangleNode *s_pBoundingBox = NULL;
#endif

// The minimum diagonal arrow
static int s_nMinDiagonalArrow = 0;

// The maximum diagonal arrow
static int s_nMaxDiagonalArrow = 0;

// The remaining diagonal arrow
static int s_nRemainingDiagonalArrow = 0;

// The score
static CCLabelTTF *s_pScore = NULL;

// The best score
static CCLabelTTF *s_pBestScore = NULL;

// The score
static int s_nScore = 0;

// The best score
static int s_nBestScore = 0;

// The total of arrows
static int s_nTotalArrows = 0;

// The number of finished arrows
static int s_nArrowCount = 0;

// The remaining throw delay time
static float s_fThrowDelayTime = 0.0f;

// Is warned?
static bool s_bWarned = false;

// Is game over?
static bool s_bGameOver = false;

#ifdef IMMORTAL
// Is immortal?
static bool s_bImmortal = false;
#endif

/////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////

/** Is diagonal angle? */
static inline bool isDiagonalAngle(int nAngleIndex)
{
    return (nAngleIndex != 1);
}

/** Gets arrow end position randomly */
static inline CCPoint getArrowEndPosition(int nCellIndex)
{
    float fMinX = s_fArrowLeft + nCellIndex * (CELL_WIDTH + CELL_GAP);
    float fMaxX = fMinX + CELL_WIDTH;
    
    return ccp(RANDOM_FLOAT_IN_RANGE(fMinX, fMaxX), s_fArrowBottom);
}

/** Gets arrow start position randomly */
static inline CCPoint getArrowStartPosition(const CCPoint &endPos)
{
    if (s_nRemainingDiagonalArrow == 0)
    {
        return ccp(endPos.x, s_fArrowTop);
    }
    
    swapArray(s_nAngleIndices, ANGLE_COUNT);
    
    int nIndex = 0;
    float fX, fY;
    float fSin, fCos;
    
    for (int i = 0; i < ANGLE_COUNT; i++)
    {
        nIndex = s_nAngleIndices[i];
        
        if (!isDiagonalAngle(nIndex))
        {
            return ccp(endPos.x, s_fArrowTop);
        }
        
        fSin = s_fSines[nIndex];
        fCos = s_fCosines[nIndex];
        
        // Left
        fY = gdGetCrossY(endPos, fSin, fCos, s_fArrowLeft);
        
        if (fY > endPos.y)
        {
            if (fY >= s_fArrowMinCrossY)
            {
                s_nRemainingDiagonalArrow--;
                
                fX = gdGetCrossX(endPos, fSin, fCos, s_fArrowTop);
                
                return ccp(fX, s_fArrowTop);
            }
        }
        else
        {
            // Right
            fY = gdGetCrossY(endPos, fSin, fCos, s_fArrowRight);
            GD_ASSERT(fY > endPos.y, "E89878767656");
            
            if (fY >= s_fArrowMinCrossY)
            {
                s_nRemainingDiagonalArrow--;
                
                fX = gdGetCrossX(endPos, fSin, fCos, s_fArrowTop);
                
                return ccp(fX, s_fArrowTop);
            }
        }
    }
    
    GD_ASSERT(true, "E89878767656: BUG!");
    
    return CCPointZero;
}

/////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////

GD_IMPLEMENT_CREATE(GameScene);

GD_IMPLEMENT_SCENE(GameScene);

bool GameScene::init()
{
    if (CCLayer::init())
    {
        setup();
        
        //
        for (int i = 0; i < ANGLE_COUNT; i++)
        {
            s_nAngleIndices[i] = i;
        }
        
        for (int i = 0; i < CELL_COUNT; i++)
        {
            s_nCellIndices[i] = i;
        }
        
        //
        s_nMinDiagonalArrow = 3;
        s_nMaxDiagonalArrow = 5;
        
        // Background
        RectangleNode *pBackground = RectangleNode::create(true);
        pBackground->setContentSize(theScreenSize);
        pBackground->setColor(WHITE_4F);
        pBackground->setAnchorPoint(CCPointZero);
        
        addChild(pBackground, -1);
        
#ifdef SHOW_CHARACTER_BOX
        {
            RectangleNode *pBox = RectangleNode::create();
            pBox->setContentSize(CCSizeMake(s_fCharacterRight - s_fCharacterLeft, s_fCharacterTop - s_fCharacterBottom));
            pBox->setAnchorPoint(AnchorPointBottomLeft);
            pBox->setPosition(ccp(s_fCharacterLeft, s_fCharacterBottom));
            pBox->setColor(BLUE_4F);
            
            addChild(pBox);
        }
#endif
        
#ifdef SHOW_ARROW_BOX
        {
            RectangleNode *pBox = RectangleNode::create();
            pBox->setContentSize(CCSizeMake(s_fArrowRight - s_fArrowLeft, s_fArrowTop - s_fArrowBottom));
            pBox->setAnchorPoint(AnchorPointBottomLeft);
            pBox->setPosition(ccp(s_fArrowLeft, s_fArrowBottom));
            pBox->setColor(RED_4F);
            
            LineNode *pLine1 = LineNode::create(ccp(0.0f, s_fArrowMinCrossY), ccp(s_fArrowLeft, s_fArrowMinCrossY));
            pLine1->setColor(MAGENTA_4F);
            
            LineNode *pLine2 = LineNode::create(ccp(s_fArrowRight, s_fArrowMinCrossY), ccp(theScreenSize.width, s_fArrowMinCrossY));
            pLine2->setColor(pLine1->getColor());
            
            addChild(pBox);
            addChild(pLine1);
            addChild(pLine2);
        }
#endif
        
#ifdef SHOW_CELL_BOX
        {
            CCSize size(CELL_WIDTH, 3.0f);
            
            float fX = s_fArrowLeft;
            float fY = s_fArrowBottom;
            float fDeltaX = CELL_WIDTH + CELL_GAP;
            
            for (int i = 0; i < CELL_COUNT; i++)
            {
                RectangleNode *pBox = RectangleNode::create();
                pBox->setContentSize(size);
                pBox->setAnchorPoint(AnchorPointBottomLeft);
                pBox->setPosition(ccp(fX, fY));
                pBox->setColor(GREEN_4F);
                
                addChild(pBox);
                
                fX += fDeltaX;
            }
        }
#endif
        
#ifdef SHOW_WARNING_LINE
        {
            LineNode *pLine = LineNode::create(ccp(0.0f, s_fWarningTop), ccp(theScreenSize.width, s_fWarningTop));
            pLine->setColor(MAGENTA_4F);
            
            addChild(pLine);
        }
#endif
        
#ifdef SHOW_VIEW
        {
            ccColor4F color = GRAY_4F;
            int zOrder = -1;
            
            // Left
            RectangleNode *pLeft = RectangleNode::create(true);
            pLeft->setContentSize(CCSizeMake(s_fViewLeft, s_fViewTop - s_fViewBottom));
            pLeft->setPosition(ccp(0.0f, s_fViewBottom));
            pLeft->setColor(color);
            pLeft->setZOrder(zOrder);
            
            // Right
            RectangleNode *pRight = RectangleNode::create(true);
            pRight->setContentSize(CCSizeMake(theScreenSize.width - s_fViewRight, s_fViewTop - s_fViewBottom));
            pRight->setPosition(ccp(s_fViewRight, s_fViewBottom));
            pRight->setColor(color);
            pRight->setZOrder(zOrder);
            
            // Top
            RectangleNode *pTop = RectangleNode::create(true);
            pTop->setContentSize(CCSizeMake(theScreenSize.width, theScreenSize.height - s_fViewTop));
            pTop->setPosition(ccp(0.0f, s_fViewTop));
            pTop->setColor(color);
            pTop->setZOrder(zOrder);
            
            // Bottom
            RectangleNode *pBottom = RectangleNode::create(true);
            pBottom->setContentSize(CCSizeMake(theScreenSize.width, s_fViewBottom));
            pBottom->setPosition(ccp(0.0f, 0.0f));
            pBottom->setColor(color);
            pBottom->setZOrder(zOrder);
            
            //
            addChild(pLeft);
            addChild(pRight);
            addChild(pTop);
            addChild(pBottom);
        }
#endif
        
        // Creates the character
        s_pCharacter = Character::create(s_fCharacterLeft, s_fCharacterRight);
        s_pCharacter->setCharacterEventListener(this);
        s_pCharacter->setPosition(CHARACTER_POS);
        
        addChild(s_pCharacter);
        
        // Creates pool of arrows
        s_pArrowPool = CCArray::createWithCapacity(MAX_ARROWS);
        s_pArrowPool->retain();
        
        for (int i = 0; i < MAX_ARROWS; i++)
        {
            Arrow *pArrow = Arrow::create("arrow.png");
            
            s_pArrowPool->addObject(pArrow);
        }
        
        // Creates array of arrows
        s_pArrows = CCArray::createWithCapacity(MAX_ARROWS);
        s_pArrows->retain();
        
#ifdef SHOW_CHARACTER_BOUNDING_BOX
        {
            // Gets bounding box
            AABB boundingBox = s_pCharacter->getBoundingBox();
            
            s_pBoundingBox = RectangleNode::create();
            s_pBoundingBox->setContentSize(boundingBox.getSize());
            s_pBoundingBox->setAnchorPoint(AnchorPointBottomLeft);
            s_pBoundingBox->setPosition(boundingBox.getBottomLeft());
            s_pBoundingBox->setColor(RED_4F);
            
            addChild(s_pBoundingBox);
        }
#endif
        
        // Control
        CrazyButton *pControl = CrazyButton::create(this, (SEL_CrazyButtonHandler)(&GameScene::onTouchPressed), (SEL_CrazyButtonHandler)(&GameScene::onTouchReleased));
        pControl->setContentSize(CCSizeMake(s_fControlWidth, s_fControlHeight));
        pControl->setAnchorPoint(AnchorPointBottomLeft);
//        pControl->setPosition(ccp(s_fViewLeft, s_fViewBottom));
        pControl->setPosition(ccp(0.0f, 0.0f));
        pControl->setTag(kTagControl);
        pControl->setTouchEnabled(false);
        
        addChild(pControl);
        
        // Creates score
        s_pScore = CCLabelTTF::create("0", FONT_NAME, FONT_SIZE);
        s_pScore->setColor(MAGENTA_3B);
        s_pScore->setPosition(ccp(theScreenSize.width * 0.5f, theScreenSize.height - 40.0f));
        
        addChild(s_pScore, 1);
        
        // Creates best score
        s_pBestScore = CCLabelTTF::create("Best: 0", FONT_NAME, 36.0f);
        s_pBestScore->setColor(GREEN_3B);
        s_pBestScore->setAnchorPoint(AnchorPointTopLeft);
        s_pBestScore->setPosition(ccp(theScreenSize.width - 150.0f, theScreenSize.height - 10.0f));
        
        addChild(s_pBestScore, 1);
        
        // Sets score
        s_nScore = 0;
        
        // Sets best score
        s_nBestScore = 0;
        
        // Sets total of arrows
        s_nTotalArrows = CELL_COUNT - BLANK_COUNT;
        
        // Sets number of finished arrows
        s_nArrowCount = 0;
        
        // Sets throw delay time
        s_fThrowDelayTime = THROW_DELAY_TIME;
        
        //
        s_bWarned   = false;
        s_bGameOver = false;
        
        // Creates Play button
        StringButton *pPlay = StringButton::create("Play", this, button_selector(GameScene::onActionPerformed));
        pPlay->setAnchorPoint(AnchorPointCenter);
        pPlay->setPosition(s_viewCenter);
        pPlay->setFontSize(BUTTON_FONT_SIZE);
        pPlay->setTouchPriority(BUTTON_PRIORITY);
        pPlay->setTag(kTagPlay);
        
        addChild(pPlay);
        
#ifdef DEBUG
        {
            float fX = 20.0f;
            float fY = theScreenSize.height - 20.0f;
            float fDeltaY = 50.0f;
            
            // Pause/Resume toggle
            StringToggle *pPauseResume = StringToggle::create("Pause", "Resume", kTagPause, kTagResume, false, this, button_selector(GameScene::onActionPerformed));
            pPauseResume->setAnchorPoint(AnchorPointTopLeft);
            pPauseResume->setPosition(ccp(fX, fY));
            pPauseResume->setTag(kTagPause);
            
            addChild(pPauseResume);
            
#ifdef IMMORTAL
            s_bImmortal = false;
            
            fY -= fDeltaY;
            
            // Immortal/Normal toggle
            StringToggle *pImmortalNormal = StringToggle::create("Immortal", "Normal", kTagImmortal, kTagNormal, s_bImmortal, this, button_selector(GameScene::onActionPerformed));
            pImmortalNormal->setAnchorPoint(AnchorPointTopLeft);
            pImmortalNormal->setPosition(ccp(fX, fY));
            pImmortalNormal->setTag(kTagImmortal);
            
            addChild(pImmortalNormal);
#endif // IMMORTAL
            
            int nArrowCount  = 5;
            int nButtonCount = CELL_COUNT - nArrowCount + 1;
            
            for (int i = 0; i < nButtonCount; i++)
            {
                fY -= fDeltaY;
                
                StringButton *pArrow = StringButton::create(gdGetString("%d arrows", nArrowCount), this, button_selector(GameScene::onActionPerformed));
                pArrow->setAnchorPoint(AnchorPointTopLeft);
                pArrow->setPosition(ccp(fX, fY));
                pArrow->setTag(kTagArrows + nArrowCount);
                
                addChild(pArrow);
                
                nArrowCount++;
            }
        }
#endif
        
        // Sets shader program
        setShaderProgram(pTheShaderCache->programForKey(kCCShader_PositionTextureColor));
        
        return true;
    }
    
    return false;
}

void GameScene::onUpdate(float fDeltaTime)
{
    // Updates the character
    s_pCharacter->onUpdate(fDeltaTime);
    
    if (s_bGameOver)
    {
        if (s_pArrows->count() == 0)
        {
            // Unschedule update
            unschedule(SEL_UPDATE);
        }
        else
        {
            // Updates all arrows
            CCObject *pObj = NULL;
            
            CCARRAY_FOREACH(s_pArrows, pObj)
            {
                Arrow *pArrow = (Arrow*)pObj;
                pArrow->onUpdate(fDeltaTime);
            }
        }
    }
    else
    {
        // Gets character bounding box
        AABB boundingBox = s_pCharacter->getBoundingBox();
        
        //
        static CCPoint vertices[4];
        
        //
        bool bWarn = false;
        
        // Updates all arrows
        CCObject *pObj = NULL;
        
        CCARRAY_FOREACH(s_pArrows, pObj)
        {
            Arrow *pArrow = (Arrow*)pObj;
            pArrow->onUpdate(fDeltaTime);
            
            // Checks if this arrow is active
            if (pArrow->isActive())
            {
                if (s_bWarned)
                {
                    // Gets arrow bounding box
                    pArrow->getBoundingBox(vertices);
                    
                    // Checks collision
                    if (gdIsParallelogramIntersectRectangle(vertices[0], vertices[1], vertices[2], vertices[3], boundingBox))
                    {
#ifdef IMMORTAL
                        if (s_bImmortal)
                        {
                            s_pCharacter->stopAllActions();
                            
                            // Creates action
                            CCActionInterval *pZoomOut = CCScaleTo::create(0.1f, 1.5f);
                            CCActionInterval *pZoomIn = CCScaleTo::create(0.1f, 1.0f);
                            CCAction *pAction = CCSequence::create(pZoomOut, pZoomIn, NULL);
                            
                            // Runs action
                            s_pCharacter->runAction(pAction);
                            
                            continue;
                        }
#endif
                        //
                        s_pCharacter->onDied();
                        
                        // Game over
                        gameOver();
                        
                        s_bGameOver = true;
                        
                        return;
                    }
                }
                else
                {
                    if (pArrow->getPosition().y <= s_fWarningTop)
                    {
                        s_bWarned = true;
                        
                        bWarn = true;
                    }
                }
            }
        }
        
        if (bWarn)
        {
            CCARRAY_FOREACH(s_pArrows, pObj)
            {
                Arrow *pArrow = (Arrow*)pObj;
                
                if (pArrow->isActive())
                {
                    pArrow->onWarning();
                }
            }
        }
        
        if (s_fThrowDelayTime > fDeltaTime)
        {
            s_fThrowDelayTime -= fDeltaTime;
        }
        else
        {
            if (s_fThrowDelayTime > 0.0f)
            {
                s_fThrowDelayTime = 0.0f;
                
                throwArrows(s_nTotalArrows);
            }
        }
    }
}

bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return false;
}

void GameScene::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void GameScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void GameScene::onActionPerformed(int nTag)
{
#ifdef DEBUG
    if (nTag >= kTagArrows)
    {
        if (s_bGameOver)
        {
            s_nTotalArrows = nTag - kTagArrows;
        }
        
        return;
    }
#endif
    
    switch (nTag)
    {
        case kTagPlay:
        {
            // Removes Play button
            removeChildByTag(kTagPlay, true);
            
            // Enables control
            AbstractButton *pControl = (AbstractButton*)getChildByTag(kTagControl);
            pControl->setTouchEnabled(true);
            
            // Schedules update
            schedule(SEL_UPDATE);
            
            break;
        }
        
        case kTagReplay:
        {
            replay();
            break;
        }
            
#ifdef DEBUG
        case kTagPause:
        {
            pTheDirector->pause();
            break;
        }
            
        case kTagResume:
        {
            pTheDirector->resume();
            break;
        }
            
#ifdef IMMORTAL
        case kTagImmortal:
        {
            s_bImmortal = true;
            break;
        }
            
        case kTagNormal:
        {
            s_bImmortal = false;
            break;
        }
#endif
#endif
    }
}

void GameScene::onTouchPressed(CCTouch *pTouch, int nTag)
{
    // Gets touch location
    CCPoint location = pTouch->getLocation();
    
    // Gets local
    CCPoint local = convertToNodeSpace(location);
    
    // Gets character bounding box
    AABB boundingBox = s_pCharacter->getBoundingBox();
    
    if (local.x < boundingBox.fLeft)
    {
        s_pCharacter->onPressed(true);
    }
    else if (local.x > boundingBox.fRight)
    {
        s_pCharacter->onPressed(false);
    }
}

void GameScene::onTouchReleased(CCTouch *pTouch, int nTag)
{
    s_pCharacter->onReleased();
}

void GameScene::throwArrows(int nArrow)
{
    GD_ASSERT(s_nArrowCount == 0, "E09898787676");
    
    swapArray(s_nCellIndices, CELL_COUNT);
    
    // Sets remaining diagonal arrow
    s_nRemainingDiagonalArrow = RANDOM_IN_RANGE(MIN_DIAGONAL_ARROW, MAX_DIAGONAL_ARROW);
    
    for (int i = 0; i < nArrow; i++)
    {
        CCPoint endPos   = getArrowEndPosition(s_nCellIndices[i]);
        CCPoint startPos = getArrowStartPosition(endPos);
        
        Arrow *pArrow = (Arrow*)s_pArrowPool->lastObject();
        pArrow->construct(this, startPos, endPos);
        
        addChild(pArrow);
        
        //
        s_pArrows->addObject(pArrow);
        s_pArrowPool->removeLastObject();
    }
}

void GameScene::gameOver()
{
    // Disables control
    AbstractButton *pControl  = (AbstractButton*)getChildByTag(kTagControl);
    pControl->setTouchEnabled(false);
    
    // Updates best score
    if (s_nScore > s_nBestScore)
    {
        s_nBestScore = s_nScore;
        
        s_pBestScore->setString(gdGetString("Best: %d", s_nBestScore));
    }
    
    // Shows "Game Over"
    CCLabelTTF *pLabel = CCLabelTTF::create("Game Over!", FONT_NAME, FONT_SIZE);
    pLabel->setColor(ORANGE_3B);
    pLabel->setPosition(s_viewCenter + ccp(0.0f, 100.0f));
    pLabel->setScale(0.5f);
    pLabel->setTag(kTagGameOver);
    
    //
    addChild(pLabel);
    
    // Creates action
    CCAction *pZoomOut = CCScaleTo::create(0.2f, 1.5f);
    CCAction *pZoomIn = CCScaleTo::create(0.1f, 1.0f);
    CCAction *pCallFunc = CCCallFunc::create(this, callfunc_selector(GameScene::onGameOverCallback));
    CCAction *pAction = CCSequence::create((CCActionInterval*)pZoomOut, pZoomIn, pCallFunc, NULL);
    
    // Runs action
    pLabel->runAction(pAction);
}

void GameScene::onGameOverCallback()
{
    // Replay button
    StringButton *pReplay = StringButton::create("Replay", this, button_selector(GameScene::onActionPerformed));
    pReplay->setFontSize(BUTTON_FONT_SIZE);
    pReplay->setPosition(s_viewCenter);
    pReplay->setAnchorPoint(AnchorPointCenter);
    pReplay->setTouchPriority(BUTTON_PRIORITY);
    pReplay->setTag(kTagReplay);
    
    addChild(pReplay);
}

void GameScene::replay()
{
    // Removes "Game Over"
    removeChildByTag(kTagGameOver, true);
    
    // Removes "Replay"
    removeChildByTag(kTagReplay, true);
    
    // Replay characters
    s_pCharacter->onReplay();
    s_pCharacter->setPosition(CHARACTER_POS);
    
    //
    onCharacterPositionChanged(s_pCharacter);
    
    // Enables controls
    AbstractButton *pControl  = (AbstractButton*)getChildByTag(kTagControl);
    pControl->setTouchEnabled(true);
    
    // Resets score
    s_pScore->setString("0");
    
    //
    s_nScore = 0;
    
    // Sets number of finished arrows
    s_nArrowCount = 0;
    
    // Sets throw delay time
    s_fThrowDelayTime = THROW_DELAY_TIME;
    
    //
    s_bWarned   = false;
    s_bGameOver = false;
    
    // Schedule update
    schedule(SEL_UPDATE);
}

/////////////////////////////////////////////////////////////////
// ICharacterEventListener
/////////////////////////////////////////////////////////////////

void GameScene::onCharacterPositionChanged(Character *pCharacter)
{
    // Gets bounding box
    AABB boundingBox = pCharacter->getBoundingBox();
    
#ifdef SHOW_CHARACTER_BOUNDING_BOX
    s_pBoundingBox->setPosition(boundingBox.getBottomLeft());
#endif
}

/////////////////////////////////////////////////////////////////
// IArrowEventListener
/////////////////////////////////////////////////////////////////

void GameScene::onArrowFinished(Arrow *pArrow)
{
    if (s_bGameOver)
    {
        return;
    }
    
    s_nArrowCount++;
    
    if (s_nArrowCount == s_nTotalArrows)
    {
        s_nArrowCount = 0;
        
        // Increases score
        s_nScore++;
        
        // Updates score
        s_pScore->setString(gdGetString("%d", s_nScore));
        
        // Creates action
        CCAction *pZoomOut = CCScaleTo::create(0.1f, 1.5f);
        CCAction *pZoomIn = CCScaleTo::create(0.1f, 1.0f);
        CCAction *pAction = CCSequence::create((CCActionInterval*)pZoomOut, pZoomIn, NULL);
        
        // Runs action
        s_pScore->runAction(pAction);
        
        //
        s_bWarned = false;
        
        // Sets throw delay time
        s_fThrowDelayTime = THROW_DELAY_TIME;
    }
}

void GameScene::onArrowExited(Arrow *pArrow)
{
    pArrow->retain();
    
    removeChild(pArrow);
    
    s_pArrows->removeObject(pArrow);
    
    s_pArrowPool->addObject(pArrow);
    
    pArrow->release();
}

void GameScene::draw()
{
    CC_NODE_DRAW_SETUP();
    
    static CCPoint vertices[4];
    
    CCObject *pObj = NULL;
    
    ccDrawColor4F(1.0f, 0.0f, 0.0f, 1.0f);
    
    CCARRAY_FOREACH(s_pArrows, pObj)
    {
        Arrow *pArrow = (Arrow*)pObj;
        pArrow->getBoundingBox(vertices);
        
        ccDrawPoly(vertices, 4, true);
    }
}
