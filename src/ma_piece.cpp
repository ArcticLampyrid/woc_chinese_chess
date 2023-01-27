#include "ma_piece.h"
#include "board.h"
#include "algorithms.h"

bool MaPiece::isBasicMove(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y) const
{
    if(x < 1 || x > 9 || y < 1 || y > 10)
        return false;
    if(Algorithms::pieceSideCheck(context, x, y, side())){
        // never eat our own army
        return false;
    }
    int offsetX = x - this->x;
    int offsetY = y - this->y;
    if(offsetX*offsetX + offsetY*offsetY != 5)
        return false;
    return !Algorithms::containsPiece(context, this->x + offsetX/2, this->y + offsetY/2);
}

const std::list<Pos> MaPiece::getPossibleMoves(const std::map<Pos, std::shared_ptr<Piece>> &context) const
{
    static Pos allPossibles[] = {
        Pos(1, 2), Pos(-1, 2), Pos(1, -2), Pos(-1, -2),
        Pos(2, 1), Pos(2, -1), Pos(-2, 1), Pos(-2, -1)
    };
    std::list<Pos> result;
    for (auto onePossible : allPossibles) {
        Pos target(this->x + onePossible.first, this->y + onePossible.second);
        if(isValidMove(context, x, y)){
            result.push_back(target);
        }
    }
    return result;
}

MaPiece::MaPiece(int x, int y, bool side)
    : Piece(x, y, setSide(PieceType::MA, side))
{

}
