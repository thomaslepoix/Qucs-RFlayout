# INCLUDE : include( Latex )
# COMMAND : add_latex_target( ${INPUT_DIR} ${NAME} )
################################################################################

find_package( LATEX COMPONENTS XELATEX )

if( XELATEX_COMPILER )

	message( STATUS "Found xelatex: ${XELATEX_COMPILER}" )
	macro( add_latex_target DIR NAME )
		add_custom_target( "${NAME}"
			COMMAND ${XELATEX_COMPILER} --shell-escape --interaction=nonstopmode "${DIR}/${NAME}.tex" > /dev/null
			COMMENT "${NAME}"
			)
		add_dependencies( doc "${NAME}" )
	endmacro( add_latex_target DIR NAME )

else( XELATEX_COMPILER )

	message( STATUS "Not found xelatex: Latex documents won't be generated" )
	macro( add_latex_target DIR NAME )
	endmacro( add_latex_target DIR NAME )

endif( XELATEX_COMPILER )
