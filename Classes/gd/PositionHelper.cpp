
#include "gd.h"

bool setPositionByAttach(CCNode &node, const CCPoint &origin, const CCSize &size, int nAttach)
{
    float fX = 0;
    float fY = 0;
    
    // Top
    if (nAttach == kAttachTopLeft)
    {
        const CCSize  &contentSize = node.getContentSize();
        const CCPoint &anchorPointInPoints = node.getAnchorPointInPoints();
        
        fX = getLeftAttach(origin, size, anchorPointInPoints);
        fY = getTopAttach(origin, size, contentSize, anchorPointInPoints);
    }
    else if (nAttach == kAttachTopCenter)
    {
        const CCSize  &contentSize = node.getContentSize();
        const CCPoint &anchorPointInPoints = node.getAnchorPointInPoints();
        
        fX = getCenterAttach(origin, size);
        fY = getTopAttach(origin, size, contentSize, anchorPointInPoints);
    }
    else if (nAttach == kAttachTopRight)
    {
        const CCSize  &contentSize = node.getContentSize();
        const CCPoint &anchorPointInPoints = node.getAnchorPointInPoints();
        
        fX = getRightAttach(origin, size, contentSize, anchorPointInPoints);
        fY = getTopAttach(origin, size, contentSize, anchorPointInPoints);
    }
    
    // Middle
    else if (nAttach == kAttachMiddleLeft)
    {
        const CCPoint &anchorPointInPoints = node.getAnchorPointInPoints();
        
        fX = getLeftAttach(origin, size, anchorPointInPoints);
        fY = getMiddleAttach(origin, size);
    }
    else if (nAttach == kAttachCenter)
    {
        fX = getCenterAttach(origin, size);
        fY = getMiddleAttach(origin, size);
    }
    else if (nAttach == kAttachMiddleRight)
    {
        const CCSize  &contentSize = node.getContentSize();
        const CCPoint &anchorPointInPoints = node.getAnchorPointInPoints();
        
        fX = getRightAttach(origin, size, contentSize, anchorPointInPoints);
        fY = getMiddleAttach(origin, size);
    }
    
    // Bottom
    else if (nAttach == kAttachBottomLeft)
    {
        const CCPoint &anchorPointInPoints = node.getAnchorPointInPoints();
        
        fX = getLeftAttach(origin, size, anchorPointInPoints);
        fY = getBottomAttach(origin, size, anchorPointInPoints);
    }
    else if (nAttach == kAttachBottomCenter)
    {
        const CCPoint &anchorPointInPoints = node.getAnchorPointInPoints();
        
        fX = getCenterAttach(origin, size);
        fY = getBottomAttach(origin, size, anchorPointInPoints);
    }
    else if (nAttach == kAttachBottomRight)
    {
        const CCSize  &contentSize = node.getContentSize();
        const CCPoint &anchorPointInPoints = node.getAnchorPointInPoints();
        
        fX = getRightAttach(origin, size, contentSize, anchorPointInPoints);
        fY = getBottomAttach(origin, size, anchorPointInPoints);
    }
    
    // Not supported
    else
    {
        GD_NOT_SUPPORTED("E000111333");
        
        return false;
    }
    
    node.setPosition(fX, fY);
    
    return true;
}
