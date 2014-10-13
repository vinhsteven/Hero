
#include "package.h"

USING_NS_CC;

RectangleNode::RectangleNode()
: m_bSolid(false)
{
    
}

bool RectangleNode::init(bool bSolid)
{
    if (ShapeNode::init())
    {
        m_bSolid = bSolid;
        
        return true;
    }
    
    return false;
}

GD_IMPLEMENT_CREATE_1_ARG(RectangleNode, bool, bSolid);

void RectangleNode::draw()
{
    CC_NODE_DRAW_SETUP();
    
    if (m_bSolid)
    {
        ccDrawSolidRect(CCPointZero, m_obContentSize, m_sColor);
    }
    else
    {
        ccDrawColor4F(m_sColor.r, m_sColor.g, m_sColor.b, m_sColor.a);
        
        ccDrawRect(CCPointZero, m_obContentSize);
    }
}

bool RectangleNode::containsPoint(const CCPoint &point) const
{
    return (point.x >= 0 &&
            point.y >= 0 &&
            point.x <= m_obContentSize.width &&
            point.y <= m_obContentSize.height);
}
