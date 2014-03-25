set(HEADERS
	Perf/ProfileNode.h
	Perf/ProfileIterator.h
	Perf/ProfileManager.h
	AutoLink.h
	vprDomain.h
	SystemBase.h
	System.h
	md/WIN32/DynLoad/LibraryWin32.h
	md/WIN32/Util/ErrorImplWin32.h
	md/WIN32/Sync/MutexWin32.h
	md/WIN32/Sync/SemaphoreWin32.h
	md/WIN32/Sync/CondVarWin32.h
	md/WIN32/Thread/ThreadKeyWin32.h
	md/WIN32/Thread/ThreadWin32.h
	md/WIN32/IO/Port/SerialPortImplWin32.h
	md/WIN32/SystemWin32.h
	md/NSPR/DynLoad/LibraryNSPR.h
	md/NSPR/Util/ErrorImplNSPR.h
	md/NSPR/vprTypesNSPR.h
	md/NSPR/SystemNSPR.h
	md/NSPR/NSPRHelpers.h
	md/NSPR/Sync/MutexNSPR.h
	md/NSPR/Sync/RWMutexNSPR.h
	md/NSPR/Sync/SemaphoreNSPR.h
	md/NSPR/Sync/CondVarNSPR.h
	md/NSPR/Thread/ThreadNSPR.h
	md/NSPR/Thread/ThreadKeyNSPR.h
	md/NSPR/IO/Socket/InetAddrNSPR.h
	md/NSPR/IO/Socket/SocketDatagramImplNSPR.h
	md/NSPR/IO/Socket/SocketStreamImplNSPR.h
	md/NSPR/IO/Socket/SocketImplNSPR.h
	md/NSPR/IO/IOSysNSPR.h
	md/NSPR/IO/SelectorImplNSPR.h
	md/BOOST/vprTypesBOOST.h
	md/BOOST/IO/IOSysBOOST.h
	md/BOOST/IO/SelectorImplBOOST.h
	md/BOOST/IO/Socket/InetAddrBOOST.h
	md/BOOST/IO/Socket/SocketStreamImplBOOST.h
	md/BOOST/IO/Socket/SocketImplBOOST.h
	md/BOOST/IO/Socket/SocketDatagramImplBOOST.h
	md/POSIX/DynLoad/LibraryUNIX.h
	md/POSIX/Util/ErrorImplPosix.h
	md/POSIX/SystemPosix.h
	md/POSIX/Sync/CondVarPosix.h
	md/POSIX/Sync/RWMutexPosix.h
	md/POSIX/Sync/SemaphorePosix.h
	md/POSIX/Sync/MutexPosix.h
	md/POSIX/Thread/ThreadPosix.h
	md/POSIX/Thread/ThreadKeyPosix.h
	md/POSIX/IO/FileHandleImplUNIX.h
	md/POSIX/IO/Port/SerialPortImplTermios.h
	md/POSIX/IO/Socket/SocketImplBSD.h
	md/POSIX/IO/Socket/InetAddrBSD.h
	md/POSIX/IO/Socket/SocketDatagramImplBSD.h
	md/POSIX/IO/Socket/SocketStreamImplBSD.h
	md/POSIX/IO/IOSysUnix.h
	md/POSIX/IO/SelectorImplBSD.h
	vprConfig.h
	vpr.h
	DynLoad/LibraryFinder.h
	DynLoad/LoaderError.h
	DynLoad/SymbolLookupException.h
	DynLoad/LibraryLoader.h
	DynLoad/LibraryException.h
	DynLoad/Library.h
	Util/ReturnStatus.h
	Util/Interval.h
	Util/Factory.h
	Util/Debug.h
	Util/Exception.h
	Util/Version.h
	Util/DurationStatCollector.h
	Util/StatCollector.h
	Util/ErrorBase.h
	Util/ResourceException.h
	Util/AttributeMapBase.h
	Util/DateTime.h
	Util/Timer.h
	Util/StreamLock.h
	Util/Error.h
	Util/FileUtils.h
	Util/IllegalArgumentException.h
	Util/detail/LifetimeTracker.h
	Util/Assert.h
	Util/BadCastException.h
	Util/SampleLimitedStatCollector.h
	Util/GUID.h
	Util/Singleton.h
	Util/SignalProxy.h
	vprTypes.h
	Sync/Guard.h
	Sync/NullMutex.h
	Sync/Mutex.h
	Sync/RWGuard.h
	Sync/Semaphore.h
	Sync/DeadlockException.h
	Sync/CondVar.h
	Sync/RWMutex.h
	Sync/GuardedQueue.h
	Sync/LockException.h
	Thread/TSObject.h
	Thread/UncaughtThreadException.h
	Thread/Signal.h
	Thread/Thread.h
	Thread/TSObjectProxy.h
	Thread/ThreadManager.h
	Thread/BaseThread.h
	Thread/ThreadPool.h
	Thread/TSTable.h
	IO/SerializableObject.h
	IO/BlockIO.h
	IO/XMLObjectReader.h
	IO/XMLObjectWriter.h
	IO/BufferObjectReader.h
	IO/ObjectReader.h
	IO/FileHandle.h
	IO/Selector.h
	IO/Stats/BaseIOStatsStrategy.h
	IO/Stats/BandwidthIOStatsStrategy.h
	IO/Stats/IOStatsStrategyAdapter.h
	IO/Selector_t.h
	IO/IOException.h
	IO/IOSysBase.h
	IO/TimeoutException.h
	IO/FileHandle_t.h
	IO/Port/SerialPort_t.h
	IO/Port/SerialTypes.h
	IO/Port/SerialPort.h
	IO/Port/Port.h
	IO/Socket/AveragingAllocationStrategy.h
	IO/Socket/MaximumAllocationStrategy.h
	IO/Socket/SocketConnector.h
	IO/Socket/InetAddr.h
	IO/Socket/ConnectionAbortedException.h
	IO/Socket/SocketException.h
	IO/Socket/SocketDatagram_t.h
	IO/Socket/SocketOptions.h
	IO/Socket/NoPushWriter.h
	IO/Socket/SimpleAllocationStrategies.h
	IO/Socket/McastReq.h
	IO/Socket/SocketDatagram.h
	IO/Socket/NoRouteToHostException.h
	IO/Socket/ConnectionRefusedException.h
	IO/Socket/SocketStream_t.h
	IO/Socket/ConnectionResetException.h
	IO/Socket/SocketTypes.h
	IO/Socket/Socket_t.h
	IO/Socket/UnknownHostException.h
	IO/Socket/Socket.h
	IO/Socket/SocketStream.h
	IO/Socket/SocketAcceptor.h
	IO/ObjectWriter.h
	IO/SelectorBase.h
	IO/IOSys.h
	IO/EOFException.h
	IO/WouldBlockException.h
	IO/BufferObjectWriter.h
)

