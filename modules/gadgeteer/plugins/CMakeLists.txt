set(CMAKE_SHARED_MODULE_PREFIX "")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${GADGET_LIB_DIR}/plugins")

# Target to build all configured plugins
add_custom_target(gadgeteer_plugins)
set_target_properties(gadgeteer_plugins PROPERTIES FOLDER "${VRJUGGLERSUITE_META_PROJECT_FOLDER}")

function(gadgeteer_add_plugin _plugin_name)
	add_definitions(-D_GADGET_CLUSTER_PLUGIN_BUILD_)
	add_library(${_plugin_name}
		MODULE ${ARGN})

	target_link_libraries(${_plugin_name} gadget)

	set_target_properties(${_plugin_name} PROPERTIES FOLDER "Gadgeteer plugins")
	install(TARGETS ${_plugin_name}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${GADGET_LIB_DIR}/plugins COMPONENT gadgeteer-runtime-plugins
		RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}/${GADGET_LIB_DIR}/plugins COMPONENT gadgeteer-runtime-plugins)
	add_dependencies(gadgeteer_plugins ${_plugin_name})
endfunction()

add_subdirectory(ApplicationBarrierManager)
add_subdirectory(ApplicationDataManager)
add_subdirectory(EventPlugin)
add_subdirectory(RIMPlugin)
