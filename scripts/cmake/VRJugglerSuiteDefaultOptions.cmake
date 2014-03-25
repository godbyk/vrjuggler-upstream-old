
if(__juggler_suite_default_options)
	return()
endif()
set(__juggler_suite_default_options YES)

get_filename_component(VRJUGGLERSUITE_MODULE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
list(APPEND CMAKE_MODULE_PATH "${VRJUGGLERSUITE_MODULE_DIR}")

# GNUInstallDirs added in CMake 2.8.5 and makes our lives easier
include(GNUInstallDirs)
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
endif()
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})
endif()
if(NOT SHARE_OUTPUT_DIRECTORY)
	set(SHARE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_DATADIR})
endif()

if(WIN32)
	set(DEFAULT_VERSIONED OFF)
else()
	set(DEFAULT_VERSIONED ON)
endif()
option(BUILD_VERSIONED_DIRECTORIES "Should we version the directories for plugins and data?" ${DEFAULT_VERSIONED})

# Java support added in CMake 2.8.6
if(CMAKE_VERSION VERSION_GREATER 2.8.5)
	find_package(Java)
	find_package(IDLJ)
	if(JAVA_FOUND AND IDLJ_FOUND)
		set(BUILD_JAVA_DEFAULT ON)
	else()
		set(BUILD_JAVA_DEFAULT OFF)
	endif()
	option(BUILD_JAVA "Should we build the Java components?" ${BUILD_JAVA_DEFAULT})
else()
	set(BUILD_JAVA OFF)
endif()

if(BUILD_JAVA)
	if(JAVA_FOUND AND IDLJ_FOUND)
		include(UseJava)
	else()
		message(FATAL_ERROR "BUILD_JAVA is on, but Java wasn't found!")
	endif()
endif()

if(APPLE)
	option(BUILD_WITH_COCOA "Should we build with Cocoa (Mac OS X native) code? (Alternative is X11)" ON)
endif()

if(MSVC)
	option(BUILD_WITHOUT_COMMON_WARNINGS "Should we disable some distracting build warnings?" ON)
	if(BUILD_WITHOUT_COMMON_WARNINGS)
		# Disable some warnings
		# 4275: non dll-interface class used as base for dll-interface class
		# 4251: needs to have dll-interface to be used by clients of class
		# 4290: C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4275 /wd4251 /wd4290")

		# Deprecation warnings for strerror, etc.
		add_definitions(-D_CRT_SECURE_NO_WARNINGS)

		# Warning related to checked iterators
		add_definitions(-D_SCL_SECURE_NO_WARNINGS)
	endif()
endif()

if(MSVC)
	option(BUILD_WITH_PROJECT_FOLDERS
		"Use project folders in build system - not compatible with Visual C++ Express editions!"
		OFF)
else()
	set(BUILD_WITH_PROJECT_FOLDERS ON)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ${BUILD_WITH_PROJECT_FOLDERS})

set(VRJUGGLERSUITE_CORELIB_PROJECT_FOLDER "Core VR Juggler libraries")
set(VRJUGGLERSUITE_META_PROJECT_FOLDER "Convenience targets")

set(CPACK_PACKAGE_VENDOR "Iowa State University")
set(CPACK_PACKAGE_CONTACT "Ryan Pavlik <rpavlik@iastate.edu>")

if(WIN32)
	add_definitions(-DCPPDOM_DYN_LINK -DWIN32 -D_WIN32_WINNT=0x0501)
	if(MSVC)
		set(BOOST_DEFAULT_DYNLINK ON)
	else()
		# MXE/MinGW or similar
		set(BOOST_DEFAULT_DYNLINK OFF)
		add_definitions(-D_SIGSET_T_)
	endif()
	option(BUILD_WITH_DYNAMIC_BOOST_LIBRARIES "Build against the dynamic libraries of Boost" ${BOOST_DEFAULT_DYNLINK})
	if(BUILD_WITH_DYNAMIC_BOOST_LIBRARIES)
		add_definitions(-DBOOST_ALL_DYN_LINK)
	endif()
