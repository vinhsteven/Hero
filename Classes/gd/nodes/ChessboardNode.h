
#ifndef _GD_NODES_CHESSBOARD_NODE_H_
#define _GD_NODES_CHESSBOARD_NODE_H_

USING_NS_CC;

class ChessboardNode : public CCDrawNode
{
public:
    
    ChessboardNode();
    
    virtual bool init();
    
    static ChessboardNode* create();
    
    /** Constructs the chessboard node object */
    virtual void construct(int nGridWidth, int nGridHeight, float fCellSide,
                           const ccColor4F &sBackgroundColor = WHITE_4F,
                           const ccColor4F &sForegroundColor = BLACK_4F,
                           const ccColor4F &sBorderColor     = GRAY_4F);
};

#endif // _GD_NODES_CHESSBOARD_NODE_H_
