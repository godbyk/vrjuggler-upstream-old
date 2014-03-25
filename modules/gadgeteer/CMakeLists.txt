cmake_minimum_required(VERSION 2.8.5)
project(Gadgeteer)

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
	set(VPR_LIBRARIES vpr)
else()
	message(FATAL_ERROR "Building Gadgeteer separate from the rest of the build has not yet been implemented!")
	#find_package(VPR REQUIRED) # TODO make this right
	#find_package(CPPDOM REQUIRED)
	#find_package(Boost REQUIRED COMPONENTS filesystem system) # TODO check this.
	#set(VPR_INCLUDE_DIRECTORIES ${VPR_INCLUDE_DIRS})
endif()

include(CTest)

set(GADGET_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${JCCL_INCLUDE_DIRECTORIES} ${GMTL_INCLUDE_DIRS})
if(NOT (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
	set(GADGET_INCLUDE_DIRECTORIES ${GADGET_INCLUDE_DIRECTORIES} PARENT_SCOPE)
endif()

###
# Configuration
###

include_directories(${GADGET_INCLUDE_DIRECTORIES})

if(BUILD_VERSIONED_DIRECTORIES)
	set(GADGET_SHARE_DIR ${CMAKE_INSTALL_DATADIR}/gadgeteer-${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER})
	set(GADGET_LIB_DIR gadgeteer-${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER})
	set(GADGET_INCLUDE_PREFIX ${CMAKE_INSTALL_INCLUDEDIR}/gadgeteer-${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER})
	set(GADGET_VERSION_DOT "${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER}")
	set(GADGET_USE_VERSIONING 1)
else()
	set(GADGET_SHARE_DIR ${CMAKE_INSTALL_DATADIR}/gadgeteer)
	set(GADGET_LIB_DIR gadgeteer)
	set(GADGET_INCLUDE_PREFIX ${CMAKE_INSTALL_INCLUDEDIR})
endif()

add_subdirectory(gadget)

add_subdirectory(drivers)

add_subdirectory(plugins)

install(DIRECTORY cluster gadget plugins
	DESTINATION ${GADGET_INCLUDE_PREFIX}
	COMPONENT gadget-dev
	FILES_MATCHING PATTERN *.h)

install(DIRECTORY data
	DESTINATION ${GADGET_SHARE_DIR}
	COMPONENT gadget-runtime)

install(DIRECTORY samples
	DESTINATION ${GADGET_SHARE_DIR}
	COMPONENT gadget-samples)

install(DIRECTORY tools
	DESTINATION ${GADGET_SHARE_DIR}
	COMPONENT gadget-tools)

install(DIRECTORY test
	DESTINATION ${GADGET_SHARE_DIR}
	COMPONENT gadget-test)

if(BUILD_TESTING)
#	add_subdirectory(test)
endif()


