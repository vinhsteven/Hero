
#include "gd.h"

USING_NS_CC;

// The screen size
CCSize theScreenSize;

void gdInit()
{
    // Sets the screen size
    theScreenSize = pTheOpenGLView->getFrameSize();
}

/////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////

/** Gets y-position of the given x-position on the given line */
#define GetYPosition(fX, fX1, fY1, fX2, fY2)    (((fY2 - (fY1)) / (fX2 - (fX1))) * (fX - (fX1)) + fY1)

enum
{
    kTopLeft = 0,
    kTop,
    kTopRight,
    kLeft,
    kCenter,
    kRight,
    kBottomLeft,
    kBottom,
    kBottomRight
};

/** Gets relative position of point to rectangle */
static inline int GetRelativePosition(const CCPoint &point, const AABB &rect)
{
#define fX      point.x
#define fY      point.y
    
#define fLeft   rect.fLeft
#define fTop    rect.fTop
#define fRight  rect.fRight
#define fBottom rect.fBottom
    
    // Left
    if (fX < fLeft)
    {
        // Top
        if (fY > fTop)
        {
            return kTopLeft;
        }
        
        // Bottom
        if (fY < fBottom)
        {
            return kBottomLeft;
        }
        
        return kLeft;
    }
    
    // Right
    if (fX > fRight)
    {
        // Top
        if (fY > fTop)
        {
            return kTopRight;
        }
        
        // Bottom
        if (fY < fBottom)
        {
            return kBottomRight;
        }
        
        return kRight;
    }
    
    // Center
    {
        // Top
        if (fY > fTop)
        {
            return kTop;
        }
        
        // Bottom
        if (fY < fBottom)
        {
            return kBottom;
        }
        
        return kCenter;
    }
    
#undef fX
#undef fY
    
#undef fLeft
#undef fTop
#undef fRight
#undef fBottom
}

/////////////////////////////////////////////////////////////////
// Helpers
/////////////////////////////////////////////////////////////////

float gdGetRotation(float fAngle)
{
    return 360.0f - CC_RADIANS_TO_DEGREES(fAngle);
}

float gdGetRotation(const CCPoint &point)
{
    float fAngle = point.getAngle();
    
    return 360.0f - CC_RADIANS_TO_DEGREES(fAngle);
}

CCPoint gdGetPointByRotate(const CCPoint &point, const CCPoint &pivot, float fAngle)
{
    fAngle = CC_DEGREES_TO_RADIANS(360.0f - fAngle);
    
    float fSin = sinf(fAngle);
    float fCos = cosf(fAngle);
    
    return CCPointMake(pivot.x + point.x * fCos - point.y * fSin, pivot.y + point.x * fSin + point.y * fCos);
}

void gdRotatePoints(CCPoint *points, int nPointCount, const CCPoint &pivot, float fAngle)
{
    fAngle = CC_DEGREES_TO_RADIANS(360.0f - fAngle);
    
    float fSin = sinf(fAngle);
    float fCos = cosf(fAngle);
    float fX, fY;
    
    for (int i = 0; i < nPointCount; i++)
    {
        fX = pivot.x + points[i].x * fCos - points[i].y * fSin;
        fY = pivot.y + points[i].x * fSin + points[i].y * fCos;
        
        points[i].setPoint(fX, fY);
    }
}

bool gdIsSegmentIntersectRectangle(const CCPoint &point1, const CCPoint &point2, const AABB &rect)
{
#define fX1     point1.x
#define fY1     point1.y
#define fX2     point2.x
#define fY2     point2.y
    
#define _X0     rect.fLeft
#define _X1     rect.fRight
#define _X2     _X0
#define _X3     _X1
    
#define _Y0     rect.fTop
#define _Y1     _Y0
#define _Y2     rect.fBottom
#define _Y3     _Y2

#define IsAbove0()  GetYPosition(_X0, fX1, fY1, fX2, fY2) >  _Y0
#define IsBelow0()  GetYPosition(_X0, fX1, fY1, fX2, fY2) <= _Y0
#define IsAbove1()  GetYPosition(_X1, fX1, fY1, fX2, fY2) >  _Y1
#define IsBelow1()  GetYPosition(_X1, fX1, fY1, fX2, fY2) <= _Y1
#define IsAbove2()  GetYPosition(_X2, fX1, fY1, fX2, fY2) >  _Y2
#define IsBelow2()  GetYPosition(_X2, fX1, fY1, fX2, fY2) <= _Y2
#define IsAbove3()  GetYPosition(_X3, fX1, fY1, fX2, fY2) >  _Y3
#define IsBelow3()  GetYPosition(_X3, fX1, fY1, fX2, fY2) <= _Y3
    
    int nDir1 = GetRelativePosition(point1, rect);
    if (nDir1 == kCenter)
    {
        return true;
    }
    
    int nDir2 = GetRelativePosition(point2, rect);
    if (nDir2 == kCenter)
    {
        return true;
    }
    
    if (nDir1 == nDir2)
    {
        return false;
    }
    
    // Top-Left
    if (nDir1 == kTopLeft)
    {
        // Right
        if (nDir2 == kRight)
        {
            return IsBelow1();
        }
        
        // Bottom
        if (nDir2 == kBottom)
        {
            return IsAbove2();
        }
        
        // Bottom-Right
        if (nDir2 == kBottomRight)
        {
            if (IsAbove1())
            {
                return false;
            }
            
            if (IsBelow2())
            {
                return false;
            }
            
            return true;
        }
        
        return false;
    }
    
    // Top-Right
    if (nDir1 == kTopRight)
    {
        // Left
        if (nDir2 == kLeft)
        {
            return IsBelow0();
        }
        
        // Bottom
        if (nDir2 == kBottom)
        {
            return IsAbove3();
        }
        
        // Bottom-Left
        if (nDir2 == kBottomLeft)
        {
            if (IsAbove0())
            {
                return false;
            }
            
            if (IsBelow3())
            {
                return false;
            }
            
            return true;
        }
        
        return false;
    }
    
    // Bottom-Left
    if (nDir1 == kBottomLeft)
    {
        // Top
        if (nDir2 == kTop)
        {
            return IsBelow0();
        }
        
        // Right
        if (nDir2 == kRight)
        {
            return IsAbove3();
        }
        
        // Top-Right
        if (nDir2 == kTopRight)
        {
            if (IsAbove0())
            {
                return false;
            }
            
            if (IsBelow3())
            {
                return false;
            }
            
            return true;
        }
        
        return false;
    }
    
    // Bottom-Right
    if (nDir1 == kBottomRight)
    {
        // Top
        if (nDir2 == kTop)
        {
            return IsBelow1();
        }
        
        // Left
        if (nDir2 == kLeft)
        {
            return IsAbove2();
        }
        
        // Top-Left
        if (nDir2 == kTopLeft)
        {
            if (IsAbove1())
            {
                return false;
            }
            
            if (IsBelow2())
            {
                return false;
            }
            
            return true;
        }
        
        return false;
    }
    
    // Top
    if (nDir1 == kTop)
    {
        // Top-Left | Top-Right
        if (nDir2 == kTopLeft || nDir2 == kTopRight)
        {
            return false;
        }
        
        // Bottom
        if (nDir2 == kBottom)
        {
            return true;
        }
        
        // Left
        if (nDir2 == kLeft || nDir2 == kBottomLeft)
        {
            return IsBelow0();
        }
        
        // Right
        return IsBelow1();
    }
    
    // Left
    if (nDir1 == kLeft)
    {
        // Top-Left | Bottom-Left
        if (nDir2 == kTopLeft || nDir2 == kBottomLeft)
        {
            return false;
        }
        
        // Right
        if (nDir2 == kRight)
        {
            return true;
        }
        
        // Top
        if (nDir2 == kTop || nDir2 == kTopRight)
        {
            return IsBelow0();
        }
        
        // Bottom
        return IsAbove2();
    }
    
    // Right
    if (nDir1 == kRight)
    {
        // Top-Right | Bottom-Right
        if (nDir2 == kTopRight || nDir2 == kBottomRight)
        {
            return false;
        }
        
        // Left
        if (nDir2 == kLeft)
        {
            return true;
        }
        
        // Top
        if (nDir2 == kTopLeft || nDir2 == kTop)
        {
            return IsBelow1();
        }
        
        // Bottom
        return IsAbove3();
    }
    
    // Bottom
    if (nDir1 == kBottom)
    {
        // Bottom-Left | Bottom-Right
        if (nDir2 == kBottomLeft || nDir2 == kBottomRight)
        {
            return false;
        }
        
        // Top
        if (nDir2 == kTop)
        {
            return true;
        }
        
        // Left
        if (nDir2 == kTopLeft || nDir2 == kLeft)
        {
            return IsAbove2();
        }
        
        // Right
        return IsAbove3();
    }
    
    return true;
    
#undef fX1
#undef fY1
#undef fX2
#undef fY2

#undef _X0
#undef _X1
#undef _X2
#undef _X3
    
#undef _Y0
#undef _Y1
#undef _Y2
#undef _Y3
    
#undef IsAbove0
#undef IsBelow0
#undef IsAbove1
#undef IsBelow1
#undef IsAbove2
#undef IsBelow2
#undef IsAbove3
#undef IsBelow3
}

