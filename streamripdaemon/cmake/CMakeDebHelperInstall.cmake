# This script is used internally by CMakeDebHelper.
# It is run at CPack-Time and copies the files generated by the debhelpers to the right place.

if( NOT CPACK_DEBIAN_PACKAGE_NAME )
	string( TOLOWER "${CPACK_PACKAGE_NAME}" CPACK_DEBIAN_PACKAGE_NAME )
endif()

# Copy all generated files where the packing will happen,
# exclude the DEBIAN-directory.
file( COPY
	"${CPACK_OUTPUT_FILE_PREFIX}/debian/${CPACK_DEBIAN_PACKAGE_NAME}/"
	DESTINATION "${CMAKE_CURRENT_BINARY_DIR}" 
	PATTERN DEBIAN EXCLUDE
) 
