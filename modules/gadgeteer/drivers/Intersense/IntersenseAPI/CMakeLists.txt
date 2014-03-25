
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
	add_definitions(-DMACOSX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "HP") # FIXME is this the proper system name?
	add_definitions(-DHP)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	add_definitions(-DLINUX -DUNIX)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Solaris") # FIXME is this the proper system name?
	add_definitions(-DSUN)
elseif(WIN32)
	# No extra definitions needed
else()
	message("CMAKE_SYSTEM_NAME is [${CMAKE_SYSTEM_NAME}]. We're not handling this case yet!")
endif()

gadgeteer_add_driver(IntersenseAPI
	IntersenseAPI.cpp
	IntersenseAPI.h
	intersense_api.rc
	IntersenseAPIStandalone.cpp
	IntersenseAPIStandalone.h
	isense/isense.c)

