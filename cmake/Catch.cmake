# INCLUDE : include( Catch )
# COMMAND : target_link_libraries( unittest Catch2::Catch )
# RUN     : make unittest
# CTEST   : add_test( NAME Unittest COMMAND $<TARGET_FILE:unittest> <args> )
#
# Create the unittest target in the unittest CMakeLists.txt.
# Register unittest target in CTest in the test CMakeLists.txt.
#
# Create a check target that run CTest and depends on unittest target.
################################################################################

set( CATCH_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/lib/catch2" )

add_library( Catch2::Catch
	IMPORTED
	INTERFACE
	)

set_target_properties( Catch2::Catch PROPERTIES
	INTERFACE_INCLUDE_DIRECTORIES "${CATCH_INCLUDE_DIR}"
	)

