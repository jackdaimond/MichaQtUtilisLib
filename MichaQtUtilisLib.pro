QT += core gui qml widgets

CONFIG += c++1z

PRECOMPILED_HEADER = src/stdafx.h
CONFIG *= precompile_header

TEMPLATE = lib
CONFIG += staticlib

VERSION=0.2

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS MICHA_LIB_VERSION=$$VERSION

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/ApplicationSettings.cpp \
    src/MichaQtUtilisLib.cpp

HEADERS += \
    src/ApplicationSettings.h \
    src/MichaQtUtilisLib.h

# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target