bool gdIsParallelogramIntersectRectangle(const CCPoint &point1, const CCPoint &point2, const CCPoint &point3, const CCPoint &point4,
                                         const AABB &rect)
{
    float fLeft   = point1.x;
    float fRight  = point1.x;
    float fTop    = point1.y;
    float fBottom = point1.y;
    
    if (fLeft > point2.x) fLeft = point2.x;
    if (fLeft > point3.x) fLeft = point3.x;
    if (fLeft > point4.x) fLeft = point4.x;
    
    if (fRight < point2.x) fRight = point2.x;
    if (fRight < point3.x) fRight = point3.x;
    if (fRight < point4.x) fRight = point4.x;
    
    if (fTop < point2.y) fTop = point2.y;
    if (fTop < point3.y) fTop = point3.y;
    if (fTop < point4.y) fTop = point4.y;
    
    if (fBottom > point2.y) fBottom = point2.y;
    if (fBottom > point3.y) fBottom = point3.y;
    if (fBottom > point4.y) fBottom = point4.y;
    
    if (fLeft   > rect.fRight)  return false;
    if (fRight  < rect.fLeft)   return false;
    if (fTop    < rect.fBottom) return false;
    if (fBottom > rect.fTop)    return false;
    
    if (gdIsSegmentIntersectRectangle(point1, point2, rect)) return true;
    if (gdIsSegmentIntersectRectangle(point2, point3, rect)) return true;
    if (gdIsSegmentIntersectRectangle(point3, point4, rect)) return true;
    if (gdIsSegmentIntersectRectangle(point4, point1, rect)) return true;
    
    return false;
}

float gdGetCrossX(const CCPoint &point, float fAngle, float fY)
{
//    if (fAngle < 0.0f)
//    {
//        do
//        {
//            fAngle += 360.0f;
//        }
//        while (fAngle < 0.0f);
//    }
//    else if (fAngle > 360.0f)
//    {
//        do
//        {
//            fAngle -= 360.0f;
//        }
//        while (fAngle > 360.0f);
//    }
//    
//    if (fAngle == 0.0f || fAngle == 180.0f)
//    {
//        return INFINITY;
//    }
//    
//    if (fAngle == 90.0f || fAngle == 270.0f)
//    {
//        return point.x;
//    }
//    
//    float fA = tanf(CC_DEGREES_TO_RADIANS(fAngle));
    
    float fSin = sinf(fAngle);
    
    if (fSin == 0.0f)
    {
        return INFINITY;
    }
    
    float fCos = cosf(fAngle);
    
    if (fCos == 0.0f)
    {
        return point.x;
    }
    
    float fA = fSin / fCos;
    float fB = point.y - fA * point.x;
    
    return (fY - fB) / fA;
}

float gdGetCrossY(const CCPoint &point, float fAngle, float fX)
{
//    if (fAngle < 0.0f)
//    {
//        do
//        {
//            fAngle += 360.0f;
//        }
//        while (fAngle < 0.0f);
//    }
//    else if (fAngle > 360.0f)
//    {
//        do
//        {
//            fAngle -= 360.0f;
//        }
//        while (fAngle > 360.0f);
//    }
//    
//    if (fAngle == 0.0f || fAngle == 180.0f)
//    {
//        return point.y;
//    }
//    
//    if (fAngle == 90.0f || fAngle == 270.0f)
//    {
//        return INFINITY;
//    }
//    
//    float fA = tanf(CC_DEGREES_TO_RADIANS(fAngle));
    
    float fSin = sinf(fAngle);
    
    if (fSin == 0.0f)
    {
        return point.y;
    }
    
    float fCos = cosf(fAngle);
    
    if (fCos == 0.0f)
    {
        return INFINITY;
    }
    
    float fA = fSin / fCos;
    float fB = point.y - fA * point.x;
    
    return fA * fX + fB;
}

float gdGetCrossX(const CCPoint &point, float fSin, float fCos, float fY)
{
    if (fSin == 0.0f)
    {
        return INFINITY;
    }
    
    if (fCos == 0.0f)
    {
        return point.x;
    }
    
    float fA = fSin / fCos;
    float fB = point.y - fA * point.x;
    
    return (fY - fB) / fA;
}

float gdGetCrossY(const CCPoint &point, float fSin, float fCos, float fX)
{
    if (fSin == 0.0f)
    {
        return point.y;
    }
    
    if (fCos == 0.0f)
    {
        return INFINITY;
    }
    
    float fA = fSin / fCos;
    float fB = point.y - fA * point.x;
    
    return fA * fX + fB;
}
