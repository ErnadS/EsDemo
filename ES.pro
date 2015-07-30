QT      += core gui widgets network

TARGET = ES
TEMPLATE = app

include(common_library/common_library.pri)
include(gui/gui.pri)

SOURCES += main.cpp\
           mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES = resources/resources.qrc

QMAKE_CXXFLAGS += -Wno-psabi   # disable "mangling of 'va_list' has changed warning
QMAKE_CXXFLAGS += -O3 -Wall -Wextra -std=c++11 -pedantic -Werror
QMAKE_CXXFLAGS += -Wno-error=strict-overflow # temporary fix

target.path = /opt
INSTALLS += target

VERSION = 1.0.6
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
