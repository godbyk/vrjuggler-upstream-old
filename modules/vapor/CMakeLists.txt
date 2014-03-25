cmake_minimum_required(VERSION 2.8.5)
project(VPR)

###
# CMake modules
###
include("${CMAKE_CURRENT_SOURCE_DIR}/../../scripts/cmake/VRJugglerSuiteDefaultOptions.cmake")

###
# Version
###
vrjugglersuite_parse_version_file()

###
# Dependencies
###

find_package(CPPDOM REQUIRED)
find_package(Threads REQUIRED)
find_package(cppunit)
find_package(Boost REQUIRED COMPONENTS filesystem system)

include(CTest)

set(VPR_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CPPDOM_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})

###
# Configuration
###

# OS define
if(WIN32)
	set(VPR_OS_Windows 1)
	set(VPR_OS VPR_OS_Windows)
else()
	set(VPR_OS_${CMAKE_SYSTEM_NAME} 1)
	set(VPR_OS VPR_OS_${CMAKE_SYSTEM_NAME})
endif()
message(STATUS "VPR: Platform ${VPR_OS}")

# System domain
if(WIN32)
	set(VPR_DOMAIN VPR_DOMAIN_WIN32)
	set(VPR_USE_POSIX OFF) # Not actually used in the header, but used in this build
else()
	option(VPR_USE_NSPR "Use NSPR system instead of POSIX." OFF)
	if(VPR_USE_NSPR)
		set(VPR_DOMAIN VPR_DOMAIN_NSPR)
		set(VPR_POSIX_SEMAPHORES 1)
		set(VPR_USE_POSIX OFF) # Not actually used in the header, but used in this build
	else()
		set(VPR_DOMAIN VPR_DOMAIN_POSIX)
		set(VPR_USE_POSIX ON) # Not actually used in the header
	endif()
endif()

if(WIN32)
	set(BOOST_DEFAULT ON)
else()
	set(BOOST_DEFAULT OFF)
endif()
option(VPR_USE_BOOST "Use Boost IO " ${BOOST_DEFAULT})

if(VPR_USE_BOOST)
	find_package(Boost REQUIRED COMPONENTS filesystem system date_time regex)
endif()
message(STATUS "VPR: Using ${VPR_DOMAIN} system - Boost IO: ${VPR_USE_BOOST}.")

# Threading
if(WIN32 AND CMAKE_USE_WIN32_THREADS_INIT)
	message(STATUS "VPR: Using Win32 threads.")
	set(VPR_USE_WINTHREADS 1)
elseif(CMAKE_USE_PTHREADS_INIT)
	message(STATUS "VPR: Using pthreads.")
	set(VPR_THREAD_SCOPE PTHREAD_SCOPE_SYSTEM)
	set(VPR_POSIX_C_SOURCE 1)
	set(VPR_USE_PTHREADS 1)
	set(VPR_POSIX_SEMAPHORES 1)

	# Until proven otherwise
	set(VPR_HAVE_UNNAMED_POSIX_SEMAPHORE 1)
else()
	message(FATAL_ERROR "VPR: Apparently unsupported thread type! ${CMAKE_THREADS_INIT}")
endif()


include(CheckIncludeFileCXX)
include(CheckSymbolExists)
include(CheckStructHasMember)
include(CheckTypeSize)
include(CheckIncludeFiles)
include(CheckCXXSourceCompiles)
include(CheckFunctionExists)

# Type sizes
if(NOT VPR_USE_BOOST)
	check_type_size(char SIZEOF_CHAR)
	check_type_size(int SIZEOF_INT)
	check_type_size(long SIZEOF_LONG)
	check_type_size("long long" SIZEOF_LONG_LONG)
	check_type_size(short SIZEOF_SHORT)
endif()


# General system header include checks
check_include_file_cxx(strings.h HAVE_STRINGS_H)
check_include_file_cxx(string.h HAVE_STRING_H)
check_include_file_cxx(sys/capability.h HAVE_SYS_CAPABILITY_H)
check_include_file_cxx(sys/file.h HAVE_SYS_FILE_H)
check_include_file_cxx(sys/types.h HAVE_SYS_TYPES_H)
check_include_file_cxx(unistd.h HAVE_UNISTD_H)
check_include_file_cxx(bstring.h HAVE_BSTRING_H)

# Numeric header needed only for simulated sockets
check_include_file_cxx(ext/numeric HAVE_EXT_NUMERIC)

