#/usr/lib/qt5/bin/qmake
#-------------------------------------------------
#
# Project created by QtCreator 2018-11-16T09:44:12
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = $$PWD/bin/qucsrflayout
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
        $$PWD/src/main.cpp \
        $$PWD/src/microstrip/element.cpp \
        $$PWD/src/microstrip/eqn.cpp \
        $$PWD/src/microstrip/pac.cpp \
        $$PWD/src/microstrip/mcorn.cpp \
        $$PWD/src/microstrip/mcoupled.cpp \
        $$PWD/src/microstrip/mcross.cpp \
        $$PWD/src/microstrip/mgap.cpp \
        $$PWD/src/microstrip/mlin.cpp \
        $$PWD/src/microstrip/mmbend.cpp \
        $$PWD/src/microstrip/mopen.cpp \
        $$PWD/src/microstrip/mrstub.cpp \
        $$PWD/src/microstrip/mstep.cpp \
        $$PWD/src/microstrip/mtee.cpp \
        $$PWD/src/microstrip/mvia.cpp \
        $$PWD/src/schparser.cpp \
        $$PWD/src/xycalculator.cpp \
        $$PWD/src/layoutwriter.cpp \
        $$PWD/src/converter.cpp \
        $$PWD/src/mainwindow.cpp \
        $$PWD/src/preview.cpp \
        $$PWD/src/logger.cpp

HEADERS += \
        $$PWD/src/microstrip/element.h \
        $$PWD/src/microstrip/eqn.h \
        $$PWD/src/microstrip/pac.h \
        $$PWD/src/microstrip/mcorn.h \
        $$PWD/src/microstrip/mcoupled.h \
        $$PWD/src/microstrip/mcross.h \
        $$PWD/src/microstrip/mgap.h \
        $$PWD/src/microstrip/mlin.h \
        $$PWD/src/microstrip/mmbend.h \
        $$PWD/src/microstrip/mopen.h \
        $$PWD/src/microstrip/mrstub.h \
        $$PWD/src/microstrip/mstep.h \
        $$PWD/src/microstrip/mtee.h \
        $$PWD/src/microstrip/mvia.h \
        $$PWD/src/schparser.h \
        $$PWD/src/xycalculator.h \
        $$PWD/src/layoutwriter.h \
        $$PWD/src/converter.h \
        $$PWD/src/mainwindow.h \
        $$PWD/src/preview.h \
        $$PWD/src/logger.h

FORMS += \
        $$PWD/src/mainwindow.ui

INCLUDEPATH += \
        $$PWD/src

#CONFIG += object_parallel_to_source
