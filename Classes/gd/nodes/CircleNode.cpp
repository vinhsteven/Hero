
#include "package.h"

USING_NS_CC;

CircleNode::CircleNode()
: m_fRadius(0)
, m_dwSegmentCount(0)
{
    
}

bool CircleNode::init(float fRadius, unsigned int dwSegmentCount)
{
    if (ShapeNode::init())
    {
        m_fRadius        = fRadius;
        m_dwSegmentCount = dwSegmentCount;
        
        // Sets content size
        setContentSize(CCSizeMake(fRadius * 2.0f, fRadius * 2.0f));
        
        return true;
    }
    
    return false;
}

GD_IMPLEMENT_CREATE_2_ARGS(CircleNode, float, fRadius, unsigned int, dwSegmentCount);

void CircleNode::draw()
{
    CC_NODE_DRAW_SETUP();
    
    ccDrawColor4F(m_sColor.r, m_sColor.g, m_sColor.b, m_sColor.a);
    
    ccDrawCircle(CCPointZero, m_fRadius, 360.0f, m_dwSegmentCount, false);
}

bool CircleNode::containsPoint(const CCPoint &point) const
{
    return (point.x * point.x + point.y * point.y <= m_fRadius * m_fRadius);
}
