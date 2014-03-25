set(TWEEK_IDL_JAVA)
foreach(idlname ${TWEEK_IDL_NAMES})
	java_idlj(idljava "${TWEEK_IDL_DIR}/${idlname}.idl" -i "${CMAKE_CURRENT_SOURCE_DIR}/..")
	list(APPEND TWEEK_IDL_JAVA ${idljava})
endforeach()

add_jar(TweekIDL
	${TWEEK_IDL_JAVA})

if(APPLE)
	set(TWEEK_MAC_SRC org/vrjuggler/tweek/mac/TweekAppListener.java)
else()
	set(TWEEK_MAC_SRC)
endif()

get_filename_component(EXTERNALS "${CMAKE_CURRENT_SOURCE_DIR}/../../../external" ABSOLUTE)
find_jar(JDOM_JAR
	jdom
	PATHS
	${EXTERNALS}/jdom/build)

find_jar(JAXENCORE_JAR
	jaxen-core
	PATHS
	${EXTERNALS}/jdom/lib)
find_jar(JAXENJDOM_JAR
	jaxen-jdom
	PATHS
	${EXTERNALS}/jdom/lib)
find_jar(SAXPATH_JAR
	saxpath
	PATHS
	${EXTERNALS}/jdom/lib)
find_jar(XERXES_JAR
	xerces
	PATHS
	${EXTERNALS}/jdom/lib)
find_jar(XMLAPIS_JAR
	xml-apis
	PATHS
	${EXTERNALS}/jdom/lib)

set(JDOM_JARS
	"${JDOM_JAR}"
	"${JAXENCORE_JAR}"
	"${JAXENJDOM_JAR}"
	"${SAXPATH_JAR}"
	"${XERXES_JAR}"
	"${XMLAPIS_JAR}")
find_jar(LIQUIDLNF_JAR
	liquidlnf
	PATHS
	${EXTERNALS}/swing-laf/liquid/)
find_jar(METOUIA_JAR
	metouia
	PATHS
	${EXTERNALS}/swing-laf/metouia/)
find_jar(JGOODIESLOOKS_JAR
	looks
	PATHS
	${EXTERNALS}/swing-laf/jgoodies-looks/)

set(CMAKE_JAVA_INCLUDE_PATH ${JDOM_JARS} "${LIQUIDLNF_JAR}" "${METOUIA_JAR}" "${JGOODIESLOOKS_JAR}")

get_property(TweekIDLJar TARGET TweekIDL PROPERTY JAR_FILE)
list(APPEND CMAKE_JAVA_INCLUDE_PATH "${TweekIDLJar}")

add_subdirectory("../../../external/swing-laf/kunststoff/sources" kunststoff-mod-build)
get_property(klafjar TARGET kunststoff-mod PROPERTY JAR_FILE)
list(APPEND CMAKE_JAVA_INCLUDE_PATH "${klafjar}")

add_jar(Tweek
	org/vrjuggler/tweek/EnvironmentServiceImpl.java
	org/vrjuggler/tweek/GlobalPreferencesServiceImpl.java
	org/vrjuggler/tweek/Tweek.java
	org/vrjuggler/tweek/TweekCore.java
	org/vrjuggler/tweek/gui/AboutBox.java
	org/vrjuggler/tweek/gui/BeanContainer.java
	org/vrjuggler/tweek/gui/BeanPrefsDialog.java
	org/vrjuggler/tweek/gui/BeanStatusDialog.java
	org/vrjuggler/tweek/gui/DirectConnectionDialog.java
	org/vrjuggler/tweek/gui/DisconnectionDialog.java
	org/vrjuggler/tweek/gui/GlobalPrefsUpdateEvent.java
	org/vrjuggler/tweek/gui/GlobalPrefsUpdateListener.java
	org/vrjuggler/tweek/gui/MessagePanel.java
	org/vrjuggler/tweek/gui/NamingServiceConnectionDialog.java
	org/vrjuggler/tweek/gui/PrefsDialog.java
	org/vrjuggler/tweek/gui/SubjectManagerWrapper.java
	org/vrjuggler/tweek/gui/TweekFrame.java
	org/vrjuggler/tweek/gui/bulb-off-small.gif
	org/vrjuggler/tweek/gui/bulb-on-small.gif
	org/vrjuggler/tweek/gui/tweek-icon.gif
	org/vrjuggler/tweek/gui/tweek.gif
	org/vrjuggler/tweek/text/MessageAdditionEvent.java
	org/vrjuggler/tweek/text/MessageAdditionListener.java
	org/vrjuggler/tweek/text/MessageDocument.java
	org/vrjuggler/tweek/text/error.gif
	org/vrjuggler/tweek/text/status.gif
	org/vrjuggler/tweek/text/warning.gif
	${TWEEK_MAC_SRC}
	LICENSE-java-laf.txt)
add_dependencies(Tweek TweekIDL)
add_dependencies(Tweek kunststoff-mod)
list(REMOVE_ITEM CMAKE_JAVA_INCLUDE_PATH "${klafjar}")

