TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    networkinterface.cpp \
    overviewupdater.cpp \
    applicationsettings.cpp \
    networkgraph.cpp \
    networkupdater.cpp \
    networkstorage.cpp

RESOURCES += qml.qrc

CONFIG += c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    networkinterface.h \
    networkunit.h \
    overviewupdater.h \
    applicationsettings.h \
    networkgraph.h \
    networkupdater.h \
    networkstorage.h \
    transfertypedefs.h
