
cmake_minimum_required(VERSION 2.6)

project( app )

add_definitions( -Wall -W )

find_package( Qt4 	REQUIRED )
# find_package( OpenCV 	REQUIRED )

SET(APP_NAME app)

SET(app_SOURCES 
	sources/main.cpp 
	sources/mainwindow.cpp
)
# header needing moc only !!
SET(app_HEADERS 
	mainwindow.h
)
SET(app_FORMS 
	# hellowindow.ui
)
SET(app_RESOURCES 
	application.qrc
)

QT4_WRAP_CPP(app_HEADERS_MOC ${test_qt_HEADERS})
QT4_WRAP_UI(app_FORMS_HEADERS ${test_qt_FORMS})
QT4_ADD_RESOURCES(app_RESOURCES_RCC ${test_qt_RESOURCES})

# set your module use
 #SET(QT_USE_QTCORE	TRUE)
#SET(QT_USE_QTGUI	TRUE)
SET(QT_DONT_USE_QTCORE FALSE)
SET(QT_DONT_USE_QTGUI FALSE)
INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(
        headers
	${QT_INCLUDE_DIR}
)
SET(QT_DEFINITIONS) 
ADD_DEFINITIONS(${QT_DEFINITIONS})

add_executable(${APP_NAME}
	${app_SOURCES}
	${app_HEADERS_MOC}
	${app_FORMS_HEADERS}
	${app_RESOURCES_RCC}
)

target_link_libraries(${APP_NAME}
	#${OpenCV_LIBS}
	${QT_LIBRARIES}
)

message(STATUS "QT_INCLUDE_DIR : " ${QT_INCLUDE_DIR})
message(STATUS "QT_USE_FILE : " ${QT_USE_FILE})
message(STATUS "QT_DEFINITIONS : " ${QT_DEFINITIONS})
message(STATUS "QT_LIBRARIES : " ${QT_LIBRARIES})
