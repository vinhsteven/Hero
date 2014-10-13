
#ifndef _GD_NODES_SHAPE_NODE_H_
#define _GD_NODES_SHAPE_NODE_H_

USING_NS_CC;

class ShapeNode : public CCNode
{
public:
    
    /** The default constructor */
    ShapeNode();
    
    /** Initializes node */
    virtual bool init();
    
    /** Gets color */
    virtual const ccColor4F& getColor() const { return m_sColor; }
    
    /** Sets color */
    virtual void setColor(const ccColor4F &sColor) { m_sColor = sColor; }
    
    /** Reverses color */
    virtual void reverseColor();
    
    /** Moves by a delta position */
    virtual void moveBy(const CCPoint &deltaPos);
    
    /** Contains the given point? */
    virtual bool containsPoint(const CCPoint &point) const = 0;
    
protected:
    
    // The color
    ccColor4F m_sColor;
};

#endif // _GD_NODES_SHAPE_NODE_H_
