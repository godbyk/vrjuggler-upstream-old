add_definitions(-D_VRJ_D3D_BUILD_)

set(HEADERS
	App.h
	BasicSimulator.h
	Config.h
	DrawManager.h
	DrawManager.h
	SimInterface.h
	SimInterfaceFactory.h
	SimInterfacePtr.h
	Window.h)

set(SOURCES
	App.cpp
	BasicSimulator.cpp
	DrawManager.cpp
	SimInterface.cpp
	SimInterfaceFactory.cpp
	Window.cpp

	../../../vrj_d3d.rc)

find_package(DirectX REQUIRED)
if(NOT (DIRECTX_D3D9_LIBRARY AND DIRECTX_D3DX9_LIBRARY AND DIRECTX_D3DXOF_LIBRARY))
	message(FATAL_ERROR "Direct3D not found but Direct3D draw manager enabled!")
endif()
include_directories(${DIRECTX_INCLUDE_DIRS})

add_library(vrj_d3d SHARED ${HEADERS} ${SOURCES})
target_link_libraries(vrj_d3d
	vrj
	${DIRECTX_D3DXOF_LIBRARY}
	${DIRECTX_DXGUID_LIBRARY}
	${DIRECTX_D3DX9_LIBRARIES}
	${DIRECTX_D3D9_LIBRARY}
	winmm)

set_target_properties(vrj_d3d PROPERTIES FOLDER "${VRJUGGLERSUITE_CORELIB_PROJECT_FOLDER}")

vrjugglersuite_set_versioned_library_output_name(vrj_d3d)

install(TARGETS vrj_d3d EXPORT vrjexport
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT vrj-runtime
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT vrj-runtime
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT vrj-dev)

