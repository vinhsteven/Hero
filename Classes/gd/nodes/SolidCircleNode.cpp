
#include "package.h"

USING_NS_CC;

SolidCircleNode::SolidCircleNode()
: m_fRadius(0)
, m_sColor(BLUE_4F)
{
    
}

bool SolidCircleNode::init(float fRadius, const ccColor4F &sColor)
{
    if (CCDrawNode::init())
    {
        m_fRadius = fRadius;
        m_sColor = sColor;
        
        // Sets content size
        setContentSize(CCSizeMake(fRadius * 2.0f, fRadius * 2.0f));
        
        //
        drawDot(CCPointZero, fRadius, sColor);
        
        return true;
    }
    
    return false;
}

GD_IMPLEMENT_CREATE_2_ARGS(SolidCircleNode, float, fRadius, const ccColor4F&, sColor);

void SolidCircleNode::setColor(const ccColor4F &sColor)
{
    m_sColor = sColor;
    
    clear();
    
    drawDot(CCPointZero, m_fRadius, m_sColor);
}

void SolidCircleNode::reverseColor()
{
    m_sColor = getReverseColor4F(m_sColor);
    
    clear();
    
    drawDot(CCPointZero, m_fRadius, m_sColor);
}

void SolidCircleNode::moveBy(const CCPoint &deltaPos)
{
    setPosition(m_obPosition + deltaPos);
}

bool SolidCircleNode::containsPoint(const CCPoint &point) const
{
    return (point.x * point.x + point.y * point.y <= m_fRadius * m_fRadius);
}
