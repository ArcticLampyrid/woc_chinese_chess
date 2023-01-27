#ifndef BINGZUPIECE_H
#define BINGZUPIECE_H

#include "piece.h"

class BingZuPiece : public Piece
{
private:
    virtual bool isBasicMove(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y) const;
public:
    virtual const std::list<Pos> getPossibleMoves(const std::map<Pos, std::shared_ptr<Piece>> &context) const;
    BingZuPiece(int x, int y, bool side);
};

#endif // BINGZUPIECE_H