endif()

function(vrjugglersuite_create_version_rc)
	configure_file("${VRJUGGLERSUITE_MODULE_DIR}/version.rc.cmake_in" "${CMAKE_CURRENT_BINARY_DIR}/version.rc")
endfunction()

function(vrjugglersuite_set_versioned_library_output_name _target)
	if(WIN32)
		set(_vertag ${MAJOR_VER_NUMBER}_${MINOR_VER_NUMBER}_${PATCH_VER_NUMBER})
	else()
		set(_vertag ${MAJOR_VER_NUMBER}_${MINOR_VER_NUMBER})
	endif()
	set_property(TARGET ${_target}
		PROPERTY OUTPUT_NAME ${_target}-${_vertag})
	set_property(TARGET ${_target}
		PROPERTY OUTPUT_NAME_DEBUG ${_target}_d-${_vertag})
endfunction()

function(vrjugglersuite_parse_version_file)
	set(_version_file "${CMAKE_CURRENT_SOURCE_DIR}/VERSION")
	if(EXISTS "${_version_file}")
		file(READ "${_version_file}" _version_contents)
	endif()
	
	set(_version_regex "^([0-9]+).([0-9]+).([0-9]+)")
	string(REGEX
		MATCH
		"${_version_regex}"
		_dummy
		"${_version_contents}")
	if(_dummy)
		set(CPACK_PACKAGE_VERSION_MAJOR "${CMAKE_MATCH_1}" PARENT_SCOPE)
		set(CPACK_PACKAGE_VERSION_MINOR "${CMAKE_MATCH_2}" PARENT_SCOPE)
		set(CPACK_PACKAGE_VERSION_PATCH "${CMAKE_MATCH_3}" PARENT_SCOPE)
		set(MAJOR_VER_NUMBER "${CMAKE_MATCH_1}" PARENT_SCOPE)
		set(MINOR_VER_NUMBER "${CMAKE_MATCH_2}" PARENT_SCOPE)
		set(PATCH_VER_NUMBER "${CMAKE_MATCH_3}" PARENT_SCOPE)

		set(CPACK_PACKAGE_VERSION
			"${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3}" PARENT_SCOPE)

		math(EXPR VER_NUMBER "${CMAKE_MATCH_1} * 1000000 + ${CMAKE_MATCH_2} * 1000 + ${CMAKE_MATCH_3}")
		set(VER_NUMBER "${VER_NUMBER}" PARENT_SCOPE)
		set(VER_STRING "\"${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3}\"" PARENT_SCOPE)
		message(STATUS "")
		message(STATUS "Configuring ${PROJECT_NAME} ${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3}")

	else()
		message(FATAL_ERROR "Could not parse VERSION!")
	endif()

endfunction()


# Copy files over to the right spot in build tree
# _varname: variable name to append the destination file's name to (for a custom target dependency)
# _dest: Destination directory: will be relative to CMAKE_BINARY_DIR and the install prefix
# _component: The install component that this will be installed with
# All other arguments are files, to be copied into the same destination (flattened)
function(vrjugglersuite_copy_and_install _varname _dest _component)
	foreach(_src ${ARGN})
		get_filename_component(_srcname "${_src}" NAME)
		install(FILES "${_src}"
			DESTINATION "${_dest}" COMPONENT "${_component}")
		set(DESTFILE "${CMAKE_BINARY_DIR}/${_dest}/${_srcname}")
		list(APPEND ${_varname} "${DESTFILE}")

		add_custom_command(OUTPUT "${DESTFILE}"
			COMMAND
			"${CMAKE_COMMAND}" -E copy_if_different "${_src}" "${DESTFILE}"
			DEPENDS
			"${_src}"
			COMMENT "Copying ${_srcname} to ${_dest} in build tree"
			VERBATIM)
	endforeach()
	set(${_varname} ${${_varname}} PARENT_SCOPE)
endfunction()
