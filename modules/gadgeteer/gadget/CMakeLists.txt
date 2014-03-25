
add_definitions(-D_GADGET_BUILD_ "-DGADGET_SHARE_DIR=\"${GADGET_SHARE_DIR}\"" "-DGADGET_ROOT_DIR=\"${CMAKE_INSTALL_PREFIX}\"")

set(HEADERS
	AutoLink.h
	Devices/DriverConfig.h
	Devices/KeyboardMouseDevice/InputAreaCocoa.h
	Devices/KeyboardMouseDevice/InputArea.h
	Devices/KeyboardMouseDevice/InputAreaWin32.h
	Devices/KeyboardMouseDevice/InputAreaXWin.h
	Devices/KeyboardMouseDevice/InputViewCocoa.h
	Devices/KeyboardMouseDevice/InputWindowCocoa.h
	Devices/KeyboardMouseDevice/InputWindowWin32.h
	Devices/KeyboardMouseDevice/InputWindowXWin.h
	Devices/KeyboardMouseDevice/KeyboardMouseDevice.h
	Devices/Sim/SimAnalog.h
	Devices/Sim/SimDigitalGlove.h
	Devices/Sim/SimDigital.h
	Devices/Sim/SimGloveGesture.h
	Devices/Sim/SimInputDevice.h
	Devices/Sim/SimInput.h
	Devices/Sim/SimPosition.h
	Devices/Sim/SimRelativePosition.h
	Devices/Sim/SimSetablePosition.h
	Event/AbstractEventInterface.h
	Event/AnalogEventInterface.h
	Event/ClickEvent.h
	Event/CommandEventInterface.h
	Event/DataExaminer.h
	Event/DigitalClickEventInterface.h
	Event/DigitalEventInterface.h
	EventEmitter.h
	EventEmitterPtr.h
	Event/EventCollection.h
	Event/EventGenerator.h
	Event/EventGeneratorPtr.h
	Event/Event.h
	Event/EventInterface.h
	Event/EventPtr.h
	Event/EventRegistration.h
	Event/EventTags.h
	Event/KeyboardMouseEventInterface.h
	Event/KeyboardMouse/KeyEvent.h
	Event/KeyboardMouse/KeyEventPtr.h
	Event/KeyboardMouse/MouseEvent.h
	Event/KeyboardMouse/MouseEventPtr.h
	Event/KeyboardMouse/SampleHandler.h
	Event/MouseClickEventInterface.h
	Event/MultiEventGenerator.h
	Event/MultiEventInterface.h
	Event/PositionEventInterface.h
	Event/ProxySetter.h
	Event/SampleHandler.h
	Event/StringEventInterface.h
	Filter/Position/FullPositionXformFilter.h
	Filter/Position/PositionCalibrationFilter.h
	Filter/Position/PositionFilterFactory.h
	Filter/Position/PositionFilter.h
	Filter/Position/PositionXformFilter.h
	gadgetConfig.h
	InputLogger.h
	InputLoggerPtr.h
	InputManager.h
	NetworkManager.h
	Node.h
	NodePtr.h
	PacketHandler.h
	PacketHandlerPtr.h
	ProxyDepChecker.h
	ProxyFactory.h
	Reactor.h
	Type/AllBaseTypes.h
	Type/AnalogData.h
	Type/Analog.h
	Type/AnalogInterface.h
	Type/AnalogProxy.h
	Type/AnalogProxyPtr.h
	Type/AnalogPtr.h
	Type/BaseTypeFactory.h
	Type/CommandData.h
	Type/Command.h
	Type/CommandInterface.h
	Type/CommandProxy.h
	Type/CommandProxyPtr.h
	Type/CommandPtr.h
	Type/DeviceConstructorBase.h
	Type/DeviceConstructor.h
	Type/DeviceData.h
	Type/DeviceFactory.h
	Type/DeviceInterface.h
	Type/DeviceTraits.h
	Type/DigitalData.h
	Type/Digital.h
	Type/DigitalInterface.h
	Type/DigitalProxy.h
	Type/DigitalProxyPtr.h
	Type/DigitalPtr.h
	Type/Gesture.h
	Type/GestureInterface.h
	Type/GestureProxy.h
	Type/GestureProxyPtr.h
	Type/GesturePtr.h
	Type/GloveData.h
	Type/GloveGesture.h
	Type/Glove.h
	Type/GloveInterface.h
	Type/GloveProxy.h
	Type/GloveProxyPtr.h
	Type/GlovePtr.h
	Type/HatData.h
	Type/Hat.h
	Type/HatInterface.h
	Type/HatProxy.h
	Type/HatProxyPtr.h
	Type/HatPtr.h
	Type/InputData.h
	Type/InputDevice.h
	Type/Input.h
	Type/InputPtr.h
	Type/KeyboardMouseData.h
	Type/KeyboardMouse/EventFactory.h
	Type/KeyboardMouse/Event.h
	Type/KeyboardMouse/EventPtr.h
	Type/KeyboardMouse.h
	Type/KeyboardMouseInterface.h
	Type/KeyboardMouse/KeyEvent.h
	Type/KeyboardMouse/KeyEventPtr.h
	Type/KeyboardMouse/Keys.h
	Type/KeyboardMouse/MouseEvent.h
	Type/KeyboardMouse/MouseEventPtr.h
	Type/KeyboardMouseProxy.h
	Type/KeyboardMouseProxyPtr.h
	Type/KeyboardMousePtr.h
#	Type/LinearSigmoidPositionFilter.h # TODO: This file is broken!
	Type/PositionData.h
	Type/Position.h
	Type/PositionInterface.h
	Type/Position/PositionUnitConversion.h
	Type/PositionProxy.h
	Type/PositionProxyPtr.h
	Type/PositionPtr.h
	Type/Proxy.h
	Type/ProxyPtr.h
	Type/ProxyTraits.h
	Type/RumbleData.h
	Type/RumbleEffect.h
	Type/RumbleEffectPtr.h
	Type/Rumble.h
	Type/RumbleInterface.h
	Type/RumbleProxy.h
	Type/RumbleProxyPtr.h
	Type/RumblePtr.h
	Type/SampleBuffer.h
	Type/Speech.h
	Type/StringData.h
	Type/String.h
	Type/StringInterface.h
	Type/StringProxy.h
	Type/StringProxyPtr.h
	Type/StringPtr.h
	Type/TypeHelpers.h
	Util/Debug.h
	Util/DeviceSerializationTokens.h
	Util/PathHelpers.h
	Util/PluginVersionException.h
	Util/Version.h

	../cluster/ClusterDelta.h
	../cluster/ClusterDepChecker.h
	../cluster/ClusterException.h
	../cluster/ClusterManager.h
	../cluster/ClusterNetwork.h
	../cluster/ClusterPlugin.h
	../cluster/ClusterPluginPtr.h
	../cluster/ConfigHandler.h
	../cluster/ConfigHandlerPtr.h
	../cluster/Packets/ConfigPacket.h
	../cluster/Packets/ConfigPacketPtr.h
	../cluster/Packets/DataPacket.h
	../cluster/Packets/DataPacketPtr.h
	../cluster/Packets/DeviceAck.h
	../cluster/Packets/DeviceAckPtr.h
	../cluster/Packets/EndBlock.h
	../cluster/Packets/EndBlockPtr.h
	../cluster/Packets/Header.h
	../cluster/Packets/HeaderPtr.h
	../cluster/Packets/PacketFactory.h
	../cluster/Packets/Packet.h
	../cluster/Packets/PacketPtr.h
	../cluster/PluginConfig.h)

