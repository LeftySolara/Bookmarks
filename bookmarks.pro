#-------------------------------------------------
#
# Project created by QtCreator 2016-04-28T19:13:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bookmarks
INCLUDEPATH += src
CONFIG += C++11
TEMPLATE = app


SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp

HEADERS  += \
    src/show.h \
    src/mainwindow.h

FORMS    += \
    src/mainwindow.ui

DISTFILES += \
    defaults.pri