set(SOURCES
	SystemBase.cpp
	Perf/ProfileNode.cpp
	Perf/ProfileIterator.cpp
	Perf/ProfileManager.cpp
	md/common/InetAddrHelpers.cpp
	vprmain.cpp
	Util/Exception.cpp
	Util/BadCastException.cpp
	Util/StreamLock.cpp
	Util/Debug.cpp
	Util/FileUtils.cpp
	Util/GUID.cpp
	Util/IllegalArgumentException.cpp
	Util/detail/LifetimeTracker.cpp
	Util/Version.cpp
	Util/Interval.cpp
	Util/ResourceException.cpp
	Sync/DeadlockException.cpp
	Sync/LockException.cpp
	Thread/ThreadPool.cpp
	Thread/BaseThread.cpp
	Thread/ThreadManager.cpp
	Thread/TSObject.cpp
	Thread/TSObjectProxy.cpp
	Thread/Signal.cpp
	Thread/UncaughtThreadException.cpp
	IO/BufferObjectWriter.cpp
	IO/IOException.cpp
	IO/XMLObjectReader.cpp
	IO/TimeoutException.cpp
	IO/BlockIO.cpp
	IO/BufferObjectReader.cpp
	IO/ObjectWriter.cpp
	IO/Stats/BandwidthIOStatsStrategy.cpp
	IO/Stats/BaseIOStatsStrategy.cpp
	IO/ObjectReader.cpp
	IO/EOFException.cpp
	IO/WouldBlockException.cpp
	IO/Port/Port.cpp
	IO/Socket/SocketAcceptor.cpp
	IO/Socket/AveragingAllocationStrategy.cpp
	IO/Socket/SocketConnector.cpp
	IO/Socket/SocketException.cpp
	IO/Socket/ConnectionAbortedException.cpp
	IO/Socket/MaximumAllocationStrategy.cpp
	IO/Socket/NoRouteToHostException.cpp
	IO/Socket/ConnectionRefusedException.cpp
	IO/Socket/NoPushWriter.cpp
	IO/Socket/ConnectionResetException.cpp
	IO/Socket/UnknownHostException.cpp
	IO/XMLObjectWriter.cpp
)

