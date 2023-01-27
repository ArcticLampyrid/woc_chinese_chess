#ifndef MAINUI_H
#define MAINUI_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollBar>
#include <QScrollArea>

class Cell;
class MainUI : public QDialog
{
    Q_OBJECT

    QHBoxLayout* layout;
    QGridLayout* boardLayout;
    QLabel *h[8 * 10], *v1[9 * 4], *v2[9 * 4], *l[8], *chu, *han;
    Cell* cells[9 * 10];
    QLabel* messageLabel;
    QLineEdit* messageEdit;
    QPushButton* sendMessageButton;
    QScrollArea* messageArea;
signals:
    void setup(Cell**);
    void message(const QString message);
public slots:
    void onFind(const QString opp_name) {
        emit setup(cells);
    }
    void onMessageReceived(const QString msg);
public:
    MainUI();
};

#endif // MAINUI_H
