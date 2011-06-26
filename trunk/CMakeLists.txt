CMAKE_MINIMUM_REQUIRED(VERSION 2.8 FATAL_ERROR)

PROJECT(Epitivo)

INCLUDE(InstallRequiredSystemLibraries)

# Set up the environment
FIND_PACKAGE(Qt4 	REQUIRED)
FIND_PACKAGE(OpenCV 	REQUIRED)

# Handle all the code
#ADD_SUBDIRECTORY(source/libmodel)
ADD_SUBDIRECTORY(source/libvm)
ADD_SUBDIRECTORY(source/libview)
ADD_SUBDIRECTORY(source/app)
