SET(app_name
	epitivo
)
SET(app_bin_dir
	../../bin
)
#SET(app_path
#	${app_bin_dir}/${app_name} 
#)
SET(headers
	GUILoader.hpp
)
SET(sources
	main.cpp
	GUILoader.cpp
)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/source)


SET(QT_USE_QTMAIN TRUE)
INCLUDE(${QT_USE_FILE})

ADD_EXECUTABLE(${app_name} 
	${headers}
	${sources}
)
TARGET_LINK_LIBRARIES(${app_name}
	view
	${QT_LIBRARIES}
)

