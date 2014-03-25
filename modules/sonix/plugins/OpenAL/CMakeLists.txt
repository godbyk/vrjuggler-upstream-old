
include_directories(${ALUT_INCLUDE_DIRS})
sonix_add_backend(OpenAL
	OpenALSoundImplementation.cpp
	OpenALSoundImplementation.h
	openal.rc)

target_link_libraries(OpenAL_snd ${ALUT_LIBRARIES})
