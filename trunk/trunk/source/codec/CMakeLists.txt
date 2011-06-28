SET(lib_name videoCodec)

SET(headers
	VideoCodec.hpp
)
SET(sources
	VideoCodec.cpp
)

INCLUDE_DIRECTORIES(
  ${CMAKE_SOURCE_DIR}/source
	${CMAKE_CURRENT_BINARY_DIR}
)

ADD_LIBRARY(${lib_name} 
	${headers}
	${sources}
)
