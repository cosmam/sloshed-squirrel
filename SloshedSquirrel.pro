# Add more folders to ship with the application, here
folder_01.source = qml/SloshedSquirrel
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH = \

CONFIG += c++11

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    processoptions.cpp \
    fileprocessor.cpp \
    fileinfo.cpp

# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2controlsapplicationviewer/qtquick2controlsapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qml/MainAreaModule/MainArea.qml \
    qml/MainAreaModule/MainTabButton.qml \
    qml/MainAreaModule/qmldir

HEADERS += \
    processoptions.h \
    Private/processoptions_p.h \
    fileprocessor.h \
    Private/fileprocessor_p.h \
    fileinfo.h

