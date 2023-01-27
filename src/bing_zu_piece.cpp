#include "bing_zu_piece.h"
#include "board.h"
#include "algorithms.h"

bool BingZuPiece::isBasicMove(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y) const
{
    if(x < 1 || x > 9 || y < 1 || y > 10)
        return false;
    if(Algorithms::pieceSideCheck(context, x, y, side())){
        // never eat our own army
        return false;
    }
    if(side() == Board::getBoard()->side() && (y<this->y)){
        // never go back
        return false;
    }else if(side() != Board::getBoard()->side() && (y>this->y)){
        // never go back
        return false;
    }
    if((side() == Board::getBoard()->side()) ^ (y<=5)){
        // has passes the river
        return std::abs(x - this->x) + std::abs(y - this->y) == 1;
    }else{
        return x == this->x && std::abs(y - this->y) == 1;
    }
    return true;
}

const std::list<Pos> BingZuPiece::getPossibleMoves(const std::map<Pos, std::shared_ptr<Piece>> &context) const
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

BingZuPiece::BingZuPiece(int x, int y, bool side)
    : Piece(x, y, setSide(PieceType::BING_ZU, side))
{

}
