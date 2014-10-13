
#ifndef _GD_NODES_RECTANGLE_NODE_H_
#define _GD_NODES_RECTANGLE_NODE_H_

USING_NS_CC;

class RectangleNode : public ShapeNode
{
public:
    
    /** The default constructor */
    RectangleNode();
    
    /** Initializes node */
    virtual bool init(bool bSolid);
    
    static RectangleNode* create(bool bSolid = false);
    
    /** Is solid? */
    virtual bool isSolid() const { return m_bSolid; }
    
    /** Sets solid or not */
    virtual void setSolid(bool bSolid) { m_bSolid = bSolid; }
    
    /** Contains the given point? */
    virtual bool containsPoint(const CCPoint &point) const;
    
    /** Draws node */
    virtual void draw();
    
protected:
    
    // Is solid?
    bool m_bSolid;
};

#endif // _GD_NODES_RECTANGLE_NODE_H_
