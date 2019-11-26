#/usr/lib/qt5/bin/qmake
#-------------------------------------------------
#
# Project created by QtCreator 2018-11-16T09:44:12
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = build/qucsrflayout
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        microstrip/element.cpp \
        microstrip/eqn.cpp \
        microstrip/pac.cpp \
        microstrip/mcorn.cpp \
        microstrip/mcoupled.cpp \
        microstrip/mcross.cpp \
        microstrip/mgap.cpp \
        microstrip/mlin.cpp \
        microstrip/mmbend.cpp \
        microstrip/mopen.cpp \
        microstrip/mrstub.cpp \
        microstrip/mstep.cpp \
        microstrip/mtee.cpp \
        microstrip/mvia.cpp \
        parser.cpp \
        xycalculator.cpp \
        layoutwriter.cpp \
        mainwindow.cpp \
        preview.cpp \
        logger.cpp

HEADERS += \
        microstrip/element.h \
        microstrip/eqn.h \
        microstrip/pac.h \
        microstrip/mcorn.h \
        microstrip/mcoupled.h \
        microstrip/mcross.h \
        microstrip/mgap.h \
        microstrip/mlin.h \
        microstrip/mmbend.h \
        microstrip/mopen.h \
        microstrip/mrstub.h \
        microstrip/mstep.h \
        microstrip/mtee.h \
        microstrip/mvia.h \
        parser.h \
        xycalculator.h \
        layoutwriter.h \
        mainwindow.h \
        preview.h \
        logger.h

FORMS += \
        mainwindow.ui

