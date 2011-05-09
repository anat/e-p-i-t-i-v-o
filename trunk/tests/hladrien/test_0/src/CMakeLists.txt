
cmake_minimum_required(VERSION 2.6)

project( test_0_project )

ADD_DEFINITIONS( -Wall -W )

find_package( OpenCV REQUIRED )

INCLUDE_DIRECTORIES( 
	#
)

ADD_EXECUTABLE( exec.out
	main.cpp
	#calibration.cpp
	#camshiftdemo.cpp
)

TARGET_LINK_LIBRARIES( exec.out
	${OpenCV_LIBS}
)
