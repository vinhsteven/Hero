
#ifndef _GD_NODES_LINE_NODE_H_
#define _GD_NODES_LINE_NODE_H_

USING_NS_CC;

class LineNode : public PathNode
{
public:
    
    /** The default constructor */
    LineNode();
    
    /** Initializes node */
    virtual bool init(const CCPoint &startPos, const CCPoint &endPos);
    
    static LineNode* create(const CCPoint &startPos, const CCPoint &endPos);
    
    /** Gets start position */
    virtual const CCPoint& getStartPosition() const { return m_startPos; }
    
    /** Sets start position */
    virtual void setStartPosition(const CCPoint &startPos) { m_startPos = startPos; }
    
    /** Gets end position */
    virtual const CCPoint& getEndPosition() const { return m_endPos; }
    
    /** Sets end position */
    virtual void setEndPosition(const CCPoint &endPos) { m_endPos = endPos; }
    
    /** Draws node */
    virtual void draw();
    
protected:
    
    // The start position
    CCPoint m_startPos;
    
    // The end position
    CCPoint m_endPos;
};

#endif // _GD_NODES_LINE_NODE_H_
