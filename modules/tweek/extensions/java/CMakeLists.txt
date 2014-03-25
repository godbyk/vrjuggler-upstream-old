
get_filename_component(EXTERNALS "${CMAKE_CURRENT_SOURCE_DIR}/../../../../external" ABSOLUTE)
find_jar(TABLELAYOUT_JAR
	TableLayout
	PATHS
	${EXTERNALS}/TableLayout)

set(CMAKE_JAVA_INCLUDE_PATH ${TWEEK_JAVA_CLASSPATH} "${TABLELAYOUT_JAR}")

add_jar(ui
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/ui/package.html"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/ui/treetable/package.html"
	org/vrjuggler/tweek/ui/JTreeTable.java
	org/vrjuggler/tweek/ui/PropertySheet.java
	org/vrjuggler/tweek/ui/PropertySheetCellEditor.java
	org/vrjuggler/tweek/ui/PropertySheetTableModel.java
	org/vrjuggler/tweek/ui/treetable/AbstractTreeTableModel.java
	org/vrjuggler/tweek/ui/treetable/TreeTableModel.java
	org/vrjuggler/tweek/ui/treetable/TreeTableModelAdapter.java)

add_jar(wizard
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/wizard/builder/images/add16.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/wizard/builder/images/down16.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/wizard/builder/images/new24.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/wizard/builder/images/open24.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/wizard/builder/images/preview24.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/wizard/builder/images/remove16.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/wizard/builder/images/save24.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/wizard/builder/images/saveas24.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/wizard/builder/images/up16.gif"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/wizard/images/juggler_sidebar.png"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/wizard/package.html"
	"${CMAKE_CURRENT_SOURCE_DIR}/org/vrjuggler/tweek/wizard/panes/package.html"
	org/vrjuggler/tweek/wizard/AbstractWizardStep.java
	org/vrjuggler/tweek/wizard/builder/PropertySheet.java
	org/vrjuggler/tweek/wizard/builder/PropertySheetCellEditor.java
	org/vrjuggler/tweek/wizard/builder/PropertySheetTableModel.java
	org/vrjuggler/tweek/wizard/builder/WizardBuilder.java
	org/vrjuggler/tweek/wizard/builder/WizardBuilderTreeModel.java
	org/vrjuggler/tweek/wizard/builder/WizardStepChooserDialog.java
	org/vrjuggler/tweek/wizard/builder/WizardStepFinder.java
	org/vrjuggler/tweek/wizard/panes/WelcomePane.java
	org/vrjuggler/tweek/wizard/RootWizardSequence.java
	org/vrjuggler/tweek/wizard/Wizard.java
	org/vrjuggler/tweek/wizard/WizardInputStream.java
	org/vrjuggler/tweek/wizard/WizardIterator.java
	org/vrjuggler/tweek/wizard/WizardLoader.java
	org/vrjuggler/tweek/wizard/WizardOutputStream.java
	org/vrjuggler/tweek/wizard/WizardPane.java
	org/vrjuggler/tweek/wizard/WizardSequence.java
	org/vrjuggler/tweek/wizard/WizardStep.java
	org/vrjuggler/tweek/wizard/WizardStepEvent.java
	org/vrjuggler/tweek/wizard/WizardStepFactory.java
	org/vrjuggler/tweek/wizard/WizardStepIterator.java
	org/vrjuggler/tweek/wizard/WizardStepListener.java
	org/vrjuggler/tweek/wizard/WizardView.java
	org/vrjuggler/tweek/wizard/WizardViewerBean.java
	org/vrjuggler/tweek/wizard/WizardViewEvent.java
	org/vrjuggler/tweek/wizard/WizardViewListener.java)


# Set up custom command to copy finished jar to a more suitable place

foreach(JARTARGET ui wizard)
	add_dependencies(${JARTARGET} tweek_java)
	set_target_properties(${JARTARGET} PROPERTIES FOLDER "Tweek Java Extensions")
	get_property(JAR TARGET ${JARTARGET} PROPERTY JAR_FILE)
	vrjugglersuite_copy_and_install(TWEEK_EXT_COPIED_FILES
		"${TWEEK_SHARE_DIR}/java"
		tweek_java_extensions
		"${JAR}")
endforeach()

add_custom_target(tweek_java_extensions DEPENDS ui wizard ${TWEEK_EXT_COPIED_FILES})
add_dependencies(tweek_java_extensions ui wizard)
set_target_properties(tweek_java_extensions PROPERTIES FOLDER "Convenience targets")

set(TWEEK_EXT_BUILDTREE_JARS ${TWEEK_EXT_COPIED_FILES} CACHE INTERNAL "" FORCE)
