
#ifndef _GD_POSITION_HELPER_H_
#define _GD_POSITION_HELPER_H_

#define getLeftAttach(origin, size, anchorPointInPoints)                (origin.x + anchorPointInPoints.x)
#define getTopAttach(origin, size, contentSize, anchorPointInPoints)    (origin.y + size.height - contentSize.height + anchorPointInPoints.y)
#define getRightAttach(origin, size, contentSize, anchorPointInPoints)  (origin.x + size.width  - contentSize.width  + anchorPointInPoints.x)
#define getBottomAttach(origin, size, anchorPointInPoints)              (origin.y + anchorPointInPoints.y)
#define getCenterAttach(origin, size)                                   (origin.x + size.width  * 0.5f)
#define getMiddleAttach(origin, size)                                   (origin.y + size.height * 0.5f)

#define getReverseAnchorPointInPointsY(pNode)   (pNode->getContentSize().height - pNode->getAnchorPointInPoints().y)

USING_NS_CC;

static const CCPoint AnchorPointCenter(0.5f, 0.5f);
static const CCPoint AnchorPointTopLeft(0.0f, 1.0f);
static const CCPoint AnchorPointTopRight(1.0f, 1.0f);
static const CCPoint AnchorPointBottomLeft(0.0f, 0.0f);
static const CCPoint AnchorPointBottomRight(1.0f, 0.0f);

enum
{
    kAttachTopLeft = 0,
    kAttachTopCenter,
    kAttachTopRight,
    
    kAttachMiddleLeft,
    kAttachCenter,
    kAttachMiddleRight,
    
    kAttachBottomLeft,
    kAttachBottomCenter,
    kAttachBottomRight,
};

/** Sets position by attach */
bool setPositionByAttach(CCNode &node, const CCPoint &origin, const CCSize &size, int nAttach);

#endif // _GD_POSITION_HELPER_H_
