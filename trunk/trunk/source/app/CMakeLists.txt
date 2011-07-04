SET(app_name
	epitivo
)
SET(app_bin_dir
	../..
)
SET(app_path
	${app_bin_dir}/${app_name} 
)
SET(headers
	GUILoader.hpp
	ConfigManager.hpp
	MediaFile.hpp
)
SET(sources
	main.cpp
	GUILoader.cpp
	ConfigManager.cpp
	MediaFile.cpp
)

INCLUDE_DIRECTORIES(
    ${CMAKE_SOURCE_DIR}/source
    ${CMAKE_SOURCE_DIR}/source/libview
    ${CMAKE_SOURCE_DIR}/source/libvm
)

SET(QT_USE_QTMAIN TRUE)
INCLUDE(${QT_USE_FILE})

ADD_EXECUTABLE(${app_path} 
	${headers}
	${sources}
)
TARGET_LINK_LIBRARIES(${app_path}
  vm
	view
	${QT_LIBRARIES}
)