set(SOURCES_WIN32
	md/WIN32/DynLoad/LibraryWin32.cpp
	md/WIN32/Util/ErrorImplWin32.cpp
	md/WIN32/Sync/SemaphoreWin32.cpp
	md/WIN32/Sync/CondVarWin32.cpp
	md/WIN32/Sync/MutexWin32.cpp
	md/WIN32/Thread/ThreadKeyWin32.cpp
	md/WIN32/Thread/ThreadWin32.cpp
	md/WIN32/IO/Port/SerialPortImplWin32.cpp
	md/WIN32/SystemWin32.cpp
	Sync/RWMutex.cpp
)
source_group(Win32 FILES ${SOURCES_WIN32})

set(SOURCES_NSPR
	md/NSPR/DynLoad/LibraryNSPR.cpp
	md/NSPR/SystemNSPR.cpp
	md/NSPR/Util/ErrorImplNSPR.cpp
	md/NSPR/NSPRHelpers.cpp
	md/NSPR/Sync/CondVarNSPR.cpp
	md/NSPR/Sync/RWMutexNSPR.cpp
	md/NSPR/Sync/MutexNSPR.cpp
	md/NSPR/Thread/ThreadNSPR.cpp
	md/NSPR/Thread/ThreadKeyNSPR.cpp
	md/NSPR/IO/IOSysNSPR.cpp
	md/NSPR/IO/SelectorImplNSPR.cpp
	md/NSPR/IO/Socket/SocketStreamImplNSPR.cpp
	md/NSPR/IO/Socket/SocketImplNSPR.cpp
	md/NSPR/IO/Socket/InetAddrNSPR.cpp
	md/NSPR/IO/Socket/SocketDatagramImplNSPR.cpp
)
source_group(NSPR FILES ${SOURCES_NSPR})

set(SOURCES_BOOST
	md/BOOST/IO/SelectorImplBOOST.cpp
	md/BOOST/IO/Socket/SocketImplBOOST.cpp
	md/BOOST/IO/Socket/SocketDatagramImplBOOST.cpp
	md/BOOST/IO/Socket/SocketStreamImplBOOST.cpp
	md/BOOST/IO/Socket/InetAddrBOOST.cpp
	md/BOOST/IO/IOSysBOOST.cpp
)
source_group(Boost FILES ${SOURCES_BOOST})

