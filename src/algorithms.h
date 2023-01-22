#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "board.h"

//工具类
class Algorithms {
public:
    //判断僵局(无子可走)
    static bool isStalemate(bool side) {
        auto result = Board::getBoard()->find(-1, -1, side);

        for (const auto& [pos, type] : result) {
            auto piece = Board::getBoard()->pieces.at(pos);
            if (!piece->getPossibleMoves().empty())
                return false;
        }

        return true;
    }

    static bool isCheck(bool side) {
        //Add your own code below
        //////////////////////////


        //////////////////////////
        return false;
    }
};

#endif // ALGORITHMS_H
