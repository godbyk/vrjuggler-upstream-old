include_directories(${VRPN_INCLUDE_DIRS})

find_package(Libusb1)
if(LIBUSB1_FOUND)
	include_directories(${LIBUSB1_INCLUDE_DIRS})
	list(APPEND VRPN_LIBRARIES ${LIBUSB1_LIBRARIES})
endif()

gadgeteer_add_driver(VRPN vrpn.rc Vrpn.cpp Vrpn.h)
target_link_libraries(VRPN_drv ${VRPN_LIBRARIES})
