
#ifndef _GD_NODES_SOLID_CIRCLE_NODE_H_
#define _GD_NODES_SOLID_CIRCLE_NODE_H_

USING_NS_CC;

class SolidCircleNode : public CCDrawNode
{
public:
    
    SolidCircleNode();
    
    virtual bool init(float fRadius, const ccColor4F &sColor);
    
    static SolidCircleNode* create(float fRadius, const ccColor4F &sColor);
    
    /** Gets color */
    virtual const ccColor4F& getColor() const { return m_sColor; }
    
    /** Sets color */
    virtual void setColor(const ccColor4F &sColor);
    
    /** Reverses color */
    virtual void reverseColor();
    
    /** Moves by a delta position */
    virtual void moveBy(const CCPoint &deltaPos);
    
    /** Contains the given point? */
    virtual bool containsPoint(const CCPoint &point) const;
    
protected:
    
    // The radius
    float m_fRadius;
    
    // The color
    ccColor4F m_sColor;
};

#endif // _GD_NODES_SOLID_CIRCLE_NODE_H_
