#-------------------------------------------------
#
# Project created by QtCreator 2014-06-18T12:43:45
#
#-------------------------------------------------

QT += core gui
CONFIG += thread
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = keyMouse
TEMPLATE = app
DESTDIR = ../keyMouse/bin

CONFIG += c++11
PRECOMPILED_HEADER += utf8.h

SOURCES += main.cpp\
        widget.cpp \
    MyGlobalShortCut/MyGlobalShortCut.cpp \
    MyGlobalShortCut/MyWinEventFilter.cpp \
    SendKeyMouse/sendkeymouse.cpp \
    floatwidget.cpp \
    hookfunction.cpp \
    statewidget.cpp \
    statesettingdialog.cpp

HEADERS  += widget.h \
    MyGlobalShortCut/MyGlobalShortCut.h \
    MyGlobalShortCut/MyWinEventFilter.h \
    SendKeyMouse/sendkeymouse.h \
    floatwidget.h \
    hookfunction.h \
    statewidget.h \
    statesettingdialog.h

FORMS    += widget.ui \
    statesettingdialog.ui
#
LIBS += -lUser32

OTHER_FILES +=

RESOURCES +=

