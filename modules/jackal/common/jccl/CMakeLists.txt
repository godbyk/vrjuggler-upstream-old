
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/jcclParam.h.in" "${CMAKE_CURRENT_BINARY_DIR}/jcclParam.h")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/jcclDefines.h.cmake_in" "${CMAKE_CURRENT_BINARY_DIR}/jcclDefines.h")
vrjugglersuite_create_version_rc()

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/jcclParam.h" "${CMAKE_CURRENT_BINARY_DIR}/jcclDefines.h"
	DESTINATION ${JCCL_INCLUDE_PREFIX}/jccl
	COMPONENT jccl-dev)

