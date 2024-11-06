cmake_minimum_required( VERSION 3.23 )

file( STRINGS "${CMAKE_SOURCE_DIR}/CHANGELOG" PROJECT_VERSION
	LIMIT_COUNT 1
	)

string( REGEX REPLACE
	"^qucsrflayout \\((.*)\\)$" "\\1"
	PROJECT_VERSION "${PROJECT_VERSION}"
	)

project( qucsrflayout
	LANGUAGES CXX
	VERSION "${PROJECT_VERSION}"
	DESCRIPTION "A tool to produce layout from qucs RF schematics (microstrip only for now)"
	HOMEPAGE_URL "https://github.com/thomaslepoix/Qucs-RFlayout"
	)
message( STATUS "Version: ${PROJECT_VERSION}" )

set( QRFL_BUGREPORT     "https://github.com/thomaslepoix/Qucs-RFlayout/issues" )
set( QRFL_FUNDING       "https://liberapay.com/thomaslepoix" )
set( QRFL_OEMS_TUTORIAL "https://github.com/thomaslepoix/Qucs-RFlayout/blob/master/doc/tutorials/openems.md" )
file( READ "${CMAKE_SOURCE_DIR}/CHANGELOG" QRFL_CHANGELOG )

set( CMAKE_MODULE_PATH
	${CMAKE_MODULE_PATH}
	"${CMAKE_SOURCE_DIR}/cmake"
	)

if( NOT CMAKE_BUILD_TYPE )
	set( CMAKE_BUILD_TYPE "Release" )
endif( NOT CMAKE_BUILD_TYPE )
message( STATUS "Build type: ${CMAKE_BUILD_TYPE}" )

include( FixedShell )

#if( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux" )
#	set( HOST_LINUX TRUE )
#endif( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux" )

option( QRFL_MINIMAL "Disable GUI support and Qt dependency" OFF )
message( STATUS "Minimal mode: ${QRFL_MINIMAL}" )
if( WIN32 AND QRFL_MINIMAL )
	message( FATAL_ERROR "QRFL_MINIMAL is not compatible with Windows build" )
endif( WIN32 AND QRFL_MINIMAL )

#if( MINGW AND HOST_LINUX )
#	find_program( PELDD NAMES peldd )
#	if( PELDD )
#		message( STATUS "Found peldd: ${PELDD}" )
#	else( PELDD )
#		message( ERROR "Not found peldd: Please install https://github.com/gsauthof/pe-util" )
#	endif( PELDD )
#endif( MINGW AND HOST_LINUX )

if( STATIC MATCHES TRUE )
	find_program( CMAKE_CXX_CPPCHECK NAMES cppcheck )
	list( APPEND CMAKE_CXX_CPPCHECK
		"--enable=all"
		"--force"
		)
	find_program( CMAKE_CXX_CLANG_TIDY NAMES clang-tidy )
	set( CMAKE_CXX_CPPCHECK "cppcheck")
endif( STATIC MATCHES TRUE )

if( CMAKE_BUILD_TYPE MATCHES Coverage )
	find_program( GCOV NAMES gcov )
	if( GCOV )
		message( STATUS "Found gcov: ${GCOV}" )
	else( GCOV )
		message( ERROR "Not found gcov: install it" )
	endif( GCOV )

	find_program( LCOV NAMES lcov )
	if( LCOV )
		message( STATUS "Found lcov: ${LCOV}" )
	else( LCOV )
		message( ERROR "Not found lcov: install it" )
	endif( LCOV )

	find_program( GENHTML NAMES genhtml )
	if( GENHTML )
		message( STATUS "Found genhtml: ${GENHTML}" )
	else( GENHTML )
		message( ERROR "Not found genhtml: install it" )
	endif( GENHTML )
endif( CMAKE_BUILD_TYPE MATCHES Coverage )

set( CMAKE_INSTALL_DEFAULT_DIRECTORY_PERMISSIONS
	OWNER_READ
	OWNER_WRITE
	OWNER_EXECUTE
	GROUP_READ
	GROUP_EXECUTE
	WORLD_READ
	WORLD_EXECUTE
	)

if( NOT QRFL_MINIMAL )
	find_package( OpenGL REQUIRED )

	find_package( Qt6
		COMPONENTS
		Core          REQUIRED
		Gui           REQUIRED
		OpenGLWidgets REQUIRED
		Widgets       REQUIRED
		)
endif( NOT QRFL_MINIMAL )

add_subdirectory( "${CMAKE_SOURCE_DIR}/src" )
add_subdirectory( "${CMAKE_SOURCE_DIR}/doc" )
add_subdirectory( "${CMAKE_SOURCE_DIR}/test" )
add_subdirectory( "${CMAKE_SOURCE_DIR}/pack" )
