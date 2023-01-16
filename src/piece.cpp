#include "piece.h"

using Type = Piece::PieceType;

const std::map<Type, wchar_t> Piece::dict = {
    { Type::RED_SHUAI, L'帥' },
    { Type::BLACK_JIANG, L'將' },
    { Type::RED_SHI, L'仕' },
    { Type::BLACK_SHI, L'士' },
    { Type::RED_XIANG, L'相' },
    { Type::BLACK_XIANG, L'象' },
    { Type::RED_MA, L'馬' },
    { Type::BLACK_MA, L'馬' },
    { Type::RED_JU, L'車' },
    { Type::BLACK_JU, L'車' },
    { Type::RED_PAO, L'炮' },
    { Type::BLACK_PAO, L'炮' },
    { Type::RED_BING, L'兵' },
    { Type::BLACK_ZU, L'卒' }
};
