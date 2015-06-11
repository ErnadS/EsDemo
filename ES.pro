QT      += core gui widgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ES
TEMPLATE = app

include(common/common.pri)

SOURCES += main.cpp\
           mainwindow.cpp \
           RuntimeWidgetEs.cpp \
           InformationWidget.cpp \
           BrightnessWidget.cpp \
           NavigationWidget.cpp \
           BackgroundWidget.cpp \
           Button.cpp \
           DisplayAliveWidget.cpp \
           BaseScreen.cpp \
           SpeedIndicationWidget.cpp \
           ScalableWidget.cpp \
           RuntimeScreen.cpp \
           NavigationController.cpp \
           RuntimeWidgetA.cpp \
           RuntimeWidgetB.cpp \
           RuntimeWidgetC.cpp \
           RuntimeWidgetD.cpp \
           RuntimeWidgetE.cpp \
           RuntimeWidgetDl1.cpp \
           RuntimeWidget.cpp \
           MultiRuntimeWidget.cpp \
           TransparentInfoButton.cpp \
           SetupMenuScreen.cpp \
           SystemWidget.cpp \
           Dl1RuntimeWidgetB.cpp \
           EsRuntimeWidgetB.cpp \
           BoatMenuScreen.cpp \
           EsRuntimeScreen.cpp \
           BoatButton.cpp

HEADERS  += mainwindow.h \
            RuntimeWidgetEs.h \
            InformationWidget.h \
            BrightnessWidget.h \
            NavigationWidget.h \
            BackgroundWidget.h \
            Button.h \
            DisplayAliveWidget.h \
            BaseScreen.h \
            SpeedIndicationWidget.h \
            ScalableWidget.h \
            RuntimeScreen.h \
            NavigationController.h \
            RuntimeWidgetA.h \
            RuntimeWidgetB.h \
            RuntimeWidgetC.h \
            RuntimeWidgetD.h \
            RuntimeWidgetE.h \
            RuntimeWidgetDl1.h \
            WidgetEnum.h \
            RuntimeWidget.h \
            MultiRuntimeWidget.h \
            TransparentInfoButton.h \
            SetupMenuScreen.h \
            SystemWidget.h \
            Dl1RuntimeWidgetB.h \
            EsRuntimeWidgetB.h \
            BoatMenuScreen.h \
            EsRuntimeScreen.h \
            BoatButton.h

FORMS    += mainwindow.ui

RESOURCES = resources/resources.qrc

QMAKE_CXXFLAGS += -Wno-psabi   # disable "mangling of 'va_list' has changed warning
QMAKE_CXXFLAGS += -O3 -Wall -Wextra -std=c++11 -pedantic -Werror

target.path = /opt
INSTALLS += target
