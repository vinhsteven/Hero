
#include "package.h"

USING_NS_CC;

LineNode::LineNode()
: m_startPos(CCPointZero)
, m_endPos(CCPointZero)
{
    
}

bool LineNode::init(const CCPoint &startPos, const CCPoint &endPos)
{
    if (PathNode::init())
    {
        m_startPos   = startPos;
        m_endPos     = endPos;
        
        return true;
    }
    
    return false;
}

GD_IMPLEMENT_CREATE_2_ARGS(LineNode, const CCPoint&, startPos, const CCPoint&, endPos);

void LineNode::draw()
{
    CC_NODE_DRAW_SETUP();
    
    ccDrawColor4F(m_sColor.r, m_sColor.g, m_sColor.b, m_sColor.a);
    
    ccDrawLine(m_startPos, m_endPos);
}
