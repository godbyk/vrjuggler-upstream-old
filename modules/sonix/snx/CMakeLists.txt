
add_definitions(-D_SNX_BUILD_ "-DSNX_SHARE_DIR=\"${SNX_SHARE_DIR}\"")

set(HEADERS
	AutoLink.h
	Endian.h
	ISoundImplementation.h
	PluginConfig.h
	snxConfig.h
	sonix.h
	SoundAPIInfo.h
	SoundFactory.h
	SoundHandle.h
	SoundImplementation.h
	SoundInfo.h
	StubSoundImplementation.h
	Util/Debug.h
	Util/Version.h)

set(SOURCES
	snxmain.cpp
	sonix.cpp
	SoundFactory.cpp
	SoundHandle.cpp
	SoundImplementation.cpp
	StubSoundImplementation.cpp
	Util/Version.cpp)

if(MSVC)
	list(APPEND SOURCES ../sonix.rc)
endif()


configure_file("${CMAKE_CURRENT_SOURCE_DIR}/snxParam.h.in" "${CMAKE_CURRENT_BINARY_DIR}/snxParam.h")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/snxDefines.h.cmake_in" "${CMAKE_CURRENT_BINARY_DIR}/snxDefines.h")
vrjugglersuite_create_version_rc()

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/snxParam.h" "${CMAKE_CURRENT_BINARY_DIR}/snxDefines.h"
	DESTINATION ${SNX_INCLUDE_PREFIX}/snx
	COMPONENT sonix-dev)

add_library(sonix SHARED ${HEADERS} ${SOURCES})
target_link_libraries(sonix
	${JCCL_LIBRARIES})

set_target_properties(sonix PROPERTIES FOLDER "${VRJUGGLERSUITE_CORELIB_PROJECT_FOLDER}")

vrjugglersuite_set_versioned_library_output_name(sonix)

install(TARGETS sonix EXPORT sonixexport
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT sonix-runtime
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT sonix-runtime
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT sonix-dev)

