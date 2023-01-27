#ifndef XIANGPIECE_H
#define XIANGPIECE_H

#include "piece.h"

class XiangPiece : public Piece
{
private:
    virtual bool isBasicMove(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y) const;
public:
    virtual const std::list<Pos> getPossibleMoves(const std::map<Pos, std::shared_ptr<Piece>> &context) const;
    XiangPiece(int x, int y, bool side);
};

#endif // XIANGPIECE_H
