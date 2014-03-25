include_directories(${DIRECTX_INCLUDE_DIRS})
gadgeteer_add_driver(DirectXJoystick
	DirectXJoystick.cpp
	DirectXJoystickExceptions.h
	DirectXJoystick.h
	directx_joystick.rc
	DirectXJoystickStandalone.cpp
	DirectXJoystickStandalone.h)

target_link_libraries(DirectXJoystick_drv ${DIRECTX_DXGUID_LIBRARY} ${DIRECTX_DINPUT_LIBRARY} ${DIRECTX_DXERR_LIBRARY})