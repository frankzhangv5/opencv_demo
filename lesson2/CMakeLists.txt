cmake_minimum_required(VERSION 2.8)
project( ImageROI )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( ImageROI ImageROI.cpp )
target_link_libraries( ImageROI ${OpenCV_LIBS} )
