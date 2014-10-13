
#include "package.h"

USING_NS_CC;

PathNode::PathNode()
: m_sColor(BLUE_4F)
{
    
}

bool PathNode::init()
{
    if (CCNode::init())
    {
        m_sColor = BLUE_4F;
        
        setShaderProgram(pTheShaderCache->programForKey(kCCShader_PositionTextureColor));
        
        return true;
    }
    
    return false;
}

void PathNode::reverseColor()
{
    m_sColor = getReverseColor4F(m_sColor);
}

void PathNode::moveBy(const CCPoint &deltaPos)
{
    setPosition(m_obPosition + deltaPos);
}
