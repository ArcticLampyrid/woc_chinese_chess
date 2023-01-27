#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "piece.h"

//工具类
class Algorithms {
public:
    //判断僵局(无子可走)
    static bool isStalemate(bool side);
    static bool noThreat(const std::map<Pos, std::shared_ptr<Piece>> &context, Pos from, Pos to, bool side);
    static bool containsPiece(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y);
    static bool pieceSideCheck(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y, bool expectedSide);
    static bool pieceTypeCheck(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y, Piece::PieceType expectedType);

    template<typename TPosFilter, std::enable_if_t<std::is_invocable_v<TPosFilter, const Pos>, int> = 0>
    static int countPiecesIf(const std::map<Pos, std::shared_ptr<Piece>> &context, TPosFilter posFilter){
        int count = 0;
        for (const auto& [pos, piece] : context) {
            if (posFilter(pos))
                count++;
        }
        return count;
    }
};
#endif // ALGORITHMS_H
