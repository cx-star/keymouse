#-------------------------------------------------
#
# Project created by QtCreator 2014-06-18T12:43:45
#
#-------------------------------------------------

QT       += core gui

CONFIG += thread

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = keyMouse
TEMPLATE = app
DESTDIR = ../keyMouse/bin

SOURCES += main.cpp\
        widget.cpp \
    MyGlobalShortCut/MyGlobalShortCut.cpp \
    MyGlobalShortCut/MyWinEventFilter.cpp \
    SendKeyMouse/sendkeymouse.cpp \
    floatwidget.cpp \
    hookfunction.cpp

HEADERS  += widget.h \
    MyGlobalShortCut/MyGlobalShortCut.h \
    MyGlobalShortCut/MyWinEventFilter.h \
    SendKeyMouse/sendkeymouse.h \
    floatwidget.h \
    hookfunction.h

FORMS    += widget.ui

OTHER_FILES +=

RESOURCES +=