set(SOURCES
	Devices/KeyboardMouseDevice/InputArea.cpp
	Devices/KeyboardMouseDevice/KeyboardMouseDevice.cpp
	Devices/Sim/SimAnalog.cpp
	Devices/Sim/SimDigital.cpp
	Devices/Sim/SimDigitalGlove.cpp
	Devices/Sim/SimGloveGesture.cpp
	Devices/Sim/SimInput.cpp
	Devices/Sim/SimPosition.cpp
	Devices/Sim/SimRelativePosition.cpp
	Devices/Sim/SimSetablePosition.cpp
	EventEmitter.cpp
	Event/AbstractEventInterface.cpp
	Event/DigitalEventInterface.cpp
	Event/Event.cpp
	Event/EventGenerator.cpp
	Event/KeyboardMouse/KeyEvent.cpp
	Event/KeyboardMouse/MouseEvent.cpp
	Filter/Position/FullPositionXformFilter.cpp
	Filter/Position/PositionCalibrationFilter.cpp
	Filter/Position/PositionFilterFactory.cpp
	Filter/Position/PositionXformFilter.cpp
	gadgetmain.cpp
	InputLogger.cpp
	InputManager.cpp
	NetworkManager.cpp
	Node.cpp
	ProxyDepChecker.cpp
	ProxyFactory.cpp
	Reactor.cpp
	Type/Analog.cpp
	Type/AnalogProxy.cpp
	Type/BaseTypeFactory.cpp
	Type/Command.cpp
	Type/CommandProxy.cpp
	Type/DeviceFactory.cpp
	Type/DeviceInterface.cpp
	Type/Digital.cpp
	Type/DigitalProxy.cpp
	Type/GestureProxy.cpp
	Type/Glove.cpp
	Type/GloveData.cpp
	Type/GloveGesture.cpp
	Type/GloveProxy.cpp
	Type/Hat.cpp
	Type/HatProxy.cpp
	Type/Input.cpp
	Type/InputData.cpp
	Type/KeyboardMouse.cpp
	Type/KeyboardMouseProxy.cpp
#	Type/LinearSigmoidPositionFilter.cpp # TODO: This file is broken!
	Type/Position.cpp
	Type/PositionProxy.cpp
	Type/Proxy.cpp
	Type/Rumble.cpp
	Type/RumbleEffect.cpp
	Type/RumbleProxy.cpp
	Type/String.cpp
	Type/StringProxy.cpp
	Util/PathHelpers.cpp
	Util/PluginVersionException.cpp
	Util/Version.cpp

	../cluster/ClusterDelta.cpp
	../cluster/ClusterDepChecker.cpp
	../cluster/ClusterException.cpp
	../cluster/ClusterManager.cpp
	../cluster/ClusterPlugin.cpp
	../cluster/ConfigHandler.cpp
	../cluster/Packets/ConfigPacket.cpp
	../cluster/Packets/DataPacket.cpp
	../cluster/Packets/DeviceAck.cpp
	../cluster/Packets/EndBlock.cpp
	../cluster/Packets/Header.cpp
	../cluster/Packets/Packet.cpp
	../cluster/Packets/PacketFactory.cpp)

