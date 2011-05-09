#!/bin/sh

export OpenCV_DIR=../../../opencv/release

if [ ! -f "CMakeLists.txt" ];
then
	echo "CMakeLists.txt file missing !"
	exit 1
fi

cmake CMakeLists.txt
make

if [ -f "exec.out" ];
then
	LD_PRELOAD=/usr/lib/libv4l/v4l2convert.so ./exec.out
fi

