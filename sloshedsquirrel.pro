QT += core
QT -= gui

CONFIG += c++14

TARGET = sloshedsquirrel
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += Java/

SOURCES += main.cpp \
    Java/parser.cpp

HEADERS += \
    Java/ifile.h \
    Java/visibility.h \
    Java/parser.h \
    Java/Private/parser_p.h
