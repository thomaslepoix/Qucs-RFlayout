# INCLUDE : include( Package )
# COMMAND : add_target_dist( ${OPTIONAL_FILES_TO_IGNORE} )
# RUN     : make dist
#
# Add the target in the top CMakeLists.txt of the project
#
# Use `make dist` to archive the whole project directory except argument files
#   and `make dist` command artifacts.
# The projecte is archived at its current state so if you want to include
#   binaries, compilation objects, documentation, etc., run the appropriate
#   command before (`make`, `make doc`, etc.).
################################################################################

macro( add_target_dist )

	#make package_source
	set( CPACK_SOURCE_GENERATOR TXZ )
	set( CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}.src" )
	set( CPACK_OUTPUT_FILE_PREFIX "${CMAKE_SOURCE_DIR}/out" )
	set( CPACK_SOURCE_IGNORE_FILES
		"${CPACK_OUTPUT_FILE_PREFIX}/${CPACK_SOURCE_PACKAGE_FILE_NAME}*"
		"${CMAKE_BINARY_DIR}/_CPack_Packages"
		${ARGV}
		)
	include( CPack )

	add_custom_target( dist
		COMMAND ${CMAKE_MAKE_PROGRAM} package_source
		VERBATIM
		)

endmacro( add_target_dist )

