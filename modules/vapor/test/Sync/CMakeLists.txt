if(NOT WIN32)
	# Uses sys/time.h
	add_executable(sync_testCond testCond.cpp)
	target_link_libraries(sync_testCond vpr)
	set_target_properties(sync_testCond PROPERTIES FOLDER "VPR tests")

	#TODO test is an infinite loop

	#add_test(NAME VPR-Sync-testCond
	#	COMMAND sync_testCond)
endif()