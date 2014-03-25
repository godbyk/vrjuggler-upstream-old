cmake_minimum_required(VERSION 2.8.5)
project(Sonix)

###
# CMake modules
###
include("${CMAKE_CURRENT_SOURCE_DIR}/../../scripts/cmake/VRJugglerSuiteDefaultOptions.cmake")

###
# Version
###
vrjugglersuite_parse_version_file()

###
# Dependencies
###

find_package(GMTL REQUIRED)
if(TARGET vpr AND TARGET jccl)
	set(JCCL_LIBRARIES jccl)
else()
	message(FATAL_ERROR "Building Sonix separate from the rest of the build has not yet been implemented!")
	#find_package(VPR REQUIRED) # TODO make this right
	#find_package(CPPDOM REQUIRED)
	#find_package(Boost REQUIRED COMPONENTS filesystem system) # TODO check this.
	#set(VPR_INCLUDE_DIRECTORIES ${VPR_INCLUDE_DIRS})
endif()

include(CTest)

set(SNX_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${JCCL_INCLUDE_DIRECTORIES} ${GMTL_INCLUDE_DIRS})
if(NOT (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
	set(SNX_INCLUDE_DIRECTORIES ${SNX_INCLUDE_DIRECTORIES} PARENT_SCOPE)
endif()

###
# Configuration
###

include_directories(${SNX_INCLUDE_DIRECTORIES})

if(BUILD_VERSIONED_DIRECTORIES)
	set(SNX_SHARE_DIR ${CMAKE_INSTALL_DATADIR}/sonix-${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER})
	set(SNX_LIB_DIR sonix-${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER})
	set(SNX_INCLUDE_PREFIX ${CMAKE_INSTALL_INCLUDEDIR}/sonix-${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER})
else()
	set(SNX_SHARE_DIR ${CMAKE_INSTALL_DATADIR})
	set(SNX_LIB_DIR sonix)
	set(SNX_INCLUDE_PREFIX ${CMAKE_INSTALL_INCLUDEDIR})
endif()

add_subdirectory(snx)
add_subdirectory(plugins)

install(DIRECTORY snx
	DESTINATION ${SNX_INCLUDE_PREFIX}
	COMPONENT sonix-dev
	FILES_MATCHING PATTERN *.h)

if(BUILD_TESTING)
#	add_subdirectory(test)
endif()


