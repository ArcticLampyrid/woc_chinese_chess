#ifndef JIANGSHUAIPIECE_H
#define JIANGSHUAIPIECE_H

#include "piece.h"

class JiangShuaiPiece : public Piece
{
private:
    bool noThreat(int x, int y) const;
    virtual bool isBasicMove(int x, int y) const;
public:
    virtual bool isValidMove(int x, int y) const;
    virtual const std::list<Pos> getPossibleMoves() const;
    JiangShuaiPiece(int x, int y, bool side);
};

#endif // JIANGSHUAIPIECE_H
