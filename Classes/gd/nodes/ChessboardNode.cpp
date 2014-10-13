
#include "package.h"

#define FIX_BORDER

#define RADIUS  0.5f

ChessboardNode::ChessboardNode()
{
    
}

bool ChessboardNode::init()
{
    if (CCDrawNode::init())
    {
        return true;
    }
    
    return false;
}

GD_IMPLEMENT_CREATE(ChessboardNode);

void ChessboardNode::construct(int nGridWidth, int nGridHeight, float fCellSide,
                               const ccColor4F &sBackgroundColor, const ccColor4F &sForegroundColor, const ccColor4F &sBorderColor)
{
#define fCellWidth  fCellSide
#define fCellHeight fCellSide
    
    // Clears this node
    clear();
    
    //
    float fWidth  = fCellWidth  * nGridWidth;
    float fHeight = fCellHeight * nGridHeight;
    
    int i, j, j0 = 1;
    float fX = 0.0f;
    float fY = 0.0f;
    CCPoint vertices[4];
    
#ifdef FIX_BORDER
    fX += 0.5f;
    fY += 0.5f;
    fWidth  -= 1.0f;
    fHeight -= 1.0f;
#endif
    
    // Fills background
    vertices[0] = ccp(fX, fY);
    vertices[1] = ccp(fX + fWidth, fY);
    vertices[2] = ccp(fX + fWidth, fY + fHeight);
    vertices[3] = ccp(fX, fY + fHeight);
    
    drawPolygon(vertices, 4, sBackgroundColor, 0.0f, sBackgroundColor);
    
#ifdef FIX_BORDER
    fX -= 0.5f;
    fY -= 0.5f;
    fWidth  += 1.0f;
    fHeight += 1.0f;
#endif
    
    // Fills foreground
    fY = fCellHeight * (nGridHeight - 1);
    
    for (i = 0; i < nGridHeight; i++)
    {
        fX = j0 * fCellWidth;
        
        for (j = j0; j < nGridWidth; j += 2)
        {
#ifdef FIX_BORDER
            fX += 0.5f;
            fY += 0.5f;
            fCellSide -= 1.0f;
#endif
            
            vertices[0] = ccp(fX, fY);
            vertices[1] = ccp(fX + fCellWidth, fY);
            vertices[2] = ccp(fX + fCellWidth, fY + fCellHeight);
            vertices[3] = ccp(fX, fY + fCellHeight);
            
            drawPolygon(vertices, 4, sForegroundColor, 0.0f, sForegroundColor);
            
#ifdef FIX_BORDER
            fX -= 0.5f;
            fY -= 0.5f;
            fCellSide += 1.0f;
#endif
            
            fX += fCellWidth * 2.0f;
        }
        
        fY -= fCellHeight;
        
        j0 = 1 - j0;
    }
    
    // Draws border
    CCPoint bottomLeft  = ccp(0.0f, 0.0f);
    CCPoint bottomRight = ccp(fWidth, 0.0f);
    CCPoint topRight    = ccp(fWidth, fHeight);
    CCPoint topLeft     = ccp(0.0f, fHeight);
    
    drawSegment(bottomLeft, bottomRight, RADIUS, sBorderColor);
    drawSegment(bottomRight, topRight, RADIUS, sBorderColor);
    drawSegment(topRight, topLeft, RADIUS, sBorderColor);
    drawSegment(topLeft, bottomLeft, RADIUS, sBorderColor);
    
    // Sets content size
    setContentSize(CCSizeMake(fWidth, fHeight));
}
