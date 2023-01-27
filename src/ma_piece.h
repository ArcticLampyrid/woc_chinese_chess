#ifndef MAPIECE_H
#define MAPIECE_H

#include "piece.h"

class MaPiece : public Piece
{
private:
    virtual bool isBasicMove(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y) const;
public:
    virtual const std::list<Pos> getPossibleMoves(const std::map<Pos, std::shared_ptr<Piece>> &context) const;
    MaPiece(int x, int y, bool side);
};

#endif // MAPIECE_H
