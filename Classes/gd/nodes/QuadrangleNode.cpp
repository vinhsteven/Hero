
#include "package.h"

USING_NS_CC;

QuadrangleNode::QuadrangleNode()
: m_bSolid(false)
{
    m_vertices[0] =
    m_vertices[1] =
    m_vertices[2] =
    m_vertices[3] = CCPointZero;
}

bool QuadrangleNode::init(const CCPoint *vertices, bool bSolid)
{
    if (ShapeNode::init())
    {
        m_vertices[0] = vertices[0];
        m_vertices[1] = vertices[1];
        m_vertices[2] = vertices[2];
        m_vertices[3] = vertices[3];
        
        m_bSolid = bSolid;
        
        return true;
    }
    
    return false;
}

GD_IMPLEMENT_CREATE_2_ARGS(QuadrangleNode, const CCPoint*, vertices, bool, bSolid);

void QuadrangleNode::setVertices(const CCPoint *vertices)
{
    m_vertices[0] = vertices[0];
    m_vertices[1] = vertices[1];
    m_vertices[2] = vertices[2];
    m_vertices[3] = vertices[3];
}

bool QuadrangleNode::containsPoint(const CCPoint &point) const
{
    //TODO
    return false;
}

void QuadrangleNode::draw()
{
    CC_NODE_DRAW_SETUP();
    
    if (m_bSolid)
    {
        ccDrawSolidPoly(m_vertices, 4, m_sColor);
    }
    else
    {
        ccDrawColor4F(m_sColor.r, m_sColor.g, m_sColor.b, m_sColor.a);
        
        ccDrawPoly(m_vertices, 4, true);
    }
}
