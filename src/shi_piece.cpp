#include "shi_piece.h"
#include "board.h"
#include "algorithms.h"

bool ShiPiece::isBasicMove(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y) const
{
    if(Algorithms::pieceSideCheck(context, x, y, side())){
        // never eat our own army
        return false;
    }
    int offsetX = x - this->x;
    int offsetY = y - this->y;
    if(offsetX*offsetX + offsetY*offsetY != 2)
        return false;
    return 4 <= x && x <= 6 && ((1 <= y && y <= 3) || (8 <= y && y <= 10));
}

const std::list<Pos> ShiPiece::getPossibleMoves(const std::map<Pos, std::shared_ptr<Piece>> &context) const
{
    static Pos allPossibles[] = { Pos(1, 1), Pos(-1, 1), Pos(1, -1), Pos(-1, -1) };
    std::list<Pos> result;
    for (auto onePossible : allPossibles) {
        Pos target(this->x + onePossible.first, this->y + onePossible.second);
        if(isValidMove(context, x, y)){
            result.push_back(target);
        }
    }
    return result;
}

ShiPiece::ShiPiece(int x, int y, bool side)
    : Piece(x, y, setSide(PieceType::SHI, side))
{

}
