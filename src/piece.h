#ifndef PIECE_H
#define PIECE_H

#include <cmath>
#include <list>
#include <map>
#include <memory>

#define RED_SIDE true
#define BLACK_SIDE false

using Pos = std::pair<int, int>;
class Piece;
class Piece {   //请不要继承QObject
public:
    mutable int x, y;
    //正数
    const enum class PieceType {
        NONE = 0,
        JIANG_SHUAI = 1,
        RED_SHUAI   = 1,    BLACK_JIANG     = -1,
        SHI = 2,
        RED_SHI     = 2,    BLACK_SHI       = -2,
        XIANG = 3,
        RED_XIANG   = 3,    BLACK_XIANG     = -3,
        MA = 4,
        RED_MA      = 4,    BLACK_MA        = -4,
        JU = 5,
        RED_JU      = 5,    BLACK_JU        = -5,
        PAO = 6,
        RED_PAO     = 6,    BLACK_PAO       = -6,
        BING_ZU = 7,
        RED_BING    = 7,    BLACK_ZU        = -7
    } type;
private:
    static const std::map<PieceType, char16_t> dict;
public:
    static inline char16_t convert(PieceType type) {
        return dict.at(type);
    }
    inline char16_t text() const {
        return convert(type);
    }
    inline void move(int x, int y) const {  //请勿修改
        this->x = x;
        this->y = y;
    }
    inline bool side() const {
        return type > PieceType::NONE;
    }
    inline const Pos pos() const {
        return std::make_pair(x, y);
    }
private:
    bool noThreat(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y) const;
    virtual bool isBasicMove(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y) const = 0;
public:
    bool isValidMove(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y) const {
        return isBasicMove(context, x, y) && noThreat(context, x, y);
    }
    virtual const std::list<Pos> getPossibleMoves(const std::map<Pos, std::shared_ptr<Piece>> &context) const = 0;

    Piece(int x, int y, PieceType type) : x(x), y(y), type(type) {}
    virtual ~Piece() {} //虚析构
    friend class Algorithms;
};

inline Piece::PieceType removeSide(Piece::PieceType type) {
    return (Piece::PieceType)std::abs((int)type);
}

inline bool getSide(Piece::PieceType type) {
    return type > Piece::PieceType::NONE;
}

inline Piece::PieceType setSide(Piece::PieceType type, bool side) {
    return (Piece::PieceType)(side ? std::abs((int)type) : -std::abs((int)type));
}

#endif // PIECE_H
