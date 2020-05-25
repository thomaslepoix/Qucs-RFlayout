add_custom_target( doc )
include( Latex )

compile_latex_file( "table_orientation" REGISTER_TO "GLOBAL_SCHEMATICS_FILES" )
add_custom_target( "global_schematics" DEPENDS ${GLOBAL_SCHEMATICS_FILES} )
add_dependencies( "doc" "global_schematics" )

compile_latex_file( "topology_mcorn" REGISTER_TO "TOPOLOGY_FILES" )
compile_latex_file( "topology_mcoupled" REGISTER_TO "TOPOLOGY_FILES" )
compile_latex_file( "topology_mcross" REGISTER_TO "TOPOLOGY_FILES" )
compile_latex_file( "topology_mgap" REGISTER_TO "TOPOLOGY_FILES" )
compile_latex_file( "topology_mlin" REGISTER_TO "TOPOLOGY_FILES" )
compile_latex_file( "topology_mmbend" REGISTER_TO "TOPOLOGY_FILES" )
compile_latex_file( "topology_mopen" REGISTER_TO "TOPOLOGY_FILES" )
compile_latex_file( "topology_mrstub" REGISTER_TO "TOPOLOGY_FILES" )
compile_latex_file( "topology_mstep" REGISTER_TO "TOPOLOGY_FILES" )
compile_latex_file( "topology_mtee" REGISTER_TO "TOPOLOGY_FILES" )
compile_latex_file( "topology_mvia" REGISTER_TO "TOPOLOGY_FILES" )
add_custom_target( "topology" DEPENDS ${TOPOLOGY_FILES} )
add_dependencies( "doc" "topology" )

compile_latex_file( "detail_mcorn" REGISTER_TO "DETAIL_FILES" )
compile_latex_file( "detail_mcoupled" REGISTER_TO "DETAIL_FILES" )
compile_latex_file( "detail_mcross" REGISTER_TO "DETAIL_FILES" )
#compile_latex_file( "detail_mgap" REGISTER_TO "DETAIL_FILES" )
compile_latex_file( "detail_mlin" REGISTER_TO "DETAIL_FILES" )
compile_latex_file( "detail_mmbend" REGISTER_TO "DETAIL_FILES" )
#compile_latex_file( "detail_mopen" REGISTER_TO "DETAIL_FILES" )
compile_latex_file( "detail_mrstub" REGISTER_TO "DETAIL_FILES" )
#compile_latex_file( "detail_mstep" REGISTER_TO "DETAIL_FILES" )
compile_latex_file( "detail_mtee" REGISTER_TO "DETAIL_FILES" )
#compile_latex_file( "detail_mvia" REGISTER_TO "DETAIL_FILES" )
add_custom_target( "detail" DEPENDS ${DETAIL_FILES} )
add_dependencies( "doc" "detail" )

compile_latex_file( "oems_mesh_mcorn" REGISTER_TO "OEMS_MESH_FILES" )
compile_latex_file( "oems_mesh_mcoupled" REGISTER_TO "OEMS_MESH_FILES" )
compile_latex_file( "oems_mesh_mcross" REGISTER_TO "OEMS_MESH_FILES" )
compile_latex_file( "oems_mesh_mgap" REGISTER_TO "OEMS_MESH_FILES" )
compile_latex_file( "oems_mesh_mlin" REGISTER_TO "OEMS_MESH_FILES" )
compile_latex_file( "oems_mesh_mmbend" REGISTER_TO "OEMS_MESH_FILES" )
compile_latex_file( "oems_mesh_mopen" REGISTER_TO "OEMS_MESH_FILES" )
compile_latex_file( "oems_mesh_mrstub" REGISTER_TO "OEMS_MESH_FILES" )
compile_latex_file( "oems_mesh_mstep" REGISTER_TO "OEMS_MESH_FILES" )
compile_latex_file( "oems_mesh_mtee" REGISTER_TO "OEMS_MESH_FILES" )
compile_latex_file( "oems_mesh_mvia" REGISTER_TO "OEMS_MESH_FILES" )
compile_latex_file( "oems_mesh_pac" REGISTER_TO "OEMS_MESH_FILES" )
add_custom_target( "oems_mesh" DEPENDS ${OEMS_MESH_FILES} )
add_dependencies( "doc" "oems_mesh" )

install(
	FILES
		${TOPOLOGY_FILES}
		${DETAIL_FILES}
		${OEMS_MESH_FILES}
	DESTINATION "share/doc/qucsrflayout" #"${CMAKE_INSTALL_DOCDIR}/qucsrflayout"
	OPTIONAL
	)

