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
        element.cpp \
        eqn.cpp \
        pac.cpp \
        mcorn.cpp \
        mcoupled.cpp \
        mcross.cpp \
        mgap.cpp \
        mlin.cpp \
        mmbend.cpp \
        mopen.cpp \
        mrstub.cpp \
        mstep.cpp \
        mtee.cpp \
        mvia.cpp \
        parser.cpp \
        xycalculator.cpp \
        layoutwriter.cpp \
        mainwindow.cpp \
        preview.cpp

HEADERS += \
        element.h \
        eqn.h \
        pac.h \
        mcorn.h \
        mcoupled.h \
        mcross.h \
        mgap.h \
        mlin.h \
        mmbend.h \
        mopen.h \
        mrstub.h \
        mstep.h \
        mtee.h \
        mvia.h \
        parser.h \
        xycalculator.h \
        layoutwriter.h \
        mainwindow.h \
        preview.h

FORMS += \
        mainwindow.ui

LIBS += -lglut -lGLU
