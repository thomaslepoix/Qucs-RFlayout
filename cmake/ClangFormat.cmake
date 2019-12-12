# INCLUDE : include( ClangFormat )
# COMMAND : add_target_format( ${FILES_TO_FORMAT} )
# RUN     : make format
#
# Add the target in a source directory CMakeLists.txt
#
# Use `make format` to run clang-format on argument files.
################################################################################

macro( add_target_format )

	find_program( FORMAT_PATH clang-format )

	if( FORMAT_PATH )

		message( STATUS "clang-format - code formating             YES " )
		add_custom_target( format
			COMMAND ${FORMAT_PATH} -style=file -i ${ARGV}
			)

	else( FORMAT_PATH )

		message( STATUS "clang-format - code formating             NO " )

	endif( FORMAT_PATH )

endmacro( add_target_format )

