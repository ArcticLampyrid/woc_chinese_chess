#include "cell.h"

QColor Cell::selected = QColor(0x00, 0x66, 0xFF);
QColor Cell::wrong = QColor(0xFF, 0x33, 0x00);
QColor Cell::fine = QColor(0x00, 0xFF, 0x33);

Cell::Cell(int x, int y) : QPushButton("+"), x(x), y(y)
{
    setFlat(true);
    setFixedSize(20, 20);
    //Add your own code below
    //////////////////////////


    //////////////////////////
}
