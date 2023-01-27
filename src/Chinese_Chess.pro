QT       += core gui widgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    algorithms.cpp \
    bing_zu_piece.cpp \
    cell.cpp \
    dialogui.cpp \
    jiang_shuai_piece.cpp \
    ju_piece.cpp \
    loginui.cpp \
    ma_piece.cpp \
    main.cpp \
    board.cpp \
    mainui.cpp \
    network.cpp \
    pao_piece.cpp \
    piece.cpp \
    shi_piece.cpp \
    xiang_piece.cpp

HEADERS += \
    algorithms.h \
    bing_zu_piece.h \
    board.h \
    cell.h \
    dialogui.h \
    exception.h \
    jiang_shuai_piece.h \
    ju_piece.h \
    loginui.h \
    ma_piece.h \
    mainui.h \
    network.h \
    pao_piece.h \
    piece.h \
    shi_piece.h \
    warning.h \
    xiang_piece.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    network.json
