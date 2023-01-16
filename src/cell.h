#ifndef CELL_H
#define CELL_H

#include "piece.h"

#include <QPushButton>

class Cell : public QPushButton {
    Q_OBJECT

    static QColor selected, wrong, fine;
public:
    const int x, y;
    Cell(int x, int y);

    inline void change(Piece const* piece = nullptr) {
        if (!piece)
            setText("+");
        else
            setText(QString(piece->text()));
    }
    inline void select() {
        setPalette(selected);
    }
    inline void wrongMove() {
        setPalette(wrong);
    }
    inline void fineMove() {
        setPalette(fine);
    }
signals:
    void click(int x, int y);
};

#endif // CELL_H
