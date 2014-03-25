cmake_minimum_required(VERSION 2.8.5)
project(JCCL)

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

if(TARGET vpr)
	set(VPR_LIBRARIES vpr)
else()
	message(FATAL_ERROR "Building JCCL separate from the rest of the build has not yet been implemented!")
	#find_package(VPR REQUIRED) # TODO make this right
	#find_package(CPPDOM REQUIRED)
	#find_package(Boost REQUIRED COMPONENTS filesystem system) # TODO check this.
	#set(VPR_INCLUDE_DIRECTORIES ${VPR_INCLUDE_DIRS})
endif()

include(CTest)

set(JCCL_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/common ${CMAKE_CURRENT_SOURCE_DIR}/config ${CMAKE_CURRENT_SOURCE_DIR}/rtrc ${CMAKE_CURRENT_BINARY_DIR}/common ${VPR_INCLUDE_DIRECTORIES})
if(NOT (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
	set(JCCL_INCLUDE_DIRECTORIES ${JCCL_INCLUDE_DIRECTORIES} PARENT_SCOPE)
endif()

###
# Configuration
###


include_directories(${JCCL_INCLUDE_DIRECTORIES})

if(BUILD_VERSIONED_DIRECTORIES)
	set(JCCL_SHARE_DIR ${CMAKE_INSTALL_DATADIR}/jccl-${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER})
	set(JCCL_INCLUDE_PREFIX ${CMAKE_INSTALL_INCLUDEDIR}/jccl-${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER})
else()
	set(JCCL_SHARE_DIR ${CMAKE_INSTALL_DATADIR}/jccl)
	set(JCCL_INCLUDE_PREFIX ${CMAKE_INSTALL_INCLUDEDIR})
endif()

add_subdirectory(common/jccl)
add_subdirectory(data)
add_subdirectory(tools/xmlupdate)

###
# Library Build
###

set(SOURCES
	common/jccl/jcclmain.cpp
	common/jccl/Util/Version.cpp

	config/jccl/Config/ConfigDefinition.cpp
	config/jccl/Config/ConfigDefinitionReader.cpp
	config/jccl/Config/ConfigDefinitionRepository.cpp
	config/jccl/Config/ConfigElement.cpp
	config/jccl/Config/Configuration.cpp
	config/jccl/Config/ElementFactory.cpp
	config/jccl/Config/ParseUtil.cpp
	config/jccl/Config/PropertyDefinition.cpp

	rtrc/jccl/RTRC/ConfigElementHandler.cpp
	rtrc/jccl/RTRC/ConfigManager.cpp
	rtrc/jccl/RTRC/DepChecker.cpp
	rtrc/jccl/RTRC/DependencyManager.cpp)

if(MSVC)
	list(APPEND SOURCES jccl.rc)
endif()

set(HEADERS
	common/jccl/AutoLink.h
	common/jccl/jcclConfig.h
	common/jccl/Plugins/PluginConfig.h
	common/jccl/Util/Debug.h
	common/jccl/Util/Version.h

	config/jccl/Config/ConfigDefinition.h
	config/jccl/Config/ConfigDefinitionPtr.h
	config/jccl/Config/ConfigDefinitionReader.h
	config/jccl/Config/ConfigDefinitionRepository.h
	config/jccl/Config/ConfigElement.h
	config/jccl/Config/ConfigElementPtr.h
	config/jccl/Config/ConfigTokens.h
	config/jccl/Config/Configuration.h
	config/jccl/Config/ElementFactory.h
	config/jccl/Config/ParseUtil.h
	config/jccl/Config/PropertyDefinition.h

	rtrc/jccl/RTRC/ConfigElementHandler.h
	rtrc/jccl/RTRC/ConfigManager.h
	rtrc/jccl/RTRC/DepChecker.h
	rtrc/jccl/RTRC/DependencyManager.h
	rtrc/jccl/RTRC/RemoteReconfig.h
)

add_definitions(-D_JCCL_BUILD_ "-DJCCL_ROOT_DIR=\"${CMAKE_INSTALL_PREFIX}\"" "-DJCCL_SHARE_DIR=\"${JCCL_SHARE_DIR}\"")

add_library(jccl SHARED ${HEADERS} ${SOURCES})
target_link_libraries(jccl
	${VPR_LIBRARIES})

set_target_properties(jccl PROPERTIES FOLDER "${VRJUGGLERSUITE_CORELIB_PROJECT_FOLDER}")
vrjugglersuite_set_versioned_library_output_name(jccl)

install(TARGETS jccl EXPORT jcclexport
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT jccl-runtime
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT jccl-runtime
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT jccl-dev)

install(DIRECTORY common/jccl config/jccl rtrc/jccl
	DESTINATION ${JCCL_INCLUDE_PREFIX}
	COMPONENT jccl-dev
	FILES_MATCHING PATTERN *.h)

add_subdirectory(config)

if(BUILD_TESTING)
#	add_subdirectory(test)
endif()


