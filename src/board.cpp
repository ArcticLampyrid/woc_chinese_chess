#include "board.h"
#include "algorithms.h"
#include "network.h"
#include "jiang_shuai_piece.h"
#include "shi_piece.h"
#include "xiang_piece.h"
#include "ma_piece.h"
#include "ju_piece.h"
#include "pao_piece.h"
#include "bing_zu_piece.h"

using Type = Piece::PieceType;

Board::Board() {
    //Add your own code below
    //////////////////////////


    //////////////////////////
}

void Board::judgeStatus() {
    if (Algorithms::isStalemate(!side()))
        return emit win(side());
    if (Algorithms::isStalemate(side()))
        return emit win(!side());
}

void Board::onSetup(Cell** cells) {
    for (int i = 0; i < 10 * 9; i++) {
        auto& cell = cells[i];
        this->cells.emplace(std::piecewise_construct, std::tuple(cell->x, cell->y), std::tuple(cell));
        connect(cell, &Cell::click, this, &Board::onClick);
    }
    std::map<Type, Constructor> factory = {
        //请将nullptr替换为'new ClassName(x, y, side)'，请正确设置派生类构造函数参数
        { Type::JIANG_SHUAI, [](int x, int y, bool side)->std::shared_ptr<Piece> { return std::make_shared<JiangShuaiPiece>(x, y, side); } },
        { Type::SHI, [](int x, int y, bool side)->std::shared_ptr<Piece> { return std::make_shared<ShiPiece>(x, y, side); } },
        { Type::XIANG, [](int x, int y, bool side)->std::shared_ptr<Piece> { return std::make_shared<XiangPiece>(x, y, side); } },
        { Type::MA, [](int x, int y, bool side)->std::shared_ptr<Piece> { return std::make_shared<MaPiece>(x, y, side); } },
        { Type::JU, [](int x, int y, bool side)->std::shared_ptr<Piece> { return std::make_shared<JuPiece>(x, y, side); } },
        { Type::PAO, [](int x, int y, bool side)->std::shared_ptr<Piece> { return std::make_shared<PaoPiece>(x, y, side); } },
        { Type::BING_ZU, [](int x, int y, bool side)->std::shared_ptr<Piece> { return std::make_shared<BingZuPiece>(x, y, side); } }
    };
    setPieces(factory);
    for (const auto& [pos, piece] : pieces)
        this->cells[pos]->change(piece);
    if (side()) 
        your_turn = true;

    //Add your own code below
    //////////////////////////


    //////////////////////////
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
        { { 1, 4 }, Type::RED_BING },
        { { 3, 4 }, Type::RED_BING },
        { { 5, 4 }, Type::RED_BING },
        { { 7, 4 }, Type::RED_BING },
        { { 9, 4 }, Type::RED_BING },
        { { 1, 10 }, Type::BLACK_JU },
        { { 2, 10 }, Type::BLACK_MA },
        { { 3, 10 }, Type::BLACK_XIANG },
        { { 4, 10 }, Type::BLACK_SHI },
        { { 5, 10 }, Type::BLACK_JIANG },
        { { 6, 10 }, Type::BLACK_SHI },
        { { 7, 10 }, Type::BLACK_XIANG },
        { { 8, 10 }, Type::BLACK_MA },
        { { 9, 10 }, Type::BLACK_JU },
        { { 2, 8 }, Type::BLACK_PAO },
        { { 8, 8 }, Type::BLACK_PAO },
        { { 1, 7 }, Type::BLACK_ZU },
        { { 3, 7 }, Type::BLACK_ZU },
        { { 5, 7 }, Type::BLACK_ZU },
        { { 7, 7 }, Type::BLACK_ZU },
        { { 9, 7 }, Type::BLACK_ZU }
    };

    for (const auto& [pos, type] : piece_list)
        pieces.emplace(pos, factory.at(removeSide(type))(pos.first, pos.second, side() == getSide(type)));
}

void Board::move(const Pos from, const Pos to) {
    const auto& piece = pieces.at(from);
    piece->move(to.first, to.second);
    auto& cell_from = cells.at(from);
    cell_from->change(nullptr);
    auto& cell_to = cells.at(to);
    cell_to->change(piece);
    pieces.insert_or_assign(to, piece);
    pieces.erase(from);
    judgeStatus();
}

void Board::onClick(int x, int y) {
    std::lock_guard guard(lock);
    static std::weak_ptr<Piece> selected;
    if (!isYourTurn() || isMoved())
        return;
    const auto pos = std::make_pair(x, y);
    if (pieces.count(pos)) {
        const auto& piece = pieces.at(pos);
        if (piece->side() == side()) {
            selected = piece;
            cells.at(pos)->select();
            return;
        }
    }
    auto lockedSelected = selected.lock();
    if (!lockedSelected)
        return;
    if (lockedSelected->isValidMove(pieces, x, y)) {
        cells.at(pos)->fineMove();
        auto originPos = lockedSelected->pos();
        emit pieceMoved(originPos, pos);
        move(originPos, pos);
        moved = true;
        your_turn = false;
        selected.reset();
    } else
        cells.at(pos)->wrongMove();
}

void Board::onMove(const Pos from, const Pos to) {
    std::lock_guard guard(lock);
    your_turn = true;
    moved = false;
    move(from, to);
}
