#ifndef PAOPIECE_H
#define PAOPIECE_H

#include "piece.h"

class PaoPiece : public Piece
{
private:
    virtual bool isBasicMove(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y) const;
public:
    virtual const std::list<Pos> getPossibleMoves(const std::map<Pos, std::shared_ptr<Piece>> &context) const;
    PaoPiece(int x, int y, bool side);
};

#endif // PAOPIECE_H
