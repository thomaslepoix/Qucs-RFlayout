
configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/changelog.hpp.in"
	"${CMAKE_CURRENT_BINARY_DIR}/generated/changelog.hpp"
	@ONLY
	)

add_executable( ${PROJECT_NAME} WIN32 )

target_sources( ${PROJECT_NAME}
	PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/logger.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/microstrip/element.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/microstrip/pac.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/microstrip/sp.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/microstrip/subst.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/microstrip/mcorn.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/microstrip/mcoupled.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/microstrip/mcross.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/microstrip/mgap.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/microstrip/mlin.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/microstrip/mmbend.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/microstrip/mopen.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/microstrip/mrstub.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/microstrip/mstep.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/microstrip/mtee.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/microstrip/mvia.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/data.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/schparser.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/xycalculator.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/oemsline.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/oemsmesh.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/layoutstrings.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/layoutwriter.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/converter.cpp"
	"$<$<NOT:$<BOOL:${QRFL_MINIMAL}>>:${CMAKE_CURRENT_SOURCE_DIR}/aboutdialog.cpp>"
	"$<$<NOT:$<BOOL:${QRFL_MINIMAL}>>:${CMAKE_CURRENT_SOURCE_DIR}/preview.cpp>"
	"$<$<NOT:$<BOOL:${QRFL_MINIMAL}>>:${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp>"
	"$<$<NOT:$<BOOL:${QRFL_MINIMAL}>>:${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc>"
	"$<$<NOT:$<BOOL:${QRFL_MINIMAL}>>:${CMAKE_SOURCE_DIR}/pack/qucsrflayout.rc>"
	"${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
	)

target_compile_definitions( ${PROJECT_NAME}
	PRIVATE
	${QT_DEPRECATED_WARNINGS}
	QRFL_VERSION="${PROJECT_VERSION}"
	QRFL_HOMEPAGE="${PROJECT_HOMEPAGE_URL}"
	QRFL_FUNDING="${QRFL_FUNDING}"
	QRFL_BUGREPORT="${QRFL_BUGREPORT}"
	$<$<BOOL:${QRFL_MINIMAL}>:QRFL_MINIMAL>
	)

target_compile_features( ${PROJECT_NAME}
	PRIVATE
	cxx_std_23
	)

target_compile_options( ${PROJECT_NAME}
	PRIVATE
	$<$<CONFIG:Debug>:-Wall>
	$<$<CONFIG:Debug>:-Wextra>
#	$<$<CONFIG:Debug>:-Weffc++>
#	$<$<CONFIG:Debug>:-Wsuggest-attribute=const>
#	$<$<CONFIG:Debug>:-Wsuggest-attribute=pure>
	)

target_include_directories( ${PROJECT_NAME}
	PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_BINARY_DIR}/generated"
	)

target_link_libraries( ${PROJECT_NAME}
	PRIVATE
	$<$<NOT:$<BOOL:${QRFL_MINIMAL}>>:Qt6::Core>
	$<$<NOT:$<BOOL:${QRFL_MINIMAL}>>:Qt6::Gui>
	$<$<NOT:$<BOOL:${QRFL_MINIMAL}>>:Qt6::OpenGLWidgets>
	$<$<NOT:$<BOOL:${QRFL_MINIMAL}>>:Qt6::Widgets>
	)

set_target_properties( ${PROJECT_NAME} PROPERTIES
	OUTPUT_NAME "qucsrflayout"
#	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
	)

if( NOT QRFL_MINIMAL )
	set_target_properties( ${PROJECT_NAME} PROPERTIES
		AUTOMOC ON
		AUTORCC ON
		AUTOUIC ON
		)
endif( NOT QRFL_MINIMAL )

install(
	TARGETS ${PROJECT_NAME}
	CONFIGURATIONS Release
	RUNTIME DESTINATION "bin" #"${CMAKE_INSTALL_BINDIR}"
	)

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
