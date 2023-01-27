#include "ju_piece.h"
#include "board.h"
#include "algorithms.h"

bool JuPiece::isBasicMove(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y) const
{
    if(x < 1 || x > 9 || y < 1 || y > 10)
        return false;
    if(Algorithms::pieceSideCheck(context, x, y, side())){
        // never eat our own army
        return false;
    }
    if(x == this->x)
    {
        int lowerY = std::min(this->y, y);
        int upperY = std::max(this->y, y);
        return Algorithms::countPiecesIf(context, [&](const Pos pos) -> bool {
            return pos.first == x && lowerY < pos.second && pos.second < upperY;
        }) == 0;
    }
    else if(y == this->y)
    {
        int lowerX = std::min(this->x, x);
        int upperX = std::max(this->x, x);
        return Algorithms::countPiecesIf(context, [&](const Pos pos) -> bool {
            return pos.second == y && lowerX < pos.first && pos.first < upperX;
        }) == 0;
    }
    else return false;
}

const std::list<Pos> JuPiece::getPossibleMoves(const std::map<Pos, std::shared_ptr<Piece>> &context) const
{
    std::list<Pos> result;
    // 暴力十字线型尝试
    // TODO improve performance
    {
        const int x = this->x;
        for(int y = 1; y < this->y; y++)
        {
            if(isValidMove(context, x, y)){
                result.push_back(std::make_pair(x, y));
            }
        }
        for(int y = this->y + 1; y <= 10; y++)
        {
            if(isValidMove(context, x, y)){
                result.push_back(std::make_pair(x, y));
            }
        }
    }
    {
        const int y = this->y;
        for(int x = 1; x < this->x; x++)
        {
            if(isValidMove(context, x, y)){
                result.push_back(std::make_pair(x, y));
            }
        }
        for(int x = this->x + 1; x <= 9; x++)
        {
            if(isValidMove(context, x, y)){
                result.push_back(std::make_pair(x, y));
            }
        }
    }
    return result;
}

JuPiece::JuPiece(int x, int y, bool side)
    : Piece(x, y, setSide(PieceType::JU, side))
{

}