add_jar(TweekBeans
	org/vrjuggler/tweek/beans/BeanAttributes.java
	org/vrjuggler/tweek/beans/BeanDependency.java
	org/vrjuggler/tweek/beans/BeanDependencyManager.java
	org/vrjuggler/tweek/beans/BeanFocusChangeEvent.java
	org/vrjuggler/tweek/beans/BeanFocusChangeListener.java
	org/vrjuggler/tweek/beans/BeanInstantiationCommunicator.java
	org/vrjuggler/tweek/beans/BeanInstantiationEvent.java
	org/vrjuggler/tweek/beans/BeanInstantiationListener.java
	org/vrjuggler/tweek/beans/BeanModelViewer.java
	org/vrjuggler/tweek/beans/BeanPathException.java
	org/vrjuggler/tweek/beans/BeanPreferences.java
	org/vrjuggler/tweek/beans/BeanRegistrationEvent.java
	org/vrjuggler/tweek/beans/BeanRegistrationListener.java
	org/vrjuggler/tweek/beans/BeanRegistry.java
	org/vrjuggler/tweek/beans/BeanTreeModel.java
	org/vrjuggler/tweek/beans/BestSAXChecker.java
	org/vrjuggler/tweek/beans/ClipboardUser.java
	org/vrjuggler/tweek/beans/DefaultBeanModelViewer.java
	org/vrjuggler/tweek/beans/FileFinder.java
	org/vrjuggler/tweek/beans/FileLoader.java
	org/vrjuggler/tweek/beans/GenericBean.java
	org/vrjuggler/tweek/beans/HelpProvider.java
	org/vrjuggler/tweek/beans/JarDependency.java
	org/vrjuggler/tweek/beans/PanelBean.java
	org/vrjuggler/tweek/beans/ServiceBean.java
	org/vrjuggler/tweek/beans/TweekBean.java
	org/vrjuggler/tweek/beans/UndoHandler.java
	org/vrjuggler/tweek/beans/ViewerBean.java
	org/vrjuggler/tweek/beans/XMLBeanFinder.java
	org/vrjuggler/tweek/beans/loader/BeanInstantiationException.java
	org/vrjuggler/tweek/beans/loader/BeanJarClassLoader.java
	org/vrjuggler/tweek/beans/loader/BeanJarFile.java
	org/vrjuggler/tweek/beans/loader/BeanLoader.java)

add_jar(TweekEvents
	org/vrjuggler/tweek/event/EventListenerRegistry.java
	org/vrjuggler/tweek/event/FileActionEvent.java
	org/vrjuggler/tweek/event/FileActionGenerator.java
	org/vrjuggler/tweek/event/FileActionListener.java
	org/vrjuggler/tweek/event/RegistrationEvent.java
	org/vrjuggler/tweek/event/RegistrationListener.java
	org/vrjuggler/tweek/event/TweekFrameAdapter.java
	org/vrjuggler/tweek/event/TweekFrameEvent.java
	org/vrjuggler/tweek/event/TweekFrameListener.java
	org/vrjuggler/tweek/event/UndoActionEvent.java
	org/vrjuggler/tweek/event/UndoActionGenerator.java
	org/vrjuggler/tweek/event/UndoActionListener.java
	org/vrjuggler/tweek/event/UserLevelChangeEvent.java
	org/vrjuggler/tweek/event/UserLevelChangeListener.java)

add_jar(TweekNet
	org/vrjuggler/tweek/net/CommunicationEvent.java
	org/vrjuggler/tweek/net/CommunicationListener.java
	org/vrjuggler/tweek/net/corba/CorbaService.java)
add_dependencies(TweekNet TweekIDL)

add_jar(TweekBeanDelivery
	TweekNet
	TweekBeans
	org/vrjuggler/tweek/beandelivery/BeanDeliveryObserverImpl.java
	org/vrjuggler/tweek/beandelivery/BeanDeliverySubjectUpdateEvent.java
	org/vrjuggler/tweek/beandelivery/BeanDeliverySubjectUpdateListener.java
	org/vrjuggler/tweek/beandelivery/TweekBeanIntrospector.java)
add_dependencies(TweekBeanDelivery TweekNet TweekBeans)

add_jar(TweekServices
	org/vrjuggler/tweek/services/EnvironmentService.java
	org/vrjuggler/tweek/services/EnvironmentServiceProxy.java
	org/vrjuggler/tweek/services/ExtensionFileFilter.java
	org/vrjuggler/tweek/services/GlobalPreferencesService.java
	org/vrjuggler/tweek/services/GlobalPreferencesServiceProxy.java)

