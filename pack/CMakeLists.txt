#set( CPACK_OUTPUT_FILE_PREFIX "${CMAKE_SOURCE_DIR}/out" )

if( UNIX AND NOT APPLE )
	set( CPACK_GENERATOR TGZ TBZ2 TXZ DEB )
	find_program( RPMBUILD rpmbuild )
	if( RPMBUILD )
		message( STATUS "Found rpmbuild: ${RPMBUILD}" )
		set( CPACK_GENERATOR ${CPACK_GENERATOR} RPM )
	else( RPMBUILD )
		message( STATUS "Not found rpmbuild: RPM package won't be generated" )
	endif( RPMBUILD )
endif( UNIX AND NOT APPLE )

set( CPACK_STRIP_FILES "bin/qucsrflayout" )

set( CPACK_PACKAGE_NAME    "qucsrflayout" )
set( CPACK_PACKAGE_VERSION "${PROJECT_VERSION}" )
set( CPACK_PACKAGE_VENDOR  "Thomas Lepoix <thomas.lepoix@protonmail.ch>" )
set( CPACK_PACKAGE_CONTACT "Thomas Lepoix <thomas.lepoix@protonmail.ch>" )
set( CPACK_PACKAGE_FILE_NAME
	"${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_HOST_SYSTEM_PROCESSOR}"
	)

#set( CPACK_PACKAGE_HOMEPAGE_URL "https://github.com/thomaslepoix/Qucs-RFlayout" )
#set( CPACK_PACKAGE_DESCRIPTION_SUMMARY "A tool to produce layout from qucs RF schematics (microstrip only for now)" )

set( CPACK_DEBIAN_FILE_NAME DEB-DEFAULT )
set( CPACK_DEBIAN_PACKAGE_CONTROL_STRICT_PERMISSION TRUE )
set( CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/thomaslepoix/Qucs-RFlayout" )
set( CPACK_DEBIAN_PACKAGE_SECTION  "electronics" )
set( CPACK_DEBIAN_PACKAGE_SUGGESTS "qucs, kicad, pcb-rnd" )
set( CPACK_DEBIAN_PACKAGE_ENHANCES "qucs" )
set( CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON )

set( CPACK_RPM_FILE_NAME RPM-DEFAULT )
set( CPACK_RPM_PACKAGE_LICENSE  "GPL-2.0" )
set( CPACK_RPM_PACKAGE_URL      "https://github.com/thomaslepoix/Qucs-RFlayout" )
set( CPACK_RPM_PACKAGE_GROUP    "Applications/Engineering" )
set( CPACK_RPM_PACKAGE_SUGGESTS "qucs, kicad, pcb-rnd" )

include( CPack )

