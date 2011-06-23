SET(lib_name vm)

SET(headers
	MainWindowVM.hpp
	CentralVM.hpp
	BottomBarVM.hpp
)
SET(sources
	MainWindowVM.cpp
	CentralVM.cpp
	BottomBarVM.cpp
)

INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}/source
	${CMAKE_CURRENT_BINARY_DIR}
)


INCLUDE(${QT_USE_FILE})

ADD_LIBRARY(${lib_name} 
	${headers}
	${sources}
)

SET_TARGET_PROPERTIES(${lib_name} 
	PROPERTIES PROJECT_LABEL "libvm"
)

TARGET_LINK_LIBRARIES(${lib_name}
	#model 
	${QT_LIBRARIES}
)

