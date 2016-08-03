QT += core
QT -= gui

CONFIG += c++14

TARGET = sloshedsquirrel
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += Java/ \
               Java/Impl

SOURCES += main.cpp \
    Java/parser.cpp \
    Java/Impl/filefactory.cpp \
    Java/Impl/codefile.cpp \
    Java/ifile.cpp

HEADERS += \
    Java/ifile.h \
    Java/visibility.h \
    Java/parser.h \
    Java/Private/parser_p.h \
    Java/Impl/filefactory.h \
    Java/Impl/Private/filefactory_p.h \
    Java/Impl/codefile.h
