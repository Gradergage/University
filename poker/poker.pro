#-------------------------------------------------
#
# Project created by QtCreator 2015-06-01T01:39:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = poker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    AI.cpp \
    dice.cpp \
    Player.cpp

HEADERS  += mainwindow.h \
    game.h \
    AI.h \
    dice.h \
    misc.h \
    Player.h

FORMS    += mainwindow.ui \
    game.ui

RESOURCES += \
    textures.qrc
