#########################################################################PROJECT
cmake_minimum_required( VERSION 2.8 )
cmake_policy( VERSION 3.11 )

project( qucsrflayout
	LANGUAGES CXX
	VERSION 1.0.0
	DESCRIPTION "A tool to produce layout from qucs RF schematics (microstrip only for now)"
#	HOMEPAGE_URL "https://github.com/thomaslepoix/Qucs-RFlayout"
	)

set( CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH}
	"${CMAKE_SOURCE_DIR}/cmake"
	)

if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE "Release" )
endif( NOT CMAKE_BUILD_TYPE )
message( STATUS "Build type: ${CMAKE_BUILD_TYPE}" )

include( FixedShell )

#find_program( CMAKE_CXX_CPPCHECK NAMES cppcheck )
#list( APPEND CMAKE_CXX_CPPCHECK
#	"--enable=all"
#	"--force"
#	)
#find_program( CMAKE_CXX_CLANG_TIDY NAMES clang-tidy )
#set( CMAKE_CXX_CPPCHECK "cppcheck")

set( CMAKE_INSTALL_DEFAULT_DIRECTORY_PERMISSIONS
	OWNER_READ
	OWNER_WRITE
	OWNER_EXECUTE
	GROUP_READ
	GROUP_EXECUTE
	WORLD_READ
	WORLD_EXECUTE
	)

#######################################################################EXTERNALS

find_package( Qt5Core    REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui     REQUIRED )
find_package( Qt5OpenGL  REQUIRED )
find_package( OpenGL     REQUIRED )

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

#########################################################################SOURCES

set( QUCS-RF-LAYOUT_SRCS
	"${CMAKE_SOURCE_DIR}/src/main.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/element.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/eqn.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/pac.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/subst.cpp"
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
	"${CMAKE_SOURCE_DIR}/src/microstrip/element.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/eqn.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/pac.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/subst.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mcorn.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mcoupled.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mcross.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mgap.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mlin.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mmbend.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mopen.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mrstub.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mstep.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mtee.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/mvia.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/microstrip.hpp"
	"${CMAKE_SOURCE_DIR}/src/schparser.hpp"
	"${CMAKE_SOURCE_DIR}/src/xycalculator.hpp"
	"${CMAKE_SOURCE_DIR}/src/layoutwriter.hpp"
	"${CMAKE_SOURCE_DIR}/src/converter.hpp"
	"${CMAKE_SOURCE_DIR}/src/mainwindow.hpp"
	"${CMAKE_SOURCE_DIR}/src/preview.hpp"
	"${CMAKE_SOURCE_DIR}/src/logger.hpp"
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
	QRFL_VERSION="${PROJECT_VERSION}"
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

install(
	TARGETS ${PROJECT_NAME}
	CONFIGURATIONS Release
	RUNTIME DESTINATION "bin" #"${CMAKE_INSTALL_BINDIR}"
	)

###########################################################################TOOLS

add_subdirectory( "${CMAKE_SOURCE_DIR}/doc" )
add_subdirectory( "${CMAKE_SOURCE_DIR}/test" )
add_subdirectory( "${CMAKE_SOURCE_DIR}/pack" )

