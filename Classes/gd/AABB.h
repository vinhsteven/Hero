
#ifndef _GD_AABB_H_
#define _GD_AABB_H_

USING_NS_CC;

class AABB
{
public:
    
    /** The default constructor */
    AABB();
    
    /** The constructor */
    AABB(float fLeft, float fTop, float fRight, float fBottom);
    
    /** The constructor */
    AABB(const CCPoint &origin, const AABB &aabb);
    
    /** The constructor */
    AABB(/*const*/ CCNode &node);
    
    /** Constructs the AABB object */
    void construct(float fLeft, float fTop, float fRight, float fBottom);
    
    /** Gets size */
    CCSize getSize() const;
    
    /** Gets bottom-left position */
    CCPoint getBottomLeft() const;
    
    /** Gets bottom-center position */
    CCPoint getBottomCenter() const;
    
public:
    
    // The left
    float fLeft;
    
    // The top
    float fTop;
    
    // The right
    float fRight;
    
    // The bottom
    float fBottom;
};

#endif // _GD_AABB_H_
