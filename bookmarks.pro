#-------------------------------------------------
#
# Project created by QtCreator 2016-04-28T19:13:02
#
#-------------------------------------------------

QT       += core gui sql
QTPLUGIN += -plugin-sql-sqlite

# The application version
VERSION = 0.1

# Preprocessor macro to get the application version in our application
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bookmarks
INCLUDEPATH += src
CONFIG += C++11
TEMPLATE = app


SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/logger.cpp \
    src/dialogaddmedia.cpp \
    src/database.cpp

HEADERS  += \
    src/show.h \
    src/mainwindow.h \
    src/logger.h \
    src/dialogaddmedia.h \
    src/database.h

FORMS    += \
    src/mainwindow.ui \
    src/dialogaddmedia.ui \

DISTFILES += \
    defaults.pri \
    scripts/db_init.sql

RESOURCES += \
    resources.qrc
