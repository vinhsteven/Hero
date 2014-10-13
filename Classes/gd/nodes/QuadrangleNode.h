
#ifndef _GD_NODES_QUADRANGLE_NODE_H_
#define _GD_NODES_QUADRANGLE_NODE_H_

USING_NS_CC;

class QuadrangleNode : public ShapeNode
{
public:
    
    /** The default constructor */
    QuadrangleNode();
    
    /** Initializes node */
    virtual bool init(const CCPoint *vertices, bool bSolid);
    
    static QuadrangleNode* create(const CCPoint *vertices, bool bSolid = false);
    
    /** Sets vertices */
    virtual void setVertices(const CCPoint *vertices);
    
    /** Is solid? */
    virtual bool isSolid() const { return m_bSolid; }
    
    /** Sets solid or not */
    virtual void setSolid(bool bSolid) { m_bSolid = bSolid; }
    
    /** Contains the given point? */
    virtual bool containsPoint(const CCPoint &point) const;
    
    /** Draws node */
    virtual void draw();
    
protected:
    
    // The vertices
    CCPoint m_vertices[4];
    
    // Is solid?
    bool m_bSolid;
};

#endif // _GD_NODES_QUADRANGLE_NODE_H_
