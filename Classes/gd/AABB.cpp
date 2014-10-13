
#include "gd.h"

AABB::AABB()
: fLeft(0)
, fTop(0)
, fRight(0)
, fBottom(0)
{
    
}

AABB::AABB(float fLeft_, float fTop_, float fRight_, float fBottom_)
{
    fLeft   = fLeft_;
    fTop    = fTop_;
    fRight  = fRight_;
    fBottom = fBottom_;
}

AABB::AABB(const CCPoint &origin, const AABB &aabb)
{
    fLeft   = origin.x + aabb.fLeft;
    fTop    = origin.y + aabb.fTop;
    fRight  = origin.x + aabb.fRight;
    fBottom = origin.y + aabb.fBottom;
}

AABB::AABB(/*const*/ CCNode &node)
{
    CCPoint origin = node.getPosition() - node.getAnchorPointInPoints();
    CCSize  size   = node.getContentSize();
    
    fLeft   = origin.x;
    fRight  = fLeft + size.width;
    fBottom = origin.y;
    fTop    = fBottom + size.height;
}

void AABB::construct(float fLeft, float fTop, float fRight, float fBottom)
{
    this->fLeft   = fLeft;
    this->fTop    = fTop;
    this->fRight  = fRight;
    this->fBottom = fBottom;
}

CCSize AABB::getSize() const
{
    return CCSizeMake(fRight - fLeft, fTop - fBottom);
}

CCPoint AABB::getBottomLeft() const
{
    return CCPointMake(fLeft, fBottom);
}

CCPoint AABB::getBottomCenter() const
{
    return CCPointMake((fLeft + fRight) * 0.5f, fBottom);
}
