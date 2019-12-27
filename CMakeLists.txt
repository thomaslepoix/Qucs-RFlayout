cmake_minimum_required( VERSION 2.8 )
cmake_policy( VERSION 3.10 )
project( qucsrflayout CXX )

set( CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH}
	"${CMAKE_SOURCE_DIR}/cmake"
	)

include( ClangFormat )
include( FixedShell )
include( Package )

find_package( Qt5Core    REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui     REQUIRED )
find_package( Qt5OpenGL  REQUIRED )
find_package( OpenGL     REQUIRED )

#find_program( CMAKE_CXX_CPPCHECK NAMES cppcheck )
#list( APPEND CMAKE_CXX_CPPCHECK
#	"--enable=all"
#	"--force"
#	)
#find_program( CMAKE_CXX_CLANG_TIDY NAMES clang-tidy )
#set( CMAKE_CXX_CPPCHECK "cppcheck")

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

#########################################################################SOURCES

set( QUCS-RF-LAYOUT_SRCS
	"${CMAKE_SOURCE_DIR}/src/main.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/element.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/eqn.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/pac.cpp"
#	"${CMAKE_SOURCE_DIR}/srcmicrostrip/subst.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mcorn.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mcoupled.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mcross.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mgap.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mlin.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mmbend.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mopen.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mrstub.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mstep.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mtee.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mvia.cpp"
	"${CMAKE_SOURCE_DIR}/src/schparser.cpp"
	"${CMAKE_SOURCE_DIR}/src/xycalculator.cpp"
	"${CMAKE_SOURCE_DIR}/src/layoutwriter.cpp"
	"${CMAKE_SOURCE_DIR}/src/converter.cpp"
	"${CMAKE_SOURCE_DIR}/src/mainwindow.cpp"
	"${CMAKE_SOURCE_DIR}/src/preview.cpp"
	"${CMAKE_SOURCE_DIR}/src/logger.cpp"
	)

set( QUCS-RF-LAYOUT_HDRS
	"${CMAKE_SOURCE_DIR}/src/microstrip/element.h"
	"${CMAKE_SOURCE_DIR}/src/microstrip/eqn.h"
	"${CMAKE_SOURCE_DIR}/src/microstrip/pac.h"
#	"${CMAKE_SOURCE_DIR}/src/microstrip/subst.h"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mcorn.h"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mcoupled.h"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mcross.h"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mgap.h"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mlin.h"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mmbend.h"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mopen.h"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mrstub.h"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mstep.h"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mtee.h"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mvia.h"
	"${CMAKE_SOURCE_DIR}/src/microstrip/microstrip.h"
	"${CMAKE_SOURCE_DIR}/src/schparser.h"
	"${CMAKE_SOURCE_DIR}/src/xycalculator.h"
	"${CMAKE_SOURCE_DIR}/src/layoutwriter.h"
	"${CMAKE_SOURCE_DIR}/src/converter.h"
	"${CMAKE_SOURCE_DIR}/src/mainwindow.h"
	"${CMAKE_SOURCE_DIR}/src/preview.h"
	"${CMAKE_SOURCE_DIR}/src/logger.h"
	)

##########################################################################TARGET

add_executable( ${PROJECT_NAME} ${QUCS-RF-LAYOUT_SRCS} )
#[[ CMAKE 3.12
add_executable( ${PROJECT_NAME} )
target_sources( ${PROJECT_NAME}
	PRIVATE
	${QUCS-RF-LAYOUT_SRCS}
	)
#]]

target_compile_definitions( ${PROJECT_NAME}
	PRIVATE
	${QT_DEPRECATED_WARNINGS}
	)

target_compile_features( ${PROJECT_NAME}
	PRIVATE
	cxx_std_11
	)

target_compile_options( ${PROJECT_NAME}
	PRIVATE
	$<$<CONFIG:Debug>:-Wall>
	$<$<CONFIG:Debug>:-Wextra>
	$<$<CONFIG:Debug>:-fexceptions>
	)

target_include_directories( ${PROJECT_NAME}
	PRIVATE
	"${CMAKE_SOURCE_DIR}/src"
	)

qt5_use_modules( ${PROJECT_NAME}
	Core
	Gui
	OpenGL
	)

set_target_properties( ${PROJECT_NAME} PROPERTIES
	OUTPUT_NAME "qucsrflayout"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out"
	)

#########################################################################INSTALL

set( QUCS_URL "https://sf.net/p/qucs" )
set( QUCS_BUGREPORT "qucs-bugs@lists.sourceforge.net" )

configure_file(
	"${CMAKE_SOURCE_DIR}/doc/qucsrflayout.1.cmake.in"
	"${CMAKE_SOURCE_DIR}/out/qucsrflayout.1"
	)

#[[ man pages
install(
	FILES "${CMAKE_SOURCE_DIR}/qucsrflayout.1.cmake.in"
	DESTINATION "${CMAKE_SOURCE_DIR}/out"
#	DESTINATION "share/man/man1"
	)
#]]
###########################################################################TOOLS

add_target_format(
	${QUCS-RF-LAYOUT_SRCS}
	${QUCS-RF-LAYOUT_HDRS}
	)

add_target_dist(
	"${CMAKE_SOURCE_DIR}/build/*"
	"${CMAKE_SOURCE_DIR}/out/${PROJECT_NAME}.src.tar.*"
	)

add_subdirectory( "${CMAKE_SOURCE_DIR}/test" )

