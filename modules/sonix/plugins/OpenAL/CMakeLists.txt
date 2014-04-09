
include_directories(${ALUT_INCLUDE_DIRS})

include(CheckIncludeFileCXX)
include(CheckFunctionExists)

check_include_file_cxx(AL/al.h HAVE_AL_AL_H)
check_include_file_cxx(AL/alut.h HAVE_AL_ALUT_H)
check_include_file_cxx(alut.h HAVE_ALUT_H)
maybe_add_definitions(HAVE_AL_AL_H HAVE_AL_ALUT_H HAVE_ALUT_H)

set(CMAKE_REQUIRED_LIBRARIES ${ALUT_LIBRARIES})
check_function_exists(alutInitWithoutContext HAVE_ALUT_INIT_WITHOUT_CONTEXT)
check_function_exists(alutGetError HAVE_ALUT_GET_ERROR)
check_function_exists(alutLoadMemoryFromFile HAVE_ALUT_LOAD_MEMORY_FROM_FILE)
unset(CMAKE_REQUIRED_LIBRARIES)
maybe_add_definitions(HAVE_ALUT_INIT_WITHOUT_CONTEXT HAVE_ALUT_GET_ERROR HAVE_ALUT_LOAD_MEMORY_FROM_FILE)

sonix_add_backend(OpenAL
	OpenALSoundImplementation.cpp
	OpenALSoundImplementation.h
	openal.rc)

target_link_libraries(OpenAL_snd ${ALUT_LIBRARIES})
