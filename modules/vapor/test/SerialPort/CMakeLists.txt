foreach(APP first reader second writer)
	add_executable(serialport_${APP} ${APP}.cpp)
	target_link_libraries(serialport_${APP} vpr)
	set_target_properties(serialport_${APP} PROPERTIES FOLDER "VPR tests")
endforeach()