set(SOURCES_POSIX
	md/POSIX/DynLoad/LibraryUNIX.cpp
	md/POSIX/Util/ErrorImplPosix.cpp
	md/POSIX/SystemPosix.cpp
	md/POSIX/Sync/SemaphorePosix.cpp
	md/POSIX/Sync/MutexPosix.cpp
	md/POSIX/Sync/RWMutexPosix.cpp
	md/POSIX/Sync/CondVarPosix.cpp
	md/POSIX/Thread/ThreadPosix.cpp
	md/POSIX/Thread/ThreadKeyPosix.cpp
	md/POSIX/IO/IOSysUnix.cpp
	md/POSIX/IO/Port/SerialPortImplTermios.cpp
	md/POSIX/IO/FileHandleImplUNIX.cpp
	md/POSIX/IO/Socket/InetAddrBSD.cpp
	md/POSIX/IO/Socket/SocketImplBSD.cpp
	md/POSIX/IO/Socket/SocketStreamImplBSD.cpp
	md/POSIX/IO/Socket/SocketDatagramImplBSD.cpp
	md/POSIX/IO/SelectorImplBSD.cpp
)
source_group(POSIX FILES ${SOURCES_POSIX})

set(SOURCES_DYNLOAD
	DynLoad/LibraryFinder.cpp
	DynLoad/LibraryException.cpp
	DynLoad/LoaderError.cpp
	DynLoad/SymbolLookupException.cpp
	DynLoad/LibraryLoader.cpp
)
source_group(DynLoad FILES ${SOURCES_DYNLOAD})
list(APPEND SOURCES ${SOURCES_DYNLOAD})

set(SOURCES_MD5C
	${CMAKE_CURRENT_SOURCE_DIR}/../../../external/libmd5-rfc/md5.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../../external/libmd5-rfc/md5.c)
source_group(MD5C FILES ${SOURCES_MD5C})

set(SOURCES_LEACHUUID
	${CMAKE_CURRENT_SOURCE_DIR}/../../../external/leach-uuid/uuid/sysdep.c
	${CMAKE_CURRENT_SOURCE_DIR}/../../../external/leach-uuid/uuid/sysdep.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../../external/leach-uuid/uuid/uuid.c
	${CMAKE_CURRENT_SOURCE_DIR}/../../../external/leach-uuid/uuid/uuid.h)
source_group(LeachUUID FILES ${SOURCES_LEACHUUID})

if(WIN32)
	list(APPEND SOURCES ${SOURCES_WIN32})
endif()

if(VPR_USE_BOOST)
	list(APPEND SOURCES ${SOURCES_BOOST})
endif()

if(VPR_USE_NSPR)
	list(APPEND SOURCES ${SOURCES_NSPR})
endif()

if(VPR_USE_POSIX)
	list(APPEND SOURCES ${SOURCES_POSIX})
endif()

if(VPR_USE_LEACH_UUID)
	list(APPEND SOURCES ${SOURCES_LEACHUUID})
endif()

if(VPR_USE_EMBEDDED_MD5C)
	list(APPEND SOURCES ${SOURCES_MD5C})
endif()


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vprDefines.h.cmake_in ${CMAKE_CURRENT_BINARY_DIR}/vprDefines.h)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/vprParam.h.in ${CMAKE_CURRENT_BINARY_DIR}/vprParam.h)
vrjugglersuite_create_version_rc()

add_definitions(-D_VPR_BUILD_)

add_library(vpr SHARED ${HEADERS} ${SOURCES})
target_link_libraries(vpr
	${UUID_LIBRARY}
	${CPPDOM_LIBRARIES}
	${CMAKE_THREAD_LIBS_INIT}
	${Boost_LIBRARIES}
	${DL_LIBRARY})

if(WIN32)
	if(MSVC)
		target_link_libraries(vpr dbghelp)
	else()
		target_link_libraries(vpr imagehlp)
	endif()
	target_link_libraries(vpr rpcrt4 ws2_32)
endif()

set_target_properties(vpr PROPERTIES FOLDER "${VRJUGGLERSUITE_CORELIB_PROJECT_FOLDER}")

vrjugglersuite_set_versioned_library_output_name(vpr)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/vprParam.h" "${CMAKE_CURRENT_BINARY_DIR}/vprDefines.h"
	DESTINATION ${VPR_INCLUDE_PREFIX}/vpr
	COMPONENT vpr-dev)

install(TARGETS vpr EXPORT vprexport
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT vpr-runtime
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT vpr-runtime
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT vpr-dev)
