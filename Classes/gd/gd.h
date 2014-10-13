
#ifndef _GD_GD_H_
#define _GD_GD_H_

#include "cocos2d.h"

#include <stdio.h>
#include <stdarg.h>

#include "AABB.h"
#include "StringHelper.h"
#include "ColorHelper.h"
#include "PositionHelper.h"
#include "AnimationHelper.h"
#include "ArrayHelper.h"

#include "nodes/package.h"

#define FRAME_DURATION  0.02f

/////////////////////////////////////////////////////////////////
// Platform
/////////////////////////////////////////////////////////////////

#define IS_PLATFORM_WIN()       ((CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8))
#define IS_PLATFORM_WINRT()     (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
#define IS_PLATFORM_WP8()       (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)

#define IS_PLATFORM_IOS()       (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

/////////////////////////////////////////////////////////////////
// Debug
/////////////////////////////////////////////////////////////////

#define GD_ASSERT               CCAssert
#define GD_LOG                  CCLOG

#define GD_NOT_SUPPORTED(format, ...)   CCAssert(false, gdGetString("[NOT SUPPORTED: "format"]", ##__VA_ARGS__))
#define GD_TODO(format, ...)            CCAssert(false, gdGetString("[TODO: "format"]", ##__VA_ARGS__))

/////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////

#define RANDOM_0_N_EXCLUSIVE(n)         (random() % (n))
#define RANDOM_IN_RANGE(min, max)       (int)(min + (random() / (float)RAND_MAX) * (max - (min) + 1))
#define RANDOM_FLOAT_IN_RANGE(min, max) (min + ((random() / (float)RAND_MAX)) * (max - (min)))

#define gdGetArrayLength(array) (sizeof(array) / sizeof(array[0]))

/////////////////////////////////////////////////////////////////
// Memory
/////////////////////////////////////////////////////////////////

#define GD_NEW(type)            new type()
#define GD_DELETE(p)            delete (p); (p) = 0

#define GD_SAFE_DELETE          CC_SAFE_DELETE
#define GD_SAFE_DELETE_ARRAY    CC_SAFE_DELETE_ARRAY
#define GD_SAFE_FREE            CC_SAFE_FREE
#define GD_SAFE_RELEASE         CC_SAFE_RELEASE
#define GD_SAFE_RELEASE_NULL    CC_SAFE_RELEASE_NULL
#define GD_SAFE_RETAIN          CC_SAFE_RETAIN

/////////////////////////////////////////////////////////////////
// Singleton
/////////////////////////////////////////////////////////////////

#define pTheDirector            CCDirector::sharedDirector()
#define pTheOpenGLView          CCEGLView::sharedOpenGLView()
#define pTheShaderCache         CCShaderCache::sharedShaderCache()
#define pTheSpriteFrameCache    CCSpriteFrameCache::sharedSpriteFrameCache()
#define pTheAnimationCache      CCAnimationCache::sharedAnimationCache()
#define pTheTextureCache        CCTextureCache::sharedTextureCache()

/////////////////////////////////////////////////////////////////
// Manually
/////////////////////////////////////////////////////////////////

#define GD_IMPLEMENT_CREATE(class);         \
class* class::create()                      \
{                                           \
    class *p = GD_NEW(class);               \
                                            \
    if (p)                                  \
    {                                       \
        if (p->init())                      \
        {                                   \
            p->autorelease();               \
        }                                   \
        else                                \
        {                                   \
            GD_DELETE(p);                   \
        }                                   \
    }                                       \
                                            \
    return p;                               \
}                                           \

#define GD_IMPLEMENT_CREATE_1_ARG(class, type1, arg1);  \
class* class::create(type1 arg1)            \
{                                           \
    class *p = GD_NEW(class);               \
                                            \
    if (p)                                  \
    {                                       \
        if (p->init(arg1))                  \
        {                                   \
            p->autorelease();               \
        }                                   \
        else                                \
        {                                   \
            GD_DELETE(p);                   \
        }                                   \
    }                                       \
                                            \
    return p;                               \
}                                           \

