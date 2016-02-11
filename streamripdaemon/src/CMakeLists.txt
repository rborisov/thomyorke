find_package(GLIB2 REQUIRED)

set (daemon_src daemon.c streamripper.c)

# Make build flags compiler specific
if (CMAKE_COMPILER_IS_GNUCC)
	if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set (CMAKE_C_FLAGS "-D_REETRANT -D__UNIX__ -ggdb -fPIC -Wall -Wextra -pedantic -O0")
	elseif( CMAKE_BUILD_TYPE STREQUAL "Release" )
        set (CMAKE_C_FLAGS "-D_REETRANT -D__UNIX__ -DNDEBUG -fPIC -Wall -Wextra -pedantic -O3")
	endif ()
endif (CMAKE_COMPILER_IS_GNUCC)

MESSAGE(STATUS "GLIB2_INCLUDE_DIRS: " ${GLIB2_INCLUDE_DIRS})
set(STREAMRIPPER_SRC_PATH "${PROJECT_SOURCE_DIR}/../libstreamripper/src/")
set(CONFIG_LIB_PATH "${PROJECT_SOURCE_DIR}/../libconfig/")
include_directories(${STREAMRIPPER_SRC_PATH} ${GLIB2_INCLUDE_DIRS} "${PROJECT_SOURCE_DIR}/../")

add_executable (streamripdaemon ${daemon_src})

# The rule to install daemon binary
install (TARGETS streamripdaemon
	RUNTIME
	DESTINATION bin)
