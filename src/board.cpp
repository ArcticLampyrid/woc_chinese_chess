#include "board.h"
#include "algorithms.h"

using Type = Piece::PieceType;

Board::Board() {
    //Add your own code below
    //////////////////////////


    //////////////////////////
}

void Board::judgeStatus() {
    checked = Algorithms::isCheck(side());
    if (Algorithms::isStalemate(side()))
        return emit win(side());
    if (Algorithms::isStalemate(!side()))
        return emit win(!side());
    //Add your own code below
    //////////////////////////

    //////////////////////////
}

void Board::onSetup(Cell** cells) {
    for (int i = 0; i < 12 * 9; i++) {
        auto& cell = cells[i];
        this->cells.emplace(std::piecewise_construct, std::tuple(cell->x, cell->y), std::tuple(cell));
    }
    std::map<Type, Constructor> factory = {
        //请将nullptr替换为'new ClassName(x, y, side)'，请正确设置派生类构造函数参数
        { Type::JIANG_SHUAI, [](int x, int y, bool side)->const Piece* { return nullptr; } },
        { Type::SHI, [](int x, int y, bool side)->const Piece* { return nullptr; } },
        { Type::XIANG, [](int x, int y, bool side)->const Piece* { return nullptr; } },
        { Type::MA, [](int x, int y, bool side)->const Piece* { return nullptr; } },
        { Type::JU, [](int x, int y, bool side)->const Piece* { return nullptr; } },
        { Type::PAO, [](int x, int y, bool side)->const Piece* { return nullptr; } },
        { Type::BING_ZU, [](int x, int y, bool side)->const Piece* { return nullptr; } }
    };
    setPieces(factory);
    for (const auto& [pos, piece] : pieces)
        this->cells[pos]->change(piece);
}

void Board::setPieces(const std::map<Type, Constructor> & factory) {
    static std::list<std::pair<Pos, Type>> piece_list = {
        { { 1, 1 }, Type::RED_JU },
        { { 2, 1 }, Type::RED_MA },
        { { 3, 1 }, Type::RED_XIANG },
        { { 4, 1 }, Type::RED_SHI },
        { { 5, 1 }, Type::RED_SHUAI },
        { { 6, 1 }, Type::RED_SHI },
        { { 7, 1 }, Type::RED_XIANG },
        { { 8, 1 }, Type::RED_MA },
        { { 9, 1 }, Type::RED_JU },
        { { 2, 3 }, Type::RED_PAO },
        { { 8, 3 }, Type::RED_PAO },
        { { 1, 5 }, Type::RED_BING },
        { { 3, 5 }, Type::RED_BING },
        { { 5, 5 }, Type::RED_BING },
        { { 7, 5 }, Type::RED_BING },
        { { 9, 5 }, Type::RED_BING },
        { { 1, 12 }, Type::BLACK_JU },
        { { 2, 12 }, Type::BLACK_MA },
        { { 3, 12 }, Type::BLACK_XIANG },
        { { 4, 12 }, Type::BLACK_SHI },
        { { 5, 12 }, Type::BLACK_JIANG },
        { { 6, 12 }, Type::BLACK_SHI },
        { { 7, 12 }, Type::BLACK_XIANG },
        { { 8, 12 }, Type::BLACK_MA },
        { { 9, 12 }, Type::BLACK_JU },
        { { 2, 10 }, Type::BLACK_PAO },
        { { 8, 10 }, Type::BLACK_PAO },
        { { 1, 8 }, Type::BLACK_ZU },
        { { 3, 8 }, Type::BLACK_ZU },
        { { 5, 8 }, Type::BLACK_ZU },
        { { 7, 8 }, Type::BLACK_ZU },
        { { 9, 8 }, Type::BLACK_ZU }
    };

    for (const auto& [pos, type] : piece_list)
        pieces.emplace(pos, factory.at(removeSide(type))(pos.first, pos.second, side() && getSide(type)));
}

void Board::move(const Pos from, const Pos to) {
    const auto& piece = pieces.at(from);
    piece->move(to.first, to.second);
    auto& cell_from = cells.at(from);
    cell_from->change(nullptr);
    auto& cell_to = cells.at(to);
    cell_to->change(piece);
    judgeStatus();
}

void Board::onClick(int x, int y) {
    std::lock_guard guard(lock);
    static Piece const* selected = nullptr;
    if (!isYourTurn() || isMoved())
        return;
    const auto pos = std::make_pair(x, y);
    if (pieces.count(pos)) {
        const auto& piece = pieces.at(pos);
        if (piece->side() == side()) {
            selected = piece;
            cells.at(pos)->select();
            moved = true;
            your_turn = false;
            move(selected->pos(), pos);
            return;
        }
    }
    if (!selected)
        return;
    if (selected->isValidMove(x, y)) {
        selected = nullptr;
        cells.at(pos)->fineMove();
    } else
        cells.at(pos)->wrongMove();
}

void Board::onMove(const Pos from, const Pos to) {
    std::lock_guard guard(lock);
    your_turn = true;
    moved = false;
    move(from, to);
}
