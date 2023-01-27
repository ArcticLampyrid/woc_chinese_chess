#include "algorithms.h"
#include "board.h"

//判断僵局(无子可走)
bool Algorithms::isStalemate(bool side) {
    auto context = Board::getBoard()->pieces;
    for (const auto& [pos, piece] : context) {
        if (piece->side() != side)
            continue;
        if (!piece->getPossibleMoves(context).empty())
            return false;
    }
    return true;
}

bool Algorithms::noThreat(const std::map<Pos, std::shared_ptr<Piece>> &context, Pos from, Pos to, bool side) {
    std::map<Pos, std::shared_ptr<Piece>> copiedContext = context;
    const auto& piece = copiedContext.at(from);
    copiedContext.insert_or_assign(to, piece);
    copiedContext.erase(from);
    auto jiangType = setSide(Piece::PieceType::JIANG_SHUAI, side);
    Pos jiangPos;
    for (const auto& [pos, piece] : copiedContext)
    {
        if (piece->type == jiangType){
            jiangPos = pos;
            break;
        }
    }
    for (const auto& [pos, piece] : copiedContext)
    {
        if (piece->isBasicMove(copiedContext, jiangPos.first, jiangPos.second))
            return false;
    }
    return true;
}

bool Algorithms::containsPiece(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y){
    return context.count(std::make_pair(x, y));
}

bool Algorithms::pieceSideCheck(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y, bool expectedSide){
    auto value = context.find(std::make_pair(x, y));
    if (value == context.end())
        return false;
    return value->second->side() == expectedSide;
}

bool Algorithms::pieceTypeCheck(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y, Piece::PieceType expectedType){
    auto value = context.find(std::make_pair(x, y));
    if (value == context.end())
        return false;
    return value->second->type == expectedType;
}
