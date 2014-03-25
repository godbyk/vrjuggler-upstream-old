cmake_minimum_required(VERSION 2.8.5)
project(Tweek)

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

if(BUILD_JAVA)
	option(TWEEK_BUILD_EXTENSIONS "Build Tweek java extensions" ON)
endif()

find_package(GMTL REQUIRED)
if(TARGET vpr)
	set(VPR_LIBRARIES vpr)
else()
	message(FATAL_ERROR "Building Tweek separate from the rest of the build has not yet been implemented!")
	#find_package(VPR REQUIRED) # TODO make this right
	#find_package(CPPDOM REQUIRED)
	#find_package(Boost REQUIRED COMPONENTS filesystem system) # TODO check this.
	#set(VPR_INCLUDE_DIRECTORIES ${VPR_INCLUDE_DIRS})
endif()

include(CTest)

set(TWEEK_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${JCCL_INCLUDE_DIRECTORIES} ${GMTL_INCLUDE_DIRS})
if(NOT (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
	set(TWEEK_INCLUDE_DIRECTORIES ${TWEEK_INCLUDE_DIRECTORIES} PARENT_SCOPE)
endif()

###
# Configuration
###

include_directories(${TWEEK_INCLUDE_DIRECTORIES})

set(TWEEK_IDL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tweek/idl)
set(TWEEK_IDL_NAMES BeanDeliverySubject Observer Subject SubjectManager)

if(BUILD_VERSIONED_DIRECTORIES)
	set(TWEEK_SHARE_DIR ${CMAKE_INSTALL_DATADIR}/tweek-${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER})
	set(TWEEK_LIB_DIR tweek-${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER})
	set(TWEEK_INCLUDE_PREFIX ${CMAKE_INSTALL_INCLUDEDIR}/tweek-${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER})
	set(TWEEK_VERSION_DOT "${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER}")
	set(TWEEK_USE_VERSIONING 1)
else()
	set(TWEEK_SHARE_DIR ${CMAKE_INSTALL_DATADIR}/tweek)
	set(TWEEK_LIB_DIR tweek)
	set(TWEEK_INCLUDE_PREFIX ${CMAKE_INSTALL_INCLUDEDIR})
endif()

if(OMNIORB4_FOUND)
	add_subdirectory(tweek)
endif()

if(BUILD_JAVA)
	find_package(IDLJ)
	add_subdirectory(java)
	if(TWEEK_BUILD_EXTENSIONS)
		add_subdirectory(extensions/java)
	endif()
endif()

install(DIRECTORY tweek
	DESTINATION ${TWEEK_INCLUDE_PREFIX}
	COMPONENT tweek-dev
	FILES_MATCHING PATTERN *.h)

install(DIRECTORY data
	DESTINATION ${TWEEK_SHARE_DIR}
	COMPONENT tweek-runtime)

if(BUILD_TESTING)
#	add_subdirectory(test)
endif()


