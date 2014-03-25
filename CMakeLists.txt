cmake_minimum_required(VERSION 2.8.5)
project(VRJugglerSuite)


###
# Configuration
###
include(CTest)
include(scripts/cmake/VRJugglerSuiteDefaultOptions.cmake)

###
# Recurse into subdirectories
###
add_subdirectory(modules)

###
# Version
###
set(CPACK_PACKAGE_VENDOR "Iowa State University")
set(CPACK_PACKAGE_CONTACT "Ryan Pavlik <rpavlik@iastate.edu>")
get_property(CPACK_PACKAGE_VERSION_MAJOR GLOBAL PROPERTY VRJ_MAJOR_VER)
get_property(CPACK_PACKAGE_VERSION_MINOR GLOBAL PROPERTY VRJ_MINOR_VER)
get_property(CPACK_PACKAGE_VERSION_PATCH GLOBAL PROPERTY VRJ_PATCH_VER)
set(CPACK_PACKAGE_VERSION
	"${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

message(STATUS "")
message(STATUS "VR Juggler Suite version ${CPACK_PACKAGE_VERSION} successfully configured!")