# General function checks
check_symbol_exists(snprintf "stdio.h" HAVE_SNPRINTF)
check_symbol_exists(strerror "string.h" HAVE_STRERROR)
check_symbol_exists(strerror_r "string.h" HAVE_STRERROR_R)

# Signal-related checks
check_include_file_cxx(signal.h HAVE_SIGNAL_H)
if(HAVE_SIGNAL_H)
	check_symbol_exists(sigaction signal.h HAVE_SIGACTION)
	check_symbol_exists(sigaddset signal.h HAVE_SIGADDSET)
	check_symbol_exists(sigdelset signal.h HAVE_SIGDELSET)
	check_symbol_exists(sigemptyset signal.h HAVE_SIGEMPTYSET)
	check_symbol_exists(sigfillset signal.h HAVE_SIGFILLSET)
	check_symbol_exists(sigismember signal.h HAVE_SIGISMEMBER)
	#check_prototype_definition(signal "void (*signal(int sig, void (*func)(int)))(int)" void signal.h HAVE_SIGNAL_RETURN_VOID)
	check_cxx_source_compiles("#include <signal.h>
								extern \"C\" void (*signal(int sig, void (*func)(int)))(int);
								int main(int argc, char * argv[]) {
								return 0;
								}" HAVE_SIGNAL_RETURN_VOID)
	if(HAVE_SIGNAL_RETURN_VOID)
		set(RETSIGTYPE void)
	else()
		set(RETSIGTYPE int)
	endif()
endif()

# Time-related checks
check_include_file_cxx(sys/time.h HAVE_SYS_TIME_H)
check_include_file_cxx(time.h HAVE_TIME_H)
if(HAVE_SYS_TIME_H AND HAVE_TIME_H)
	check_include_files("time.h;sys/time.h" TIME_WITH_SYS_TIME)
endif()
if(HAVE_SYS_TIME_H)
	# If these structs exist, they have these members for sure.
	check_struct_has_member("struct timeval" tv_sec sys/time.h HAVE_TIMEVAL)
	set(CMAKE_EXTRA_INCLUDE_FILES "sys/time.h")
	check_type_size("struct timezone" HAVE_TIMEZONE)
	set(CMAKE_EXTRA_INCLUDE_FILES)
endif()

# UUID checks
if(WIN32)
	message(STATUS "VPR: Using Windows built-in UUID code.")
else()
	check_include_file_cxx(uuid.h HAVE_UUID_H)
	check_include_file_cxx(uuid/uuid.h HAVE_UUID_UUID_H)
	check_include_file_cxx(sys/uuid.h HAVE_SYS_UUID_H)

	find_library(LIBUUID_LIBRARY uuid)
	if(LIBUUID_LIBRARY)
		set(CMAKE_REQUIRED_LIBRARIES ${LIBUUID_LIBRARY})
		check_function_exists(uuid_create HAVE_UUID_CREATE)
		check_function_exists(uuid_generate HAVE_UUID_GENERATE)
		set(CMAKE_REQUIRED_LIBRARIES)
	else()
		check_function_exists(uuid_create HAVE_UUID_CREATE_NOLIB)
		check_function_exists(uuid_generate HAVE_UUID_GENERATE_NOLIB)
	endif()

	set(VPR_LEACH_UUID_DEFAULT OFF)
	if(HAVE_UUID_CREATE_NOLIB)
		set(UUID_LIBRARY)
		set(VPR_USE_DCE_1_1_UUID 1)
		message(STATUS "VPR: Have DCE 1.1 uuid code - no library needed.")
	elseif(HAVE_UUID_GENERATE_NOLIB)
		set(UUID_LIBRARY)
		set(VPR_USE_LIBUUID 1)
		message(STATUS "VPR: Have libuuid code - no library needed.")
	elseif(HAVE_UUID_CREATE)
		set(UUID_LIBRARY ${LIBUUID_LIBRARY})
		set(VPR_USE_DCE_1_1_UUID 1)
		message(STATUS "VPR: Have DCE 1.1 uuid code in ${UUID_LIBRARY}.")
	elseif(HAVE_UUID_GENERATE)
		set(UUID_LIBRARY ${LIBUUID_LIBRARY})
		set(VPR_USE_LIBUUID 1)
		message(STATUS "VPR: Have libuuid code in ${UUID_LIBRARY}.")
	else()
		# Fallback: included Leach UUID code
		set(VPR_LEACH_UUID_DEFAULT ON)
	endif()

	option(VPR_USE_LEACH_UUID "Use bundled Leach UUID code instead of platform libraries?" ${VPR_LEACH_UUID_DEFAULT})
	if(VPR_USE_LEACH_UUID)
		# TODO - this is actually just a VPR-local include directory.
		list(APPEND VPR_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/../../external/leach-uuid")
		message(STATUS "VPR: Using bundled Leach UUID code.")
		set(UUID_LIBRARY)
		set(VPR_USE_DCE_1_1_UUID OFF)
		set(VPR_USE_LIBUUID OFF)
	endif()
endif()

# MD5 library
option(VPR_USE_EMBEDDED_MD5C "Use embedded MD5 code - currently the only option." ON)
if(VPR_USE_EMBEDDED_MD5C)
	set(MD5_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../external/libmd5-rfc")
	include_directories(${MD5_INCLUDE_DIR})
else()
	message(FATAL_ERROR "No alternate MD5 code currently available - must enable VPR_USE_EMBEDDED_MD5C")
endif()

# Networking
if(NOT VPR_USE_NSPR)
#	check_type_size(in_addr_t HAVE_IN_ADDR_T)
#	if(NOT HAVE_IN_ADDR_T)
#		message(FATAL_ERROR "Haven't yet handled if there's no in_addr_t")
#	endif()
	check_include_file_cxx(sys/socket.h HAVE_SYS_SOCKET_H)
	check_struct_has_member(sockaddr_in sin_len "sys/types.h;netinet/in.h" HAVE_SIN_LEN)
	check_symbol_exists(TCP_CORK "sys/types.h;netinet/tcp.h" HAVE_TCP_CORK)
	check_symbol_exists(TCP_NOPUSH "sys/types.h;netinet/tcp.h" HAVE_TCP_NOPUSH)
	if(NOT CMAKE_SYSTEM_NAME MATCHES "Darwin")
		# According to configure.ac, Darwin has a buggy nopush implementation
		if(HAVE_TCP_CORK OR HAVE_TCP_NOPUSH)
			set(HAVE_CORKABLE_TCP 1)
		endif()
	endif()
	if(HAVE_SYS_SOCKET_H)
		# for example, Darwin
		check_symbol_exists(getifaddrs "sys/types.h;sys/socket.h;ifaddrs.h" HAVE_GETIFADDRS)
	else()
		# for example, Linux
		check_symbol_exists(getifaddrs "sys/types.h;ifaddrs.h" HAVE_GETIFADDRS)
	endif()
endif()

# Unordered ("hash") structures
check_include_file_cxx(hash_map HAVE_HASH_MAP)
check_include_file_cxx(hash_map.h HAVE_HASH_MAP_H)
check_include_file_cxx(ext/hash_map HAVE_EXT_HASH_MAP)

check_include_file_cxx(hash_set HAVE_HASH_SET)
check_include_file_cxx(hash_set.h HAVE_HASH_SET_H)
check_include_file_cxx(ext/hash_set HAVE_EXT_HASH_SET)

# Backtrace support
check_symbol_exists(backtrace "execinfo.h" HAVE_BACKTRACE)

# Dynamic libraries
if(NOT WIN32)
	find_library(LIBDL_LIBRARY dl)
	if(LIBDL_LIBRARY)
		set(DL_LIBRARY ${LIBDL_LIBRARY})
	else()
		set(DL_LIBRARY)
	endif()
endif()

# Target system release
if("${CMAKE_SYSTEM_VERSION}" MATCHES "^([0-9]*)[.]([0-9]*)")
	set(VPR_OS_RELEASE_MAJOR ${CMAKE_MATCH_1})
	set(VPR_OS_RELEASE_MINOR ${CMAKE_MATCH_2})
endif()

if(NOT (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR))
	set(VPR_INCLUDE_DIRECTORIES ${VPR_INCLUDE_DIRECTORIES} PARENT_SCOPE)
endif()
include_directories(${VPR_INCLUDE_DIRECTORIES})

if(BUILD_VERSIONED_DIRECTORIES)
	set(VPR_INCLUDE_PREFIX ${CMAKE_INSTALL_INCLUDEDIR}/vpr-${MAJOR_VER_NUMBER}.${MINOR_VER_NUMBER})
else()
	set(VPR_INCLUDE_PREFIX ${CMAKE_INSTALL_INCLUDEDIR})
endif()

add_subdirectory(vpr)

install(DIRECTORY vpr
	DESTINATION ${VPR_INCLUDE_PREFIX}
	COMPONENT vpr-dev
	FILES_MATCHING PATTERN *.h)

if(BUILD_TESTING)
	add_subdirectory(test)
endif()
