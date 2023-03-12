#include "mainui.h"
#include "cell.h"
#include "network.h"
#include "board.h"

MainUI::MainUI() : QDialog(),
    layout(new QHBoxLayout), boardLayout(new QGridLayout),
    chu(new QLabel("楚河")), han(new QLabel("汉界")),
    messageLabel(new QLabel("聊天信息：")), messageEdit(new QLineEdit),
    sendMessageButton(new QPushButton("发送")), messageArea(new QScrollArea)
{
    auto count = 0;
    for (auto& i : h) {
        i = new QLabel("---");
        boardLayout->addWidget(i, count / 8 * 2, count % 8 * 2 + 1, Qt::AlignCenter);
        count++;
    }
    count = 0;
    for (auto& i : v1) {
        i = new QLabel("|");
        boardLayout->addWidget(i, count / 9 * 2 + 1, count % 9 * 2, Qt::AlignCenter);
        count++;
    }
    boardLayout->addWidget(chu, 9, 0, 1, 8, Qt::AlignCenter);
    boardLayout->addWidget(han, 9, 10, 1, 8, Qt::AlignCenter);
    for (auto& i : v2) {
        i = new QLabel("|");
        boardLayout->addWidget(i, count / 9 * 2 + 3, count % 9 * 2, Qt::AlignCenter);
        count++;
    }
    count = 0;
    for (auto& i : cells) {
        i = new Cell(count% 9 + 1, 10 - count / 9);
        boardLayout->addWidget(i, count / 9 * 2, count % 9 * 2);
        count++;
    }
    l[0] = new QLabel("\\");
    boardLayout->addWidget(l[0], 1, 7, Qt::AlignCenter);
    l[1] = new QLabel("/");
    boardLayout->addWidget(l[1], 1, 9, Qt::AlignCenter);
    l[2] = new QLabel("/");
    boardLayout->addWidget(l[2], 3, 7, Qt::AlignCenter);
    l[3] = new QLabel("\\");
    boardLayout->addWidget(l[3], 3, 9, Qt::AlignCenter);
    l[0] = new QLabel("\\");
    boardLayout->addWidget(l[0], 15, 7, Qt::AlignCenter);
    l[1] = new QLabel("/");
    boardLayout->addWidget(l[1], 15, 9, Qt::AlignCenter);
    l[6] = new QLabel("/");
    boardLayout->addWidget(l[6], 17, 7, Qt::AlignCenter);
    l[7] = new QLabel("\\");
    boardLayout->addWidget(l[7], 17, 9, Qt::AlignCenter);

    layout->addLayout(boardLayout);

    QHBoxLayout* sendArea = new QHBoxLayout;
    sendArea->addWidget(messageEdit, 1);
    sendArea->addWidget(sendMessageButton, 0, Qt::AlignRight);

    messageArea->setWidget(messageLabel);
    messageArea->setAlignment(Qt::AlignTop);
    messageArea->setWidgetResizable(true);

    QVBoxLayout* chatArea = new QVBoxLayout;
    chatArea->addWidget(messageArea, 1);
    chatArea->addLayout(sendArea);
    layout->addLayout(chatArea);

    connect(messageEdit, &QLineEdit::returnPressed, [this]{
        sendMessageButton->click();
    });
    connect(sendMessageButton, &QPushButton::clicked, [this]{
        QString msg = messageEdit->text();
        messageLabel->setText(messageLabel->text().append(QT_UNICODE_LITERAL("\n自己：")).append(msg));
        emit message(msg);
        messageEdit->setText("");
    });

    setLayout(layout);
    connect(Network::getInstance(), &Network::findOK, this, &MainUI::onFind);
    connect(Network::getInstance(), &Network::move, Board::getBoard(), &Board::onMove);
    connect(Board::getBoard(), &Board::pieceMoved, Network::getInstance(), &Network::onMove);
    connect(this, &MainUI::setup, Board::getBoard(), &Board::onSetup);

    connect(Network::getInstance(), &Network::message, this, &MainUI::onMessageReceived);
    connect(this, &MainUI::message, Network::getInstance(), &Network::onMessageSent);
}

void MainUI::onMessageReceived(const QString msg)
{
    messageLabel->setText(messageLabel->text().append(QT_UNICODE_LITERAL("\n对面：")).append(msg));
}
