if(BUILD_JAVA)
	set(CMAKE_JAVA_INCLUDE_PATH ${TWEEK_JAVA_CLASSPATH})
	###
	# jccl_config
	add_jar(jccl_config
		"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/jccl/config/event/package.html"
		"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/jccl/config/io/package.html"
		"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/jccl/config/package.html"
		"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/jccl/config/undo/package.html"
		"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/jccl/config/images/jugglerlogo.jpg"
		org/vrjuggler/jccl/config/Category.java
		org/vrjuggler/jccl/config/ConfigBroker.java
		org/vrjuggler/jccl/config/ConfigBrokerImpl.java
		org/vrjuggler/jccl/config/ConfigBrokerProxy.java
		org/vrjuggler/jccl/config/ConfigContext.java
		org/vrjuggler/jccl/config/ConfigDefinition.java
		org/vrjuggler/jccl/config/ConfigDefinitionRepository.java
		org/vrjuggler/jccl/config/ConfigElement.java
		org/vrjuggler/jccl/config/ConfigElementFactory.java
		org/vrjuggler/jccl/config/ConfigElementPointer.java
		org/vrjuggler/jccl/config/ConfigUndoManager.java
		org/vrjuggler/jccl/config/Configuration.java
		org/vrjuggler/jccl/config/ConfigUtilities.java
		org/vrjuggler/jccl/config/DataSource.java
		org/vrjuggler/jccl/config/DefinitionLookupException.java
		org/vrjuggler/jccl/config/event/ConfigBrokerEvent.java
		org/vrjuggler/jccl/config/event/ConfigBrokerListener.java
		org/vrjuggler/jccl/config/event/ConfigContextEvent.java
		org/vrjuggler/jccl/config/event/ConfigContextListener.java
		org/vrjuggler/jccl/config/event/ConfigDefinitionAdapter.java
		org/vrjuggler/jccl/config/event/ConfigDefinitionEvent.java
		org/vrjuggler/jccl/config/event/ConfigDefinitionListener.java
		org/vrjuggler/jccl/config/event/ConfigDefinitionRepositoryAdapter.java
		org/vrjuggler/jccl/config/event/ConfigDefinitionRepositoryEvent.java
		org/vrjuggler/jccl/config/event/ConfigDefinitionRepositoryListener.java
		org/vrjuggler/jccl/config/event/ConfigElementAdapter.java
		org/vrjuggler/jccl/config/event/ConfigElementEvent.java
		org/vrjuggler/jccl/config/event/ConfigElementListener.java
		org/vrjuggler/jccl/config/event/ConfigElementPointerEvent.java
		org/vrjuggler/jccl/config/event/ConfigElementPointerListener.java
		org/vrjuggler/jccl/config/event/ConfigEvent.java
		org/vrjuggler/jccl/config/event/ConfigListener.java
		org/vrjuggler/jccl/config/event/PropertyDefinitionAdapter.java
		org/vrjuggler/jccl/config/event/PropertyDefinitionEvent.java
		org/vrjuggler/jccl/config/event/PropertyDefinitionListener.java
		org/vrjuggler/jccl/config/FileDataSource.java
		org/vrjuggler/jccl/config/io/ConfigDefinitionConstants.java
		org/vrjuggler/jccl/config/io/ConfigDefinitionParser.java
		org/vrjuggler/jccl/config/io/ConfigDefinitionReader.java
		org/vrjuggler/jccl/config/io/ConfigDefinitionWriter.java
		org/vrjuggler/jccl/config/io/ConfigElementParser.java
		org/vrjuggler/jccl/config/io/ConfigIOConstants.java
		org/vrjuggler/jccl/config/io/ConfigSchemaResolver.java
		org/vrjuggler/jccl/config/io/ConfigurationParser.java
		org/vrjuggler/jccl/config/io/ConfigurationReader.java
		org/vrjuggler/jccl/config/io/ConfigurationWriter.java
		org/vrjuggler/jccl/config/io/DefinitionFilenameFilter.java
		org/vrjuggler/jccl/config/io/MissingAttributeException.java
		org/vrjuggler/jccl/config/io/ParseException.java
		org/vrjuggler/jccl/config/PropertyDefinition.java
		org/vrjuggler/jccl/config/PropertyValueDefinition.java
		org/vrjuggler/jccl/config/ResourceChooser.java
		org/vrjuggler/jccl/config/SwingWorker.java
		org/vrjuggler/jccl/config/undo/ConfigContextEdit.java
		org/vrjuggler/jccl/config/undo/ConfigElementNameEdit.java
		org/vrjuggler/jccl/config/undo/ConfigElementPropertyEdit.java
		org/vrjuggler/jccl/config/undo/ConfigElementPropertyValueAddEdit.java
		org/vrjuggler/jccl/config/undo/ConfigElementPropertyValueIndexEdit.java
		org/vrjuggler/jccl/config/undo/ConfigElementPropertyValueRemoveEdit.java)
	add_dependencies(jccl_config tweek_java)
	set_target_properties(jccl_config PROPERTIES FOLDER "JCCL Java")
	get_property(JAR TARGET jccl_config PROPERTY JAR_FILE)
	list(APPEND CMAKE_JAVA_INCLUDE_PATH ${JAR})

	###
	# jccl_rtrc
	get_filename_component(CORBARTRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../plugins/corba_rtrc" ABSOLUTE)

	java_idlj(JCCL_CORBARTRC_JAVA "${CORBARTRC_DIR}/idl/RemoteReconfigSubject.idl" -i "${CORBARTRC_DIR}" -i "${CMAKE_CURRENT_SOURCE_DIR}/../../tweek")
	add_jar(jccl_rtrc
		${CORBARTRC_DIR}/org/vrjuggler/jccl/rtrc/RTRCDataSource.java
		${CORBARTRC_DIR}/org/vrjuggler/jccl/rtrc/RTRCDataSourceBroker.java
		${CORBARTRC_DIR}/org/vrjuggler/jccl/rtrc/RTRCDataSourceBrokerImpl.java
		${CORBARTRC_DIR}/org/vrjuggler/jccl/rtrc/RTRCDataSourceBrokerProxy.java
		${JCCL_CORBARTRC_JAVA})
	set_target_properties(jccl_rtrc PROPERTIES FOLDER "JCCL Java")
	add_dependencies(jccl_rtrc jccl_config)

	###
	# jccl_editors
	list(APPEND CMAKE_JAVA_INCLUDE_PATH "${TABLELAYOUT_JAR}" ${TWEEK_EXT_BUILDTREE_JARS})

	string(FIND "${TABLELAYOUT_JAR}" "${EXTERNALS}" FINDRESULT)
	if(FINDRESULT EQUAL 0)
		# OK, this is a file from our "externals" folder - must install it.
		vrjugglersuite_copy_and_install(JCCL_COPIED_FILES
			"${JCCL_SHARE_DIR}/java"
			jccl_java
			"${TABLELAYOUT_JAR}")
	else()
		message(FATAL_ERROR "Used system JAR: ${jar} - TODO")
	endif()
	#get_filename_component(EDITORS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../editors" ABSOLUTE)
	set(EDITORS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../editors")
	add_jar(jccl_editors
		jccl_config
		ui
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/BooleanEditor.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/ConfigContextEditor.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/ConfigContextModel.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/ConfigDefinitionChooser.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/ConfigDefinitionEditor.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/ConfigDefinitionPropertySheet.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/ConfigDefinitionRepositoryEditor.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/ConfigDefinitionRepositoryModel.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/ConfigDefinitionTableModel.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/ConfigElementCellEditor.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/ConfigElementPointerEditor.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/ConfigElementPropertySheet.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/ConfigElementTreeTableModel.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/CustomEditor.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/CustomEditorRegistry.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/DataFlavorRepository.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/ElementTree.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/EmbeddedElementPanel.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/EnumeratedPropertyValueEditor.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/event/ConfigElementSelectionEvent.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/event/ConfigElementSelectionListener.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/event/package.html
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/ExpandablePanel.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/FloatEditor.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/GenericConfigEditor.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/images/Back16.gif
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/images/category.gif
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/images/collapse_property.gif
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/images/configchunk.gif
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/images/config_element.gif
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/images/Copy16.gif
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/images/Cut16.gif
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/images/Delete16.gif
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/images/Down16.gif
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/images/expand_property.gif
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/images/Forward16.gif
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/images/New16.gif
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/images/newcategory.gif
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/images/Paste16.gif
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/images/property.gif
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/images/removecategory.gif
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/images/Up16.gif
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/IntegerEditor.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/net/TinyBrowser.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/package.html
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/PropertyComponent.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/PropertyDefinitionEditor.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/PropertyDefinitionEditorRegistry.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/PropertyEditorPanel.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/PropertySheet.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/PropertySheetFactory.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/StringEditor.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/TransferableConfigElement.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/ValuetypeEditor.java
		${EDITORS_DIR}/org/vrjuggler/jccl/editors/VarListPanel.java)

	add_dependencies(jccl_editors jccl_config ui tweek_java_extensions)
	set_target_properties(jccl_editors PROPERTIES FOLDER "JCCL Java")

	# Set up custom command to copy finished jar to a more suitable place
	foreach(JARTARGET jccl_config jccl_rtrc jccl_editors)
		get_property(JAR TARGET ${JARTARGET} PROPERTY JAR_FILE)
		vrjugglersuite_copy_and_install(JCCL_COPIED_FILES
			"${JCCL_SHARE_DIR}/beans"
			jccl_java
			"${JAR}")
	endforeach()

	set(JCCL_JAVA_CLASSPATH ${TWEEK_JAVA_CLASSPATH} ${TWEEK_EXT_BUILDTREE_JARS} ${JCCL_COPIED_FILES} CACHE INTERNAL "" FORCE)

	vrjugglersuite_copy_and_install(JCCL_COPIED_XML
		"${JCCL_SHARE_DIR}/beans"
		jccl_java
		"${CMAKE_CURRENT_SOURCE_DIR}/jccl_config.xml"
		"${CORBARTRC_DIR}/jccl_rtrc.xml")

	# Add the custom meta-target to trigger the jar copying
	add_custom_target(jccl_java ALL
		DEPENDS ${JCCL_COPIED_FILES} jccl_config jccl_rtrc jccl_editors)
	set_target_properties(jccl_java PROPERTIES FOLDER "Convenience targets")
endif()
