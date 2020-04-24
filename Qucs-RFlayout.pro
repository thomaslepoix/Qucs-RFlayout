#/usr/lib/qt5/bin/qmake
#-------------------------------------------------
#
# Project created by QtCreator 2018-11-16T09:44:12
#
#-------------------------------------------------

QT += core gui opengl
greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

isEmpty(PREFIX): PREFIX = /usr/local

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

##########################################################################TARGET

TARGET = $$PWD/out/qucsrflayout
TEMPLATE = app

SOURCES += \
	$$PWD/src/main.cpp \
	$$PWD/src/microstrip/element.cpp \
	$$PWD/src/microstrip/eqn.cpp \
	$$PWD/src/microstrip/pac.cpp \
	$$PWD/src/microstrip/sp.cpp \
	$$PWD/src/microstrip/subst.cpp \
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
	$$PWD/src/logger.cpp \
	$$PWD/src/data.cpp \
	$$PWD/src/oemsmesh.cpp

HEADERS += \
	$$PWD/src/microstrip/element.hpp \
	$$PWD/src/microstrip/eqn.hpp \
	$$PWD/src/microstrip/pac.hpp \
	$$PWD/src/microstrip/sp.hpp \
	$$PWD/src/microstrip/subst.hpp \
	$$PWD/src/microstrip/mcorn.hpp \
	$$PWD/src/microstrip/mcoupled.hpp \
	$$PWD/src/microstrip/mcross.hpp \
	$$PWD/src/microstrip/mgap.hpp \
	$$PWD/src/microstrip/mlin.hpp \
	$$PWD/src/microstrip/mmbend.hpp \
	$$PWD/src/microstrip/mopen.hpp \
	$$PWD/src/microstrip/mrstub.hpp \
	$$PWD/src/microstrip/mstep.hpp \
	$$PWD/src/microstrip/mtee.hpp \
	$$PWD/src/microstrip/mvia.hpp \
	$$PWD/src/schparser.hpp \
	$$PWD/src/xycalculator.hpp \
	$$PWD/src/layoutwriter.hpp \
	$$PWD/src/converter.hpp \
	$$PWD/src/mainwindow.hpp \
	$$PWD/src/preview.hpp \
	$$PWD/src/logger.hpp \
	$$PWD/src/data.hpp \
	$$PWD/src/oemsmesh.hpp \
	$$PWD/src/oemsline.hpp

FORMS += \
	$$PWD/src/mainwindow.ui

INCLUDEPATH += \
	$$PWD/src

DEFINES += \
	QRFL_VERSION=\\\"1.0.0\\\"

target.path = $$PREFIX/bin
INSTALLS += target

#############################################################################DOC

QUCS_URL = "https://sf.net/p/qucs"
QUCS_BUGREPORT = "qucs-bugs@lists.sourceforge.net"

QMAKE_SUBSTITUTES += $$PWD/doc/qucsrflayout.1.qmake.in

unix {
	man.extra = gzip -9 -c ./doc/qucsrflayout.1.qmake > ./doc/qucsrflayout.1.gz
	man.files = ./doc/qucsrflayout.1.gz
	man.path = $$PREFIX/share/man/man1
	man.clean = rm -f doc/qucsrflayout.1.gz
	INSTALLS += man
	}

#CONFIG += object_parallel_to_source

