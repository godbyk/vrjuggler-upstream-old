
add_definitions(-D_VRJ_BUILD_ "-DVJ_SHARE_DIR=\"${VRJ_SHARE_DIR}\"" "-DVJ_ROOT_DIR=\"${CMAKE_INSTALL_PREFIX}\"")

set(HEADERS
	AutoLink.h
	Display/CameraProjection.h
	Display/CameraProjectionPtr.h
	Display/DisplayExceptions.h
	Display/Display.h
	Display/DisplayManager.h
	Display/DisplayPtr.h
	Display/Frustum.h
	Display/Projection.h
	Display/ProjectionPtr.h
	Display/SimViewport.h
	Display/SimViewportPtr.h
	Display/SurfaceProjection.h
	Display/SurfaceProjectionPtr.h
	Display/SurfaceViewport.h
	Display/SurfaceViewportPtr.h
	Display/TrackedSurfaceProjection.h
	Display/TrackedSurfaceProjectionPtr.h
	Display/Viewport.h
	Display/ViewportPtr.h
	Draw/CpuAffinityFromEnv.h
	Draw/DrawManager.h
	Draw/DrawSimInterface.h
	Draw/DrawSimInterfacePtr.h
	Kernel/App.h
	Kernel/KernelExceptions.h
	Kernel/Kernel.h
	Kernel/User.h
	Kernel/UserPtr.h
	Performance/PerformanceMediator.h
	Performance/PerfPlugin.h
	Performance/PluginConfig.h
	Sound/SoundManagerFactory.h
	Sound/SoundManager.h
	Sound/SoundManagerSonix.h
	Test/Asserter.h
	Test/Message.h
	Test/TestCase.h
	Test/TestFailure.h
	Test/Test.h
	Test/TestRunner.h
	Test/TestSuite.h
	Util/Debug.h
	Util/Version.h
	vrjConfig.h)

set(SOURCES
	Display/CameraProjection.cpp
	Display/Display.cpp
	Display/DisplayExceptions.cpp
	Display/DisplayManager.cpp
	Display/Frustum.cpp
	Display/Projection.cpp
	Display/SimViewport.cpp
	Display/SurfaceProjection.cpp
	Display/SurfaceViewport.cpp
	Display/TrackedSurfaceProjection.cpp
	Display/Viewport.cpp
	Draw/CpuAffinityFromEnv.cpp
	Draw/DrawManager.cpp
	Draw/DrawSimInterface.cpp
	Kernel/App.cpp
	Kernel/Kernel.cpp
	Kernel/KernelExceptions.cpp
	Kernel/User.cpp
	Performance/PerformanceMediator.cpp
	Sound/SoundManager.cpp
	Sound/SoundManagerFactory.cpp
	Sound/SoundManagerSonix.cpp
	Util/Version.cpp
	vrjmain.cpp

	../vrj.rc)

set(VRJ_USE_COCOA)
set(VRJ_USE_X11)
if(WIN32)
	message(STATUS "VRJ: Using Win32 native libraries")
#	list(APPEND SOURCES 
#		Devices/KeyboardMouseDevice/InputAreaWin32.cpp
#		Devices/KeyboardMouseDevice/InputWindowWin32.cpp)
#	list(APPEND HEADERS
#		Devices/KeyboardMouseDevice/InputAreaWin32.h
#		Devices/KeyboardMouseDevice/InputWindowWin32.h)
elseif(BUILD_WITH_COCOA)	
	set(VRJ_USE_COCOA 1)
	message(STATUS "VRJ: Using Cocoa native libraries")
	list(APPEND SOURCES 
		Kernel/CocoaWrapper.mm
		Kernel/VRJBasicDelegate.mm)
	list(APPEND HEADERS
		Kernel/CocoaWrapper.h
		Kernel/VRJBasicDelegate.h)
else()
	set(VRJ_USE_X11 1)
	message(STATUS "VRJ: Using X11 libraries")
#	list(APPEND SOURCES 
#		Devices/KeyboardMouseDevice/InputAreaXWin.cpp
#		Devices/KeyboardMouseDevice/InputWindowXWin.cpp)
#	list(APPEND HEADERS
#		Devices/KeyboardMouseDevice/InputAreaXWin.h
#		Devices/KeyboardMouseDevice/InputWindowXWin.h)
endif()

include(CheckIncludeFileCXX)
check_include_file_cxx("ext/functional" HAVE_EXT_FUNCTIONAL)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/vrjParam.h.in" "${CMAKE_CURRENT_BINARY_DIR}/vrjParam.h")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/vrjDefines.h.cmake_in" "${CMAKE_CURRENT_BINARY_DIR}/vrjDefines.h")
vrjugglersuite_create_version_rc()

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/vrjParam.h" "${CMAKE_CURRENT_BINARY_DIR}/vrjDefines.h"
	DESTINATION "${VRJ_INCLUDE_PREFIX}/vrj"
	COMPONENT vrj-dev)

add_library(vrj SHARED ${HEADERS} ${SOURCES})
target_link_libraries(vrj
	${GADGET_LIBRARIES}
	${SNX_LIBRARIES}
	${Boost_PROGRAM_OPTIONS_LIBRARY})

set_target_properties(vrj PROPERTIES FOLDER "${VRJUGGLERSUITE_CORELIB_PROJECT_FOLDER}")

vrjugglersuite_set_versioned_library_output_name(vrj)

install(TARGETS vrj EXPORT vrjexport
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT vrj-runtime
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT vrj-runtime
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT vrj-dev)
