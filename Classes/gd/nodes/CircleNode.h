
#ifndef _GD_NODES_CIRCLE_NODE_H_
#define _GD_NODES_CIRCLE_NODE_H_

USING_NS_CC;

class CircleNode : public ShapeNode
{
public:
    
    /** The default constructor */
    CircleNode();
    
    /** Initializes node */
    virtual bool init(float fRadius, unsigned int dwSegmentCount);
    
    static CircleNode* create(float fRadius, unsigned int dwSegmentCount);
    
    /** Contains the given point? */
    virtual bool containsPoint(const CCPoint &point) const;
    
    /** Draws node */
    virtual void draw();
    
protected:
    
    // The radius
    float m_fRadius;
    
    // The number of segments
    unsigned int m_dwSegmentCount;
};

#endif // _GD_NODES_CIRCLE_NODE_H_
