add_definitions(-D_VRJ_OGL_BUILD_)

set(HEADERS
	../OpenGL/App.h
	../OpenGL/ContextData.h
	../OpenGL/DrawManager.h
	../OpenGL/ProcApp.h
	../OpenGL/UserData.h
	../OpenGL/Window.h
	../OpenGL/WindowPtr.h
	App.h
	BasicSimulator.h
	Config.h
	ContextData.h
	DrawHeadFunctors.h
	DrawManager.h
	DrawObjectFunctor.h
	DrawWandFunctors.h
	ExtensionLoader.h
	Pipe.h
	ProcApp.h
	SimInterfaceFactory.h
	SimInterface.h
	SimInterfacePtr.h
	UserData.h
	WindowCocoa.h
	Window.h
	WindowPtr.h
	WindowXWin.h)

set(OPENSG_HEADERS
	../OpenSG/App.h)
source_group(OpenSG FILES ${OPENSG_HEADERS})

set(OSG_HEADERS
	../OSG/App.h
	../OSG/AppPager.h
	../OSG/AppViewer.h)
source_group(OSG FILES ${OSG_HEADERS})

set(SOURCES
	App.cpp
	BasicSimulator.cpp
	DrawAxesFunctorsCore.cpp
	DrawAxesFunctors.cpp
	DrawHeadFunctorsCore.cpp
	DrawHeadFunctors.cpp
	DrawManager.cpp
	DrawWandFunctors.cpp
	DrawWandFunctorsCore.cpp
	DrawWandFunctors.cpp
	ExtensionLoader.cpp
	ExtensionLoaderGL.cpp
	ExtensionLoaderGLCore.cpp
	Pipe.cpp
	ProcApp.cpp
	SimInterface.cpp
	SimInterfaceFactory.cpp
	UserData.cpp
	Window.cpp

	../../../vrj_ogl.rc)

if(WIN32)
	list(APPEND SOURCES
		ExtensionLoaderWGL.cpp
		WindowWin32.cpp)
	list(APPEND HEADERS
		ExtensionLoaderWGL.h
		WindowWin32.h)
elseif(BUILD_WITH_COCOA)
	list(APPEND SOURCES 
		VRJOpenGLView.mm
		WindowCocoa.mm)
	list(APPEND HEADERS
		VRJOpenGLView.h
		WindowCocoa.h)
else()
	list(APPEND SOURCES
		ExtensionLoaderGLX.cpp
		WindowXWin.cpp)
	list(APPEND HEADERS
		ExtensionLoaderGLX.h
		WindowXWin.h)
endif()

# TODO: this may link with the wrong (framework) versions of OpenGL on a Mac X11 build
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

add_library(vrj_ogl SHARED ${HEADERS} ${SOURCES} ${OPENSG_HEADERS} ${OSG_HEADERS})
target_link_libraries(vrj_ogl
	vrj
	${OPENGL_LIBRARIES})

set_target_properties(vrj_ogl PROPERTIES FOLDER "${VRJUGGLERSUITE_CORELIB_PROJECT_FOLDER}")

vrjugglersuite_set_versioned_library_output_name(vrj_ogl)

install(TARGETS vrj_ogl EXPORT vrjexport
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT vrj-runtime
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT vrj-runtime
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT vrj-dev)

