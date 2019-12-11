project(qucsrflayout CXX)
cmake_minimum_required(VERSION 3.0)
cmake_policy(VERSION 3.0)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(OpenGL REQUIRED)

#find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)
#list(APPEND CMAKE_CXX_CPPCHECK
#	"--enable=all"
#	"--force"
#	)
#find_program(CMAKE_CXX_CLANG_TIDY NAMES clang-tidy)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


#set(CMAKE_CXX_CPPCHECK "cppcheck")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

add_definitions(${QT_DEPRECATED_WARNINGS})

set(QUCS-RF-LAYOUT_SRCS
        src/main.cpp
        src/microstrip/element.cpp
        src/microstrip/eqn.cpp
        src/microstrip/pac.cpp
#		srcmicrostrip/subst.cpp
        src/microstrip/mcorn.cpp
        src/microstrip/mcoupled.cpp
        src/microstrip/mcross.cpp
        src/microstrip/mgap.cpp
        src/microstrip/mlin.cpp
        src/microstrip/mmbend.cpp
        src/microstrip/mopen.cpp
        src/microstrip/mrstub.cpp
        src/microstrip/mstep.cpp
        src/microstrip/mtee.cpp
        src/microstrip/mvia.cpp
        src/schparser.cpp
        src/xycalculator.cpp
        src/layoutwriter.cpp
        src/converter.cpp
        src/mainwindow.cpp
        src/preview.cpp
        src/logger.cpp
)

#set(QUCS-RF-LAYOUT_HDRS
#        src/microstrip/element.h
#        src/microstrip/eqn.h
#        src/microstrip/pac.h
#        src/microstrip/subst.h
#        src/microstrip/mcorn.h
#        src/microstrip/mcoupled.h
#        src/microstrip/mcross.h
#        src/microstrip/mgap.h
#        src/microstrip/mlin.h
#        src/microstrip/mmbend.h
#        src/microstrip/mopen.h
#        src/microstrip/mrstub.h
#        src/microstrip/mstep.h
#        src/microstrip/mtee.h
#        src/microstrip/mvia.h
#        src/parser.h
#        src/xycalculator.h
#        src/layoutwriter.h
#        src/mainwindow.h
#        src/preview.h
#)

set(QUCS-RF-LAYOUT_UIS
        src/mainwindow.ui
)

include_directories("src")

add_executable(qucsrflayout ${QUCS-RF-LAYOUT_SRCS})

qt5_use_modules(qucsrflayout Core Gui OpenGL)

set(EXECUTABLE_OUTPUT_PATH "../bin")

# man pages
install(FILES qucsrflayout.1.cmake.in DESTINATION share/man/man1)

