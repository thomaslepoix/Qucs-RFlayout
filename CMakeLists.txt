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
set(CMAKE_INCLUDE_CURRENT_DIR ON)


#set(CMAKE_CXX_CPPCHECK "cppcheck")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")

add_definitions(${QT_DEPRECATED_WARNINGS})

set(QUCS-RF-LAYOUT_SRCS
        main.cpp
        microstrip/element.cpp
        microstrip/eqn.cpp
        microstrip/pac.cpp
#		microstrip/subst.cpp
        microstrip/mcorn.cpp
        microstrip/mcoupled.cpp
        microstrip/mcross.cpp
        microstrip/mgap.cpp
        microstrip/mlin.cpp
        microstrip/mmbend.cpp
        microstrip/mopen.cpp
        microstrip/mrstub.cpp
        microstrip/mstep.cpp
        microstrip/mtee.cpp
        microstrip/mvia.cpp
        parser.cpp
        xycalculator.cpp
        layoutwriter.cpp
        mainwindow.cpp
        preview.cpp
        logger.cpp
)

#set(QUCS-RF-LAYOUT_HDRS
#        microstrip/element.h
#        microstrip/eqn.h
#        microstrip/pac.h
#        microstrip/subst.h
#        microstrip/mcorn.h
#        microstrip/mcoupled.h
#        microstrip/mcross.h
#        microstrip/mgap.h
#        microstrip/mlin.h
#        microstrip/mmbend.h
#        microstrip/mopen.h
#        microstrip/mrstub.h
#        microstrip/mstep.h
#        microstrip/mtee.h
#        microstrip/mvia.h
#        parser.h
#        xycalculator.h
#        layoutwriter.h
#        mainwindow.h
#        preview.h
#)

set(QUCS-RF-LAYOUT_UIS
        mainwindow.ui
)

qt5_wrap_ui(QUCS-RF-LAYOUT_UI_HDRS ${QUCS-RF-LAYOUT_UIS})

add_executable(qucsrflayout ${QUCS-RF-LAYOUT_SRCS} ${QUCS-RF-LAYOUT_UI_HDRS})

qt5_use_modules(qucsrflayout Core Gui OpenGL)

set(EXECUTABLE_OUTPUT_PATH "../bin")

# man pages
install(FILES qucsrflayout.1.cmake.in DESTINATION share/man/man1)

