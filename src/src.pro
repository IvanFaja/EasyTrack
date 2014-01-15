#-------------------------------------------------
#
# Project created by QtCreator 2014-01-12T13:01:09
#
#-------------------------------------------------

QT       -= gui
QT      += sql
TARGET = src
TEMPLATE = lib

DEFINES += SRC_LIBRARY

SOURCES += item.cpp \
    Database/databasemanager.cpp \
    itemprivate.cpp \
    Database/itemmodel.cpp

HEADERS += item.h\
        src_global.h \
    Database/databasemanager.h \
    itemprivate.h \
    Database/itemmodel.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
