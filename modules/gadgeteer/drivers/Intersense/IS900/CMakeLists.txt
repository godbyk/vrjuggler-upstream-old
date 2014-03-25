gadgeteer_add_driver(IS900
	Intersense.cpp
	Intersense.h
	IntersenseStandalone.cpp
	IntersenseStandalone.h
	is900.rc
	isdriver.cpp
	isdriver.h
	isense.cpp
	isense.h
	itcom.cpp
	itcom.h
	serial.cpp
	serial.h
	timer.cpp
	timer.h
	wsock.cpp
	wsock.h)

if(WIN32)
	target_link_libraries(IS900_drv ws2_32)
endif()
