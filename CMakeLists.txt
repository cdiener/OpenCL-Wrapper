#-----------------------------------------------------------------------------
#  OCL-Library
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8)

project(OCL_Library)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}")

find_package(OpenCL REQUIRED)

add_definitions(-Wall)

include_directories(${OPENCL_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})

# OCL Library is defined as a separate archive
add_library(OCL_Library src/ocl.cpp src/ocl.h)

# example 1
add_executable(example1  src/example1.cpp)
target_link_libraries(example1 OCL_Library ${OPENCL_LIBRARIES})

#example2
add_executable(example2  src/example2.cpp)
target_link_libraries(example2 OCL_Library ${OPENCL_LIBRARIES})

#example3
add_executable(example3  src/example3.cpp)
target_link_libraries(example3 OCL_Library ${OPENCL_LIBRARIES})

file(COPY src/vectoradd.cl DESTINATION .)


