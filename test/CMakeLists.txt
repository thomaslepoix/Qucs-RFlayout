#######################################################################UNITTESTS

include( Catch )

set( QUCS-RF-LAYOUT_TESTS
	"${CMAKE_SOURCE_DIR}/test/unit/test.cpp"
	"${CMAKE_SOURCE_DIR}/test/unit/test_schparser.cpp"
	)

add_executable( unittest EXCLUDE_FROM_ALL
	${QUCS-RF-LAYOUT_TESTS}
	${QUCS-RF-LAYOUT_SRCS}
	)

target_compile_definitions( unittest
	PRIVATE
	${QT_DEPRECATED_WARNINGS}
	-DQRFL_UNITTEST
	)

target_compile_features( unittest
	PRIVATE
	cxx_std_11
	)

target_compile_options( unittest
	PRIVATE
	$<$<CONFIG:Debug>:-Wall>
	$<$<CONFIG:Debug>:-Wextra>
	$<$<CONFIG:Debug>:-fexceptions>
	)

target_include_directories( unittest
	PRIVATE
	"${CMAKE_SOURCE_DIR}/src"
	)

target_link_libraries( unittest
	Catch2::Catch
	)

qt5_use_modules( unittest
	Core
	Gui
	OpenGL
	)

set_target_properties( unittest PROPERTIES
	OUTPUT_NAME "unittest_qucsrflayout"
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/out"
	)

#######################################################################RUN_TESTS

include( CTest )

add_custom_target( check
	VERBATIM
	COMMAND ${FIXED_SHELL}
	"echo -e \"[----] \\033[36mRunning tests\\033[0m\""
	USES_TERMINAL
	COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
	DEPENDS unittest
	)

add_custom_target( checkall
	VERBATIM
	COMMAND ${FIXED_SHELL}
	"echo -e \"[----] \\033[36mRunning tests\\033[0m\""
	USES_TERMINAL
	COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -V
	DEPENDS unittest
	)

add_test( NAME Unittest
	COMMAND ${FIXED_SHELL}
	"$<TARGET_FILE:unittest> -s --use-colour=yes 2> /dev/null"
	)

