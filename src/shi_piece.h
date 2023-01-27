#ifndef SHIPIECE_H
#define SHIPIECE_H

#include "piece.h"

class ShiPiece : public Piece
{
private:
    virtual bool isBasicMove(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y) const;
public:
    virtual const std::list<Pos> getPossibleMoves(const std::map<Pos, std::shared_ptr<Piece>> &context) const;
    ShiPiece(int x, int y, bool side);
};

#endif // SHIPIECE_H
