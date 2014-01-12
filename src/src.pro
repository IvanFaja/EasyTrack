#-------------------------------------------------
#
# Project created by QtCreator 2014-01-12T13:01:09
#
#-------------------------------------------------

QT       -= gui

TARGET = src
TEMPLATE = lib

DEFINES += SRC_LIBRARY

SOURCES += item.cpp

HEADERS += item.h\
        src_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