add_jar(Viewers
	org/vrjuggler/tweek/treeviewer/BeanSelectionListener.java
	org/vrjuggler/tweek/treeviewer/BeanTree.java
	org/vrjuggler/tweek/treeviewer/BeanTreeViewer.java
	org/vrjuggler/tweek/iconviewer/BeanIconPanel.java
	org/vrjuggler/tweek/iconviewer/BeanIconViewer.java
	org/vrjuggler/tweek/iconviewer/InternalBeanFrame.java
	org/vrjuggler/tweek/iconviewer/PrefsEditor.java
	org/vrjuggler/tweek/iconviewer/PrefsEvent.java
	org/vrjuggler/tweek/iconviewer/PrefsEventListener.java
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/iconviewer/back-small.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/iconviewer/back.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/iconviewer/bean_default.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/iconviewer/bean_folder.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/iconviewer/forward-small.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/iconviewer/forward.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/iconviewer/home-small.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/iconviewer/home.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/LICENSE-java-laf.txt")

# Arguments:
# - metatarget name to create (will also be the install component name)
# - solution folder for the individual targets
# - destination for jars relative to ${CMAKE_BINARY_DIR} and the install dir
# - One or more targets created with add_jar()
function(tweek_create_metatarget _name _slnfolder _dest)
	set(DESTJARS)
	file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/${_dest}/")

	# For each jar target
	foreach(jartarget ${ARGN})
		# Add a solution folder property
		set_target_properties(${jartarget} PROPERTIES FOLDER "${_slnfolder}")

		# Set up custom command to copy finished jar to a more suitable place
		get_property(JAR_${jartarget} TARGET ${jartarget} PROPERTY JAR_FILE)
		set(JAR "${JAR_${jartarget}}")
		get_filename_component(JARNAME "${JAR}" NAME)
		set(DESTJAR "${CMAKE_BINARY_DIR}/${_dest}/${JARNAME}")
		add_custom_command(OUTPUT "${DESTJAR}"
			COMMAND
			"${CMAKE_COMMAND}" -E copy_if_different "${JAR}" "${DESTJAR}"
			DEPENDS
			"${jartarget}"
			COMMENT "Copying ${JARNAME} to ${_dest} in build tree"
			VERBATIM)
		list(APPEND DESTJARS "${DESTJAR}")
	endforeach()

	# Install from our "suitable place" to its equivalent in the install tree
	install(FILES ${DESTJARS}
		DESTINATION "${_dest}" COMPONENT "${_name}")

	# Add the custom meta-target to trigger the jar copying
	add_custom_target(${_name} ALL
		DEPENDS ${DESTJARS} ${ARGN})
	add_dependencies(${_name} ${ARGN})
	set_target_properties(${_name} PROPERTIES FOLDER "Convenience targets")

	# Clean up our copied jars, too
	set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${DESTJARS})
endfunction()

tweek_create_metatarget(tweek_java
	"Tweek Java API"
	"${TWEEK_SHARE_DIR}/java"
	kunststoff-mod
	TweekIDL
	Tweek
	TweekBeanDelivery
	TweekBeans
	TweekEvents
	TweekNet
	TweekServices)

tweek_create_metatarget(tweek_beans
	"Tweek Beans"
	"${TWEEK_SHARE_DIR}/beans"
	Viewers)

# XML file for beans directory
vrjugglersuite_copy_and_install(TWEEK_BEANS_COPIED_FILES
	"${TWEEK_SHARE_DIR}/beans"
	tweek_beans
	"${CMAKE_CURRENT_SOURCE_DIR}/Viewers.xml")

add_custom_target(tweek_copy_xml
	DEPENDS ${TWEEK_BEANS_COPIED_FILES})
set_target_properties(tweek_copy_xml PROPERTIES FOLDER "Tweek Beans")
add_dependencies(tweek_beans tweek_copy_xml)

# Look at our classpath and copy any dependencies that we're using our local copy of.
foreach(jar ${CMAKE_JAVA_INCLUDE_PATH})
	string(FIND "${jar}" "${EXTERNALS}" FROMEXTERNALS)
	string(FIND "${jar}" "${CMAKE_CURRENT_BINARY_DIR}" FROMBUILD)
	if(FROMEXTERNALS EQUAL 0 OR FROMBUILD EQUAL 0)
		# OK, this is a file from our "externals" or our build folder - must install it.
		list(APPEND BUNDLED_JAR_DEPENDENCIES "${jar}")
	else()
		message(FATAL_ERROR "Used system JAR: ${jar} - TODO")
	endif()
endforeach()

vrjugglersuite_copy_and_install(TWEEK_COPIED_FILES
	"${TWEEK_SHARE_DIR}/java"
	tweek_java
	${BUNDLED_JAR_DEPENDENCIES}
	"${CMAKE_CURRENT_SOURCE_DIR}/java.security.policy.txt")

add_custom_target(tweek_copy_jar_deps
	DEPENDS ${TWEEK_COPIED_FILES})
set_target_properties(tweek_copy_jar_deps PROPERTIES FOLDER "Tweek Java API")
add_dependencies(tweek_java tweek_copy_jar_deps)


set(BUILDTREE_CLASSPATH ${TWEEK_COPIED_FILES})
foreach(target
	kunststoff-mod
	Tweek
	TweekBeanDelivery
	TweekBeans
	TweekEvents
	TweekNet
	TweekServices)
	list(APPEND BUILDTREE_CLASSPATH "${CMAKE_BINARY_DIR}/${TWEEK_SHARE_DIR}/java/${target}.jar")
endforeach()

set(TWEEK_JAVA_CLASSPATH ${BUILDTREE_CLASSPATH} CACHE INTERNAL "" FORCE)
