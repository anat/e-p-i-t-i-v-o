SET(lib_name view)

SET(headers
)
SET(moc_headers
	MainWindow.hpp
	CentralView.hpp
        CameraView.hpp
	PlayerView.hpp
	DeviceSelectView.hpp
        playlistwidget.hpp
)
SET(sources
	MainWindow.cpp
	CentralView.cpp
        CameraView.cpp
        PlayerView.cpp
        playlistwidget.cpp
	DeviceSelectView.cpp
)

SET(forms
	MainWindow.ui
	CentralView.ui
        CameraView.ui
	PlayerView.ui
	DeviceSelectView.ui
        playlistwidget.ui
)
SET(resources
	resources.qrc
)

QT4_WRAP_CPP(moc_generated ${moc_headers})
QT4_WRAP_UI(forms_generated ${forms})
QT4_ADD_RESOURCES(rc_generated ${resources})

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}/source
	${CMAKE_CURRENT_BINARY_DIR}
)

SOURCE_GROUP("Generated Files" REGULAR_EXPRESSION "(moc_.*cxx|ui_.*h|qrc_.*cxx)$")
SOURCE_GROUP("UI Files" REGULAR_EXPRESSION ".*.ui$")
SOURCE_GROUP("RC Files" REGULAR_EXPRESSION ".*.qrc$")

INCLUDE(${QT_USE_FILE})

ADD_LIBRARY(${lib_name} 
	${headers} ${moc_headers} ${sources} ${forms} ${moc_generated} ${forms_generated} ${rc_generated}
)
SET_TARGET_PROPERTIES(${lib_name} 
	PROPERTIES PROJECT_LABEL "libview"
)
TARGET_LINK_LIBRARIES(${lib_name} 
  vm	
	${QT_LIBRARIES}
)
