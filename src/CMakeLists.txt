cmake_minimum_required(VERSION 3.16)
project(Chinese_Chess VERSION 1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Network Widgets)

qt_standard_project_setup()

qt_add_executable(Chinese_Chess WIN32 MACOSX_BUNDLE
    algorithms.cpp algorithms.h
    bing_zu_piece.cpp bing_zu_piece.h
    board.cpp board.h
    cell.cpp cell.h
    dialogui.cpp dialogui.h
    exception.h
    jiang_shuai_piece.cpp jiang_shuai_piece.h
    ju_piece.cpp ju_piece.h
    loginui.cpp loginui.h
    ma_piece.cpp ma_piece.h
    main.cpp
    mainui.cpp mainui.h
    network.cpp network.h
    pao_piece.cpp pao_piece.h
    piece.cpp piece.h
    shi_piece.cpp shi_piece.h
    warning.h
    xiang_piece.cpp xiang_piece.h
)
target_link_libraries(Chinese_Chess PRIVATE
    Qt::Core
    Qt::Gui
    Qt::Network
    Qt::Widgets
)
add_custom_command(TARGET Chinese_Chess PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/network.json $<TARGET_FILE_DIR:Chinese_Chess>)
