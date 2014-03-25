cmake_minimum_required(VERSION 2.8.5)
project(VRJuggler)

###
# CMake modules
###
include("${CMAKE_CURRENT_SOURCE_DIR}/../../scripts/cmake/VRJugglerSuiteDefaultOptions.cmake")

###
# Version
###
vrjugglersuite_parse_version_file()

# Since this is the main module, shout this version loud and proud.
set_property(GLOBAL PROPERTY VRJ_MAJOR_VER ${MAJOR_VER_NUMBER})
set_property(GLOBAL PROPERTY VRJ_MINOR_VER ${MINOR_VER_NUMBER})
set_property(GLOBAL PROPERTY VRJ_PATCH_VER ${PATCH_VER_NUMBER})

###
# Dependencies
###

if(TARGET vpr AND TARGET jccl AND TARGET gadget AND TARGET sonix)
	set(GADGET_LIBRARIES gadget)
	set(SNX_LIBRARIES sonix)
	set(JCCL_LIBRARIES jccl)
	set(VPR_LIBRARIES vpr)
else()
	message(FATAL_ERROR "Building VR Juggler separate from the rest of the build has not yet been implemented!")
	#find_package(VPR REQUIRED) # TODO make this right
	#find_package(CPPDOM REQUIRED)
	#find_package(Boost REQUIRED COMPONENTS filesystem system) # TODO check this.
	#set(VPR_INCLUDE_DIRECTORIES ${VPR_INCLUDE_DIRS})
endif()

find_package(Boost REQUIRED COMPONENTS filesystem system program_options)

include(CTest)

set(VRJ_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${GADGET_INCLUDE_DIRECTORIES} ${SNX_INCLUDE_DIRECTORIES})
if(NOT (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
	set(VRJ_INCLUDE_DIRECTORIES ${VRJ_INCLUDE_DIRECTORIES} PARENT_SCOPE)
endif()

###
# Configuration
###

include_directories(${VRJ_INCLUDE_DIRECTORIES})

if(BUILD_VERSIONED_DIRECTORIES)
	set(VRJ_SHARE_DIR ${CMAKE_INSTALL_DATADIR}/vrjuggler-${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER})
	set(VRJ_LIB_DIR vrjuggler-${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER})
	set(VRJ_INCLUDE_PREFIX ${CMAKE_INSTALL_INCLUDEDIR}/vrjuggler-${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER})
	set(VRJ_VERSION_DOT "${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER}")
	set(VRJ_USE_VERSIONING 1)
else()
	set(VRJ_SHARE_DIR ${CMAKE_INSTALL_DATADIR}/vrjuggler)
	set(VRJ_LIB_DIR vrjuggler)
	set(VRJ_INCLUDE_PREFIX ${CMAKE_INSTALL_INCLUDEDIR})
endif()

add_subdirectory(vrj)
add_subdirectory(vrj/Draw)

if(BUILD_JAVA)
	add_subdirectory(vrjconfig)
endif()

install(DIRECTORY vrj
	DESTINATION ${VRJ_INCLUDE_PREFIX}
	COMPONENT vrj-dev
	FILES_MATCHING PATTERN *.h)

install(DIRECTORY data
	DESTINATION ${VRJ_SHARE_DIR}
	COMPONENT vrj-runtime)

install(DIRECTORY samples
	DESTINATION ${VRJ_SHARE_DIR}
	COMPONENT vrj-samples)

install(DIRECTORY tools
	DESTINATION ${VRJ_SHARE_DIR}
	COMPONENT vrj-tools)

install(DIRECTORY test
	DESTINATION ${VRJ_SHARE_DIR}
	COMPONENT vrj-test)

if(BUILD_TESTING)
#	add_subdirectory(test)
endif()