if(MSVC)
	list(APPEND SOURCES ../gadget.rc)
endif()

set(GADGET_USE_COCOA)
set(GADGET_USE_X11)
if(WIN32)
	message(STATUS "Gadgeteer: Using Win32 native input for keyboard/mouse device")
	list(APPEND SOURCES 
		Devices/KeyboardMouseDevice/InputAreaWin32.cpp
		Devices/KeyboardMouseDevice/InputWindowWin32.cpp)
	list(APPEND HEADERS
		Devices/KeyboardMouseDevice/InputAreaWin32.h
		Devices/KeyboardMouseDevice/InputWindowWin32.h)
elseif(BUILD_WITH_COCOA)
	set(GADGET_USE_COCOA 1)
	message(STATUS "Gadgeteer: Using Cocoa input for keyboard/mouse device")
	list(APPEND SOURCES 
		Devices/KeyboardMouseDevice/InputAreaCocoa.mm
		Devices/KeyboardMouseDevice/InputViewCocoa.mm
		Devices/KeyboardMouseDevice/InputWindowCocoa.mm)
	list(APPEND HEADERS
		Devices/KeyboardMouseDevice/InputAreaCocoa.h
		Devices/KeyboardMouseDevice/InputViewCocoa.h
		Devices/KeyboardMouseDevice/InputWindowCocoa.h)
else()
	set(GADGET_USE_X11 1)
	message(STATUS "Gadgeteer: Using X11 input for keyboard/mouse device")
	list(APPEND SOURCES 
		Devices/KeyboardMouseDevice/InputAreaXWin.cpp
		Devices/KeyboardMouseDevice/InputWindowXWin.cpp)
	list(APPEND HEADERS
		Devices/KeyboardMouseDevice/InputAreaXWin.h
		Devices/KeyboardMouseDevice/InputWindowXWin.h)
endif()

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/gadgetParam.h.in" "${CMAKE_CURRENT_BINARY_DIR}/gadgetParam.h")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/gadgetDefines.h.cmake_in" "${CMAKE_CURRENT_BINARY_DIR}/gadgetDefines.h")
vrjugglersuite_create_version_rc()

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/gadgetParam.h" "${CMAKE_CURRENT_BINARY_DIR}/gadgetDefines.h"
	DESTINATION "${GADGET_INCLUDE_PREFIX}/gadget"
	COMPONENT gadget-dev)

add_library(gadget SHARED ${HEADERS} ${SOURCES})
target_link_libraries(gadget
	${JCCL_LIBRARIES})

if(WIN32)
	target_link_libraries(gadget comctl32)
elseif(GADGET_USE_X11)
	target_link_libraries(gadget ${X11_X11_LIB})
endif()

set_target_properties(gadget PROPERTIES FOLDER "${VRJUGGLERSUITE_CORELIB_PROJECT_FOLDER}")
vrjugglersuite_set_versioned_library_output_name(gadget)

install(TARGETS gadget EXPORT gadgetexport
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT gadget-runtime
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT gadget-runtime
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT gadget-dev)

