#include "piece.h"
#include "algorithms.h"

using Type = Piece::PieceType;

const std::map<Type, char16_t> Piece::dict = {
    { Type::RED_SHUAI, u'帥' },
    { Type::BLACK_JIANG, u'將' },
    { Type::RED_SHI, u'仕' },
    { Type::BLACK_SHI, u'士' },
    { Type::RED_XIANG, u'相' },
    { Type::BLACK_XIANG, u'象' },
    { Type::RED_MA, u'馬' },
    { Type::BLACK_MA, u'馬' },
    { Type::RED_JU, u'車' },
    { Type::BLACK_JU, u'車' },
    { Type::RED_PAO, u'炮' },
    { Type::BLACK_PAO, u'炮' },
    { Type::RED_BING, u'兵' },
    { Type::BLACK_ZU, u'卒' }
};

bool Piece::noThreat(const std::map<Pos, std::shared_ptr<Piece>> &context, int x, int y) const
{
    return Algorithms::noThreat(context, std::make_pair(this->x, this->y), std::make_pair(x, y), this->side());
}
