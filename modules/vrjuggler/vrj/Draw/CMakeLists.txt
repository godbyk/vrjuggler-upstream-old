
option(VRJ_BUILD_WITH_OPENGL "Build the OpenGL draw manager?" ON)
if(VRJ_BUILD_WITH_OPENGL)
	add_subdirectory(OpenGL)
endif()

if(WIN32)
	option(VRJ_BUILD_WITH_DIRECT3D "Build the Direct3d draw manager?" OFF)
	if(VRJ_BUILD_WITH_DIRECT3D)
		add_subdirectory(Direct3D)
	endif()
endif()

option(VRJ_BUILD_WITH_PERFORMER "Build the OpenGL Performer draw manager?" OFF)
if(VRJ_BUILD_WITH_PERFORMER)
	add_subdirectory(Pf)
endif()


