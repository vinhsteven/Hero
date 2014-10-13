
#include "package.h"

#define RADIUS  0.5f

USING_NS_CC;

GridNode::GridNode()
{
    
}

bool GridNode::init()
{
    if (CCDrawNode::init())
    {
        return true;
    }
    
    return false;
}

GD_IMPLEMENT_CREATE(GridNode);

void GridNode::construct(int nGridWidth, int nGridHeight, float fCellWidth, float fCellHeight,
                         const ccColor4F &sColor)
{
    // Clears this node
    clear();
    
    //
    float fWidth  = fCellWidth  * nGridWidth;
    float fHeight = fCellHeight * nGridHeight;
    
    int i, j;
    float fX, fY;
    
    // Draws horizontal lines
    fX = 0.0f;
    fY = 0.0f;
    
    for (i = 0; i <= nGridHeight; i++)
    {
        drawSegment(ccp(fX, fY), ccp(fWidth, fY), RADIUS, sColor);
        
        fY += fCellHeight;
    }
    
    // Draws vertical lines
    fX = 0.0f;
    fY = 0.0f;
    
    for (j = 0; j <= nGridWidth; j++)
    {
        drawSegment(ccp(fX, fY), ccp(fX, fHeight), RADIUS, sColor);
        
        fX += fCellWidth;
    }
    
    // Sets content size
    setContentSize(CCSizeMake(fWidth, fHeight));
}

void GridNode::setColor(const ccColor4F &sColor)
{
    ccColor4B color = ccc4BFromccc4F(sColor);
    
    for (int i = 0; i < m_nBufferCount; i++)
    {
        m_pBuffer[i].colors = color;
    }
    
    // Sets dirty
    m_bDirty = true;
}
