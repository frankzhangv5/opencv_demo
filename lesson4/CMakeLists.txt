cmake_minimum_required(VERSION 2.8)
project( ImageROILinearBlending )
add_compile_options(-g)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( ImageROILinearBlending ImageROILinearBlending.cpp )
target_link_libraries( ImageROILinearBlending ${OpenCV_LIBS} )
