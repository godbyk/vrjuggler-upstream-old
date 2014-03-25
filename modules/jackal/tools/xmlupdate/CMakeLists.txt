set(SOURCES
	cfg_2.0-2.1.xsl
	cfg_2.1-3.0.xsl
	desc_2.0-2.1.xsl
	desc_2.1-2.2.xsl
	desc_2.2-2.3.xsl
	desc_2.3-3.0.xsl
	jdef_3.0-3.1.xsl
	Makefile
	README.txt
	xmlupdate.py)


install(FILES ${SOURCES}
	COMPONENT jccl-runtime
	DESTINATION ${JCCL_SHARE_DIR}/tools/xmlupdate)

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/${JCCL_SHARE_DIR}/tools/xmlupdate")

foreach(fn ${SOURCES})
	configure_file("${CMAKE_CURRENT_SOURCE_DIR}/${fn}"
		"${CMAKE_BINARY_DIR}/${JCCL_SHARE_DIR}/tools/xmlupdate/${fn}" COPYONLY)
endforeach()
