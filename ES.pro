QT      += core gui widgets network

TARGET = ES
TEMPLATE = app

target.path = /opt
INSTALLS += target

include(common_library/common_library.pri)
include(gui/gui.pri)

SOURCES += main.cpp\
           mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES = resources/resources.qrc

QMAKE_CXXFLAGS += -Wno-psabi  # disable "mangling of 'va_list' has changed warning
# QMAKE_CXXFLAGS += -O3 -Wall -Wextra -std=c++11 -pedantic -Werror
QMAKE_CXXFLAGS += -O0 -g -Wall -Wextra -std=c++11 -pedantic -Werror
QMAKE_CXXFLAGS += -Wno-error=strict-overflow # temporary fix

CONFIG += release
CONFIG += debug



VERSION = 1.0.0
DEFINES += APP_VERSION=\\\"$$VERSION\\\"
