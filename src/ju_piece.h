#ifndef JUPIECE_H
#define JUPIECE_H

#include "piece.h"

class JuPiece : public Piece
{
private:
    virtual bool isBasicMove(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y) const;
public:
    virtual const std::list<Pos> getPossibleMoves(const std::map<Pos, std::shared_ptr<Piece>> &context) const;
    JuPiece(int x, int y, bool side);
};

#endif // JUPIECE_H
