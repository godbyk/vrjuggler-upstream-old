if(NOT WIN32)
	# Uses sys/time.h
	add_executable(thread_stlTest stlTest.cpp)
	target_link_libraries(thread_stlTest vpr)
	add_test(NAME VPR-Thread-stlTest
		COMMAND thread_stlTest)
	set_target_properties(thread_stlTest PROPERTIES FOLDER "VPR tests")
endif()

add_executable(thread_test test.cpp)
target_link_libraries(thread_test vpr)
set_target_properties(thread_test PROPERTIES FOLDER "VPR tests")
# TODO test is an infinite loop
#add_test(NAME VPR-Thread-test
#	COMMAND thread_test)

if(NOT WIN32)
	# Uses sys/time.h
	add_executable(thread_testPool testPool.cpp)
	target_link_libraries(thread_testPool vpr)
	set_target_properties(thread_testPool PROPERTIES FOLDER "VPR tests")
	add_test(NAME VPR-Thread-testPool
		COMMAND thread_testPool)
endif()

add_executable(thread_testSelfPerformance testSelfPerformance.cpp)
target_link_libraries(thread_testSelfPerformance vpr)
set_target_properties(thread_testSelfPerformance PROPERTIES FOLDER "VPR tests")
add_test(NAME VPR-Thread-testSelfPerformance
	COMMAND thread_testSelfPerformance 5)

add_executable(thread_testTSD_Performance testTSD_Performance.cpp)
target_link_libraries(thread_testTSD_Performance vpr)
set_target_properties(thread_testTSD_Performance PROPERTIES FOLDER "VPR tests")
add_test(NAME VPR-Thread-testTSD_Performance
	COMMAND thread_testTSD_Performance 5)
