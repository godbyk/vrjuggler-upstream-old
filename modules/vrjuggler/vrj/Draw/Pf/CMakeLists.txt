add_definitions(-D_VRJ_PF_BUILD_)

set(HEADERS
	App.h
	BasicSimulator.h
	Config.h
	DrawManager.h
	InputHandler.h
	PfApp.h
	PfDrawManager.h
	PfUtil.h
	SimInterface.h
	SimInterfaceFactory.h
	SimInterfacePtr.h
	Util.h)

set(SOURCES
	App.cpp
	BasicSimulator.cpp
	DrawManager.cpp
	InputHandler.cpp
	SimInterface.cpp
	SimInterfaceFactory.cpp
	Util.cpp

	../../../vrj_pf.rc)

find_package(Performer REQUIRED)
include_directories(${PERFORMER_INCLUDE_DIRS})

add_library(vrj_pf SHARED ${HEADERS} ${SOURCES})
target_link_libraries(vrj_pf
	vrj
	${PERFORMER_LIBRARIES}
	${PERFORMER_PFUI_LIBRARY}
	${PERFORMER_PFDU_UTIL_LIBRARY})

set_target_properties(vrj_pf PROPERTIES FOLDER "${VRJUGGLERSUITE_CORELIB_PROJECT_FOLDER}")

vrjugglersuite_set_versioned_library_output_name(vrj_pf)

install(TARGETS vrj_pf EXPORT vrjexport
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT vrj-runtime
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT vrj-runtime
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT vrj-dev)