#define GD_IMPLEMENT_CREATE_2_ARGS(class, type1, arg1, type2, arg2);    \
class* class::create(type1 arg1, type2 arg2)\
{                                           \
    class *p = GD_NEW(class);               \
                                            \
    if (p)                                  \
    {                                       \
        if (p->init(arg1, arg2))            \
        {                                   \
            p->autorelease();               \
        }                                   \
        else                                \
        {                                   \
            GD_DELETE(p);                   \
        }                                   \
    }                                       \
                                            \
    return p;                               \
}                                           \

#define GD_IMPLEMENT_CREATE_3_ARGS(class, type1, arg1, type2, arg2, type3, arg3);   \
class* class::create(type1 arg1, type2 arg2, type3 arg3)    \
{                                           \
    class *p = GD_NEW(class);               \
                                            \
    if (p)                                  \
    {                                       \
        if (p->init(arg1, arg2, arg3))      \
        {                                   \
            p->autorelease();               \
        }                                   \
        else                                \
        {                                   \
            GD_DELETE(p);                   \
        }                                   \
    }                                       \
                                            \
    return p;                               \
}                                           \

#define GD_IMPLEMENT_CREATE_4_ARGS(class, type1, arg1, type2, arg2, type3, arg3, type4, arg4);  \
class* class::create(type1 arg1, type2 arg2, type3 arg3, type4 arg4)    \
{                                           \
    class *p = GD_NEW(class);               \
                                            \
    if (p)                                  \
    {                                       \
        if (p->init(arg1, arg2, arg3, arg4))\
        {                                   \
            p->autorelease();               \
        }                                   \
        else                                \
        {                                   \
            GD_DELETE(p);                   \
        }                                   \
    }                                       \
                                            \
    return p;                               \
}                                           \

#define GD_IMPLEMENT_SCENE(class);          \
CCScene* class::scene()                     \
{                                           \
    CCScene *pScene = CCScene::create();    \
                                            \
    class *p = class::create();             \
                                            \
    pScene->addChild(p);                    \
                                            \
    return pScene;                          \
}                                           \

#define GD_IMPLEMENT_GET_SET(funcName, varType, varName);               \
virtual varType get##funcName() const { return m_##varName; }           \
virtual void set##funcName(varType varName) { m_##varName = varName; }  \

/////////////////////////////////////////////////////////////////
// Globals
/////////////////////////////////////////////////////////////////

// The screen size
extern cocos2d::CCSize theScreenSize;

extern void gdInit();

/////////////////////////////////////////////////////////////////
// Helpers
/////////////////////////////////////////////////////////////////

// Gets minimum
template <class T>
static inline T gdGetMin(T a, T b)
{
    return (a < b ? a : b);
}

// Gets maximum
template <class T>
static inline T gdGetMax(T a, T b)
{
    return (a > b ? a : b);
}

// Gets ratation in degrees (fAngle in radians)
extern float gdGetRotation(float fAngle);

// Gets ratation in degrees
extern float gdGetRotation(const CCPoint &point);

// Gets point by rotate around a pivot (degrees)
extern CCPoint gdGetPointByRotate(const CCPoint &point, const CCPoint &pivot, float fAngle);

// Rotates given points around a pivot (degrees)
extern void gdRotatePoints(CCPoint *points, int nPointCount, const CCPoint &pivot, float fAngle);

// Checks if segment intersect rectangle
extern bool gdIsSegmentIntersectRectangle(const CCPoint &point1, const CCPoint &point2, const AABB &rect);

// Checks if parallelogram intersect rectangle
extern bool gdIsParallelogramIntersectRectangle(const CCPoint &point1, const CCPoint &point2, const CCPoint &point3, const CCPoint &point4,
                                                const AABB &rect);

// Gets x-cross (radians, x-axis, counter-clockwise)
extern float gdGetCrossX(const CCPoint &point, float fAngle, float fY);

// Gets y-cross (radians, x-axis, counter-clockwise)
extern float gdGetCrossY(const CCPoint &point, float fAngle, float fX);

// Gets x-cross (radians, x-axis, counter-clockwise)
extern float gdGetCrossX(const CCPoint &point, float fSin, float fCos, float fY);

// Gets y-cross (radians, x-axis, counter-clockwise)
extern float gdGetCrossY(const CCPoint &point, float fSin, float fCos, float fX);

#endif // _GD_GD_H_
