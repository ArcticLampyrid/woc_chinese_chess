#ifndef JIANGSHUAIPIECE_H
#define JIANGSHUAIPIECE_H

#include "piece.h"

class JiangShuaiPiece : public Piece
{
private:
    virtual bool isBasicMove(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y) const;
public:
    virtual const std::list<Pos> getPossibleMoves(const std::map<Pos, std::shared_ptr<Piece>> &context) const;
    JiangShuaiPiece(int x, int y, bool side);
};

#endif // JIANGSHUAIPIECE_H
