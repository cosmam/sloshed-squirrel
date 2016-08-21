TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

RESOURCES += qml.qrc

SOURCES += unittests/main.cpp \
    unittests/src/core/initparams.cpp \
    unittests/src/core/testcasefactory.cpp \
    unittests/src/core/impl/testcase.cpp

include(CodeAnalysis.pri)
include(unittests/deployment.pri)

HEADERS += \
    unittests/src/core/testcase.h \
    unittests/src/core/testtypes.h \
    unittests/src/core/initparams.h \
    unittests/src/core/testcasefactory.h \
    unittests/src/core/impl/testcase.h

