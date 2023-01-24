#include "jiang_shuai_piece.h"

bool JiangShuaiPiece::isBasicMove(int x, int y) const
{
    if(std::abs(x - this->x) + std::abs(y - this->y) != 1)
        return false;
    return 4 <= x && x <= 6 && ((1 <= y && y <= 3) || (10 <= y && y <= 12));
}

bool JiangShuaiPiece::isValidMove(int x, int y) const
{
    return isBasicMove(x, y);
}

const std::list<Pos> JiangShuaiPiece::getPossibleMoves() const
{
    static Pos allPossibles[] = { Pos(1, 0), Pos(-1, 0), Pos(0, 1), Pos(0, -1) };
    std::list<Pos> result;
    for (auto onePossible : allPossibles) {
        Pos target(this->x + onePossible.first, this->y + onePossible.second);
        if(isValidMove(x, y)){
            result.push_back(target);
        }
    }
    return result;
}

JiangShuaiPiece::JiangShuaiPiece(int x, int y, bool side)
    : Piece(x, y, setSide(PieceType::JIANG_SHUAI, side))
{

}
