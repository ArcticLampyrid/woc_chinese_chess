#ifndef BOARD_H
#define BOARD_H

#include "cell.h"

#include <QObject>
#include <functional>
#include <mutex>
#include <utility>

/* BOARD Layout
 * 对手：
 * 10   +-+-+-+-+-+-+-+-+
 *      | | | |\|/| | | |
 * 9    +-+-+-+-+-+-+-+-+
 *      | | | |/|\| | | |
 * 8    +-+-+-+-+-+-+-+-+
 *      | | | | | | | | |
 * 7    +-+-+-+-+-+-+-+-+
 *      | | | | | | | | |
 * 6    +-+-+-+-+-+-+-+-+
 *        楚河      汉界
 * 5    +-+-+-+-+-+-+-+-+
 *      | | | | | | | | |
 * 4    +-+-+-+-+-+-+-+-+
 *      | | | | | | | | |
 * 3    +-+-+-+-+-+-+-+-+
 *      | | | |\|/| | | |
 * 2    +-+-+-+-+-+-+-+-+
 *      | | | |/|\| | | |
 * 1    +-+-+-+-+-+-+-+-+
 *      1 2 3 4 5 6 7 8 9
 * 我方：
*/
class Board : public QObject
{
    Q_OBJECT

    using Constructor = std::function<std::shared_ptr<Piece>(int, int, bool)>;    //工厂函数类型
public:
    //获取全局单例对象
    static inline const Board* getBoard() {
        static Board const* singleton = nullptr;    //全局单例
        if (!singleton)
            singleton = new Board;
        return singleton;
    }
private:
    bool checked = false;       //将军状态
    bool your_turn = false;     //你的回合
    bool moved = false;         //是否走棋
    mutable bool SIDE;          //哪一方？
    std::mutex lock;
public:
    inline bool isChecked() const {
        return checked;
    }
    inline bool isYourTurn() const {
        return your_turn;
    }
    inline bool isMoved() const {
        return moved;
    }
    inline bool side() const {
        return SIDE;
    }
private:
    std::map<Pos, std::shared_ptr<Piece>> pieces;
    std::map<Pos, Cell*> cells;

    Board();
    void setPieces(const std::map<Piece::PieceType, Constructor> &);
    void move(const Pos from, const Pos to);
    void judgeStatus(); //走棋后对局势评估（输赢和当前是否处于将军状态）
signals:
    void win(bool side);
    void pieceMoved(const Pos from, const Pos to);
public slots:
    void onSetup(Cell**);
    void onClick(int x, int y);
    void onMove(const Pos from, const Pos to);  //对方走棋
public:
    ~Board() {}

    friend class Algorithms;
    friend class Network;
};
#endif // BOARD_H
