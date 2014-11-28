TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    networkinterface.cpp \
    applicationsettings.cpp \
    networkgraph.cpp \
    networkupdater.cpp \
    networkstorage.cpp \
    hourlymodel.cpp

RESOURCES += qml.qrc

CONFIG += c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    networkinterface.h \
    networkunit.h \
    applicationsettings.h \
    networkgraph.h \
    networkupdater.h \
    networkstorage.h \
    transfertypedefs.h \
    hourlymodel.h

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml
