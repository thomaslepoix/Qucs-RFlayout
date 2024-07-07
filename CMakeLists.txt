#########################################################################PROJECT
#cmake_minimum_required( VERSION 3.12 )
cmake_minimum_required( VERSION 3.20 )
cmake_policy(SET CMP0069 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)

project( qucsrflayout
	LANGUAGES CXX
	VERSION 2.0.1
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

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

option( CPM_DISABLE "Don't use CPM to retrieve dependencies" "$ENV{CPM_DISABLE}" )

if( NOT CPM_DISABLE )
	message( STATUS "Downloading dependencies with CPM" )

	list( APPEND CMAKE_MODULE_PATH
		"${CMAKE_SOURCE_DIR}/cmake"
		)

	include( CPM )

	# https://github.com/cpm-cmake/CPM.cmake/issues/428

	set( QT_MODULES
		qtbase
		)

	CPMAddPackage(
		NAME Qt6
		GIT_REPOSITORY https://code.qt.io/qt/qt5.git
		VERSION 6.6.1
		GIT_SHALLOW
		GIT_SUBMODULES "${QT_MODULES}"
#		DOWNLOAD_ONLY
		)

	set( Qt6_base_DIR "${Qt6_base_BINARY_DIR}" )

#	CPMAddPackage(
#		NAME cmake-utils
#		GITHUB_REPOSITORY conformism/cmake-utils
#		GIT_TAG main
#		DOWNLOAD_ONLY
#		)
#
#	set( CMakeUtils_DIR "${cmake-utils_SOURCE_DIR}" )
#
#	CPMAddPackage(
#		NAME pugixml
#		GITHUB_REPOSITORY zeux/pugixml
#		VERSION 1.12.1
#		OPTIONS
#			"BUILD_SHARED_LIBS ON"
#		)
#
#	set( pugixml_DIR "${pugixml_BINARY_DIR}" )
#
#	CPMAddPackage(
#		NAME CLI11
#		GITHUB_REPOSITORY CLIUtils/CLI11
#		VERSION 2.3.1
#		)
#
#	set( CLI11_DIR "${CLI11_BINARY_DIR}" )

endif()

include( FixedShell )

if( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux" )
	set( HOST_LINUX TRUE )
endif( ${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux" )

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

#######################################################################EXTERNALS

find_package( OpenGL REQUIRED )

find_package( Qt6
	COMPONENTS
	Core          REQUIRED
	Gui           REQUIRED
	OpenGLWidgets REQUIRED
	Widgets       REQUIRED
	)

set( CMAKE_INCLUDE_CURRENT_DIR ON )

#########################################################################SOURCES
set( QUCS-RF-LAYOUT_SRCS
	"${CMAKE_SOURCE_DIR}/src/logger.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/element.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/pac.cpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/sp.cpp"
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
	"${CMAKE_SOURCE_DIR}/src/data.cpp"
	"${CMAKE_SOURCE_DIR}/src/schparser.cpp"
	"${CMAKE_SOURCE_DIR}/src/xycalculator.cpp"
	"${CMAKE_SOURCE_DIR}/src/oemsline.cpp"
	"${CMAKE_SOURCE_DIR}/src/oemsmesh.cpp"
	"${CMAKE_SOURCE_DIR}/src/layoutstrings.cpp"
	"${CMAKE_SOURCE_DIR}/src/layoutwriter.cpp"
	"${CMAKE_SOURCE_DIR}/src/converter.cpp"
	"${CMAKE_SOURCE_DIR}/src/preview.cpp"
	"${CMAKE_SOURCE_DIR}/src/mainwindow.cpp"
	"${CMAKE_SOURCE_DIR}/src/main.cpp"
	)

set( QUCS-RF-LAYOUT_HDRS
	"${CMAKE_SOURCE_DIR}/src/logger.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/element.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/pac.hpp"
	"${CMAKE_SOURCE_DIR}/src/microstrip/sp.hpp"
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
	"${CMAKE_SOURCE_DIR}/src/data.hpp"
	"${CMAKE_SOURCE_DIR}/src/schparser.hpp"
	"${CMAKE_SOURCE_DIR}/src/xycalculator.hpp"
	"${CMAKE_SOURCE_DIR}/src/oemsline.hpp"
	"${CMAKE_SOURCE_DIR}/src/oemsmesh.hpp"
	"${CMAKE_SOURCE_DIR}/src/layoutstrings.hpp"
	"${CMAKE_SOURCE_DIR}/src/layoutwriter.hpp"
	"${CMAKE_SOURCE_DIR}/src/converter.hpp"
	"${CMAKE_SOURCE_DIR}/src/preview.hpp"
	"${CMAKE_SOURCE_DIR}/src/mainwindow.hpp"
	)

##########################################################################TARGET

add_executable( ${PROJECT_NAME} WIN32
	${QUCS-RF-LAYOUT_SRCS}
	)
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
	cxx_std_23
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

target_link_libraries( ${PROJECT_NAME}
#	PRIVATE
	Qt6::Core
	Qt6::Gui
	Qt6::OpenGLWidgets
	Qt6::Widgets
	)

set_target_properties( ${PROJECT_NAME} PROPERTIES
	OUTPUT_NAME "qucsrflayout"
#	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
	AUTOMOC ON
	AUTOUIC ON
	)

install(
	TARGETS ${PROJECT_NAME}
	CONFIGURATIONS Release
	RUNTIME DESTINATION "bin" #"${CMAKE_INSTALL_BINDIR}"
	)

include( CheckIPOSupported )
# Optional IPO. Do not use IPO if it's not supported by compiler.
check_ipo_supported(
	RESULT result
	OUTPUT output
	)
if( result )
	set_property( TARGET ${PROJECT_NAME}
		PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE
		)
else()
	message( WARNING "IPO is not supported: ${output}" )
endif()

#if( WIN32 )
#
#	if( MINGW AND HOST_LINUX )
#		set( MINGW_PATH "/usr/x86_64-w64-mingw32" )
#
#		add_custom_command(
#			TARGET ${PROJECT_NAME} POST_BUILD
#			COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/dist/platforms"
#			COMMAND ${CMAKE_COMMAND} -E copy_if_different `${PELDD} -a "${CMAKE_BINARY_DIR}/qucsrflayout.exe" -w UxTheme.dll -w d3d11.dll -w dxgi.dll -w OPENGL32.dll -w USERENV.dll` "${CMAKE_BINARY_DIR}/dist"
#			COMMAND ${CMAKE_COMMAND} -E copy_if_different "${MINGW_PATH}/lib/qt/plugins/platforms/qwindows.dll" "${CMAKE_BINARY_DIR}/dist/platforms"
#			COMMENT "Find additional DLLs"
#			)
#	else( MINGW AND HOST_LINUX )
#		#  Use winqdeploy or a Microsoft equivalent of ldd to copy dlls
#	endif( MINGW AND HOST_LINUX )
#
#	install(
#		DIRECTORY "${CMAKE_BINARY_DIR}/dist/."
#		DESTINATION "bin"
#		)
#
#endif( WIN32 )

###########################################################################TOOLS

add_subdirectory( "${CMAKE_SOURCE_DIR}/doc" )
add_subdirectory( "${CMAKE_SOURCE_DIR}/test" )
add_subdirectory( "${CMAKE_SOURCE_DIR}/pack" )


find_package( CMakeUtils )
set( CMAKE_UTILS CODECHECKER SANITIZERS )
include( CMakeUtils )

codechecker(
	GLOBAL
#	NO_CTU
	SKIP
		+${CMAKE_SOURCE_DIR}/src
		-*
#		+${CMAKE_SOURCE_DIR}/test/unit
	ARGS
		"${CMAKE_BINARY_DIR}/compile_commands.json"
		-j 4
		--keep-gcc-include-fixed
		--keep-gcc-intrin
#	ADDITIONAL_OPTIONAL_REPORTS
#		"${CMAKE_BINARY_DIR}/src/CMakeFiles/raisin_cppcheck.dir/codechecker_reports"
	)

enable_sanitizers(
	TARGET ${PROJECT_NAME}
	)
