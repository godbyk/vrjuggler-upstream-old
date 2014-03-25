set(CMAKE_SHARED_MODULE_PREFIX "")

set(RELEASE_DIR opt)
set(MINSIZEREL_DIR opt)
if(MSVC)
	set(DEBUG_DIR dbgrt)
	set(RELWITHDEBINFO_DIR dbg)
else()
	set(DEBUG_DIR dbg)
	set(RELWITHDEBINFO_DIR opt) # TODO not sure if this makes sense
endif()

foreach(buildtype RELEASE MINSIZEREL RELWITHDEBINFO DEBUG)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${buildtype} "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${SNX_LIB_DIR}/plugins/${${buildtype}_DIR}")
endforeach()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE}")

# Target to build all configured backends
add_custom_target(sonix_backends)
set_target_properties(sonix_backends PROPERTIES FOLDER "${VRJUGGLERSUITE_META_PROJECT_FOLDER}")

function(sonix_add_backend _backend_name)
	add_definitions(-D_SNX_PLUGIN_BUILD_)
	add_library(${_backend_name}_snd
		MODULE ${ARGN})

	target_link_libraries(${_backend_name}_snd sonix)
	set_target_properties(${_backend_name}_snd PROPERTIES FOLDER "Sonix backends")
	add_dependencies(sonix_backends ${_backend_name}_drv)

	foreach(buildtype RELEASE MINSIZEREL RELWITHDEBINFO DEBUG)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${buildtype} "${BASELIBDIR}/${${buildtype}_DIR}")

		install(TARGETS ${_backend_name}_snd
			LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${SNX_LIB_DIR}/plugins/${${buildtype}_DIR} COMPONENT sonix-runtime-openal
			RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}/${SNX_LIB_DIR}/plugins/${${buildtype}_DIR} COMPONENT sonix-runtime-openal
			CONFIGURATIONS ${buildtype})
	endforeach()
endfunction()

find_package(ALUT)
if(ALUT_FOUND)
	add_subdirectory(OpenAL)
endif()

#find_package(Audiere)
#if(AUDIERE_FOUND)
#	add_subdirectory(Audiere)
#endif()

#find_package(Subsynth)
#if(SUBSYNTH_FOUND)
#	add_subdirectory(Subsynth)
#endif()

