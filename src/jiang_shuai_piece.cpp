#include "jiang_shuai_piece.h"
#include "board.h"
#include "algorithms.h"

bool JiangShuaiPiece::isBasicMove(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y) const
{
    if(Algorithms::pieceSideCheck(context, x, y, side()))
    {
        // never eat our own army
        return false;
    }
    if(x == this->x && Algorithms::pieceTypeCheck(context, x, y, setSide(PieceType::JIANG_SHUAI, !this->side())))
    {
        // two commander can kill each other
        int lowerY = std::min(this->y, y);
        int upperY = std::max(this->y, y);
        return Algorithms::countPiecesIf(context, [&](const Pos pos) -> bool {
            return pos.first == x && lowerY < pos.second && pos.second < upperY;
        }) == 0;
    }
    if(std::abs(x - this->x) + std::abs(y - this->y) != 1)
        return false;
    return 4 <= x && x <= 6 && ((1 <= y && y <= 3) || (8 <= y && y <= 10));
}

const std::list<Pos> JiangShuaiPiece::getPossibleMoves(const std::map<Pos, std::shared_ptr<Piece>> &context) const
{
    static Pos allPossibles[] = { Pos(1, 0), Pos(-1, 0), Pos(0, 1), Pos(0, -1) };
    std::list<Pos> result;
    for (auto onePossible : allPossibles) {
        Pos target(this->x + onePossible.first, this->y + onePossible.second);
        if(isValidMove(context, x, y)){
            result.push_back(target);
        }
    }
    return result;
}

JiangShuaiPiece::JiangShuaiPiece(int x, int y, bool side)
    : Piece(x, y, setSide(PieceType::JIANG_SHUAI, side))
{

}
