find_package( LATEX COMPONENTS XELATEX )

################################################################################
# compile_latex_file(name
#                    [DESTINATION destination_dir]
#                    [SOURCE source_dir] 
#                    [TEXINPUTS texinputs]
#                    [SUBDIRS subdir1 [subdir2] ...]
#                    [REGISTER_TO var]
#                    [SHELL_ESCAPE]
#                    [VERBOSE]
#                    [MINTED]
#                    )
# [DESTINATION]
#       Directory where output pdf file and byproduct files are created. Default
#       is : "${CMAKE_CURRENT_BINARY_DIR}".
# [SOURCE]
#       Directory where main tex file is located. Default is :
#       "${CMAKE_CURRENT_SOURCE_DIR}".
# [TEXINPUTS]
#       Directories where other files (tex files, images, classes, etc.) are
#       included from. Default contains current directory (at build time) and
#       LaTex system directories. Should be set as long as main tex file
#       includes other files AND you don't execute the build command where the
#       main tex file is located. Or if a tex file includes another file from
#       elsewhere than the main tex file directory. Syntax is : "dir1:dir2:..."
# [SUBDIRS]
#       Directories where other tex files are located. Should be a relative path
#       from a TEXINPUTS location. The purpose of this flag is to create a build
#       tree that correspond to the source tree. For example, if a tex file
#       contains this "\include{chapters/chapter2}", add "chapters" to subdirs.
# [REGISTER_TO]
#       Append output pdf file to var. To the tex file to be compiled, at least
#       one target must DEPENDS on its output file. Avoid making more than one
#       target DEPENDS on one output pdf file, instead create dependencies
#       between other dependant targets and the one that wraps the tex file
#       compilation.
# [SHELL_ESCAPE]
#       Append "--shell-escape" to the LaTex compiler.
# [VERBOSE]
#       Show LaTex compiler output messages.
# [MINTED]
#       Use it only if you use the LaTex package Minted AND you override
#       DESTINATION. Defines \mintedoutputdir to set the Minted package argument
#       "outputdir". So you can include Minted this way :
#       "\usepackage[outputdir=\mintedoutputdir]{minted}"
################################################################################
function( compile_latex_file NAME )
	set( OPTIONS VERBOSE SHELL_ESCAPE MINTED )
	set( ONEVALUEARGS DESTINATION SOURCE TEXINPUTS REGISTER_TO )
	set( MULTIVALUEARGS SUBDIRS )
	cmake_parse_arguments( LATEX
		"${OPTIONS}"
		"${ONEVALUEARGS}"
		"${MULTIVALUEARGS}"
		${ARGN}
		)

	if( NOT LATEX_SOURCE)
		set( LATEX_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}" )
	endif()
	if( NOT LATEX_DESTINATION )
		set( LATEX_DESTINATION "${CMAKE_CURRENT_BINARY_DIR}" )
	endif()
	if( LATEX_SHELL_ESCAPE )
		set( LATEX_SHELL_ESCAPE "--shell-escape" )
	else()
		set( LATEX_SHELL_ESCAPE )
	endif()
	if( LATEX_VERBOSE )
		set( LATEX_VERBOSE "#" )
	else()
		set( LATEX_VERBOSE )
	endif()
	if( LATEX_MINTED )
		set( LATEX_MINTED "\\def\\mintedoutputdir{${LATEX_DESTINATION}}" )
	else()
		set( LATEX_MINTED )
	endif()
	foreach( SUBDIR ${LATEX_SUBDIRS} )
		list( APPEND FULL_SUBDIRS "${LATEX_DESTINATION}/${SUBDIR}" )
	endforeach()

	add_custom_command(
		OUTPUT "${LATEX_DESTINATION}/${NAME}.pdf"
		DEPENDS "${LATEX_SOURCE}/${NAME}.tex"
		BYPRODUCTS
			"${LATEX_DESTINATION}/${NAME}.aux"
			"${LATEX_DESTINATION}/${NAME}.log"
			"${LATEX_DESTINATION}/${NAME}.out"
			"${LATEX_DESTINATION}/${NAME}.run.xml"
			"${LATEX_DESTINATION}/${NAME}.toc"
			"${LATEX_DESTINATION}/${NAME}-blx.bib"
			# Some are probably missing
		COMMAND ${CMAKE_COMMAND} -E make_directory ${LATEX_DESTINATION} ${FULL_SUBDIRS}
		COMMAND ${CMAKE_COMMAND} -E env TEXINPUTS="${LATEX_TEXINPUTS}": 
			${XELATEX_COMPILER}
			"${LATEX_SHELL_ESCAPE}"
			--interaction=nonstopmode
			--output-directory="${LATEX_DESTINATION}"
			"\"${LATEX_MINTED}\\input{${LATEX_SOURCE}/${NAME}.tex}\""
			"${LATEX_VERBOSE}" > /dev/null
		)

	if( LATEX_REGISTER_TO )
		list( APPEND "${LATEX_REGISTER_TO}"
			"${LATEX_DESTINATION}/${NAME}.pdf"
			)
		set( "${LATEX_REGISTER_TO}"
			"${${LATEX_REGISTER_TO}}"
			PARENT_SCOPE
			)
	endif()
endfunction()
