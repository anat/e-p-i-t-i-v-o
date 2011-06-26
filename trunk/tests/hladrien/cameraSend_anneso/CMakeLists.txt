
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project( cameraSend )

INCLUDE(InstallRequiredSystemLibraries)

ADD_DEFINITIONS( -Wall -W )

find_package( OpenCV REQUIRED )
FIND_PACKAGE(Qt4     REQUIRED)

SET(app_name cameraSend.out)
SET(headers
)
SET(moc_headers
	imageview.h
	mainwindow.h
)
SET(sources
	main.cpp
	imageview.cpp
	mainwindow.cpp
)
SET(forms
	imageview.ui
	mainwindow.ui
)
SET(resources
)

QT4_WRAP_CPP(moc_generated ${moc_headers})
QT4_WRAP_UI(forms_generated ${forms})
QT4_ADD_RESOURCES(rc_generated ${resources})

INCLUDE_DIRECTORIES(
        ${CMAKE_CURRENT_BINARY_DIR}
)

SOURCE_GROUP("Generated Files" REGULAR_EXPRESSION "(moc_.*cxx|ui_.*h|qrc_.*cxx)$")
SOURCE_GROUP("UI Files" REGULAR_EXPRESSION ".*.ui$")
SOURCE_GROUP("RC Files" REGULAR_EXPRESSION ".*.qrc$")

INCLUDE(${QT_USE_FILE})

ADD_EXECUTABLE( ${app_name}
 	${headers} ${moc_headers} ${sources} ${forms} ${moc_generated} ${forms_generated} ${rc_generated}
)

TARGET_LINK_LIBRARIES( ${app_name}
	${OpenCV_LIBS}
	${QT_LIBRARIES}
)
