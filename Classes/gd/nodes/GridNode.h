
#ifndef _GD_NODES_GRID_NODE_H_
#define _GD_NODES_GRID_NODE_H_

USING_NS_CC;

class GridNode : public CCDrawNode
{
public:
    
    GridNode();
    
    virtual bool init();
    
    static GridNode* create();
    
    /** Constructs the grid node object */
    virtual void construct(int nGridWidth, int nGridHeight, float fCellWidth, float fCellHeight,
                           const ccColor4F &sColor = BLUE_4F);
    
    /** Sets color */
    virtual void setColor(const ccColor4F &sColor);
};

#endif // _GD_NODES_GRID_NODE_H_
