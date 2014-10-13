
#include "package.h"

USING_NS_CC;

ShapeNode::ShapeNode()
: m_sColor(BLUE_4F)
{
    
}

bool ShapeNode::init()
{
    if (CCNode::init())
    {
        m_sColor = BLUE_4F;
        
        setShaderProgram(pTheShaderCache->programForKey(kCCShader_PositionTextureColor));
        
        return true;
    }
    
    return false;
}

void ShapeNode::reverseColor()
{
    m_sColor = getReverseColor4F(m_sColor);
}

void ShapeNode::moveBy(const CCPoint &deltaPos)
{
    setPosition(m_obPosition + deltaPos);
}
