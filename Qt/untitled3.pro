#-------------------------------------------------
#
# Project created by QtCreator 2015-05-04T19:07:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled3
TEMPLATE = app
QMAKE_LFLAGS += -static
SOURCES += main.cpp\
        mainwindow.cpp \
    bot.cpp \
    misc.cpp \
    AI.cpp \
    dice.cpp \
    Player.cpp

HEADERS  += mainwindow.h \
    bot.h \
    misc.h \
    AI.h \
    dice.h \
    Player.h

FORMS    += mainwindow.ui \
    bot.ui

RESOURCES += \
    textures.qrc
