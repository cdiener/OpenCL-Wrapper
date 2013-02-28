#-----------------------------------------------------------------------------
#  OCL-Library
#-----------------------------------------------------------------------------

cmake_minimum_required(VERSION 2.8)

project(OCL_Library)


set(SPADES_APP_NAME "SPADES : Simple  plug-ins")
find_package(OpenCL REQUIRED)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${OPENCL_INCLUDE_DIRS})
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")


if (MSVC)
   add_definitions( -D_CRT_SECURE_NO_WARNINGS  -W3 )
endif(MSVC)


# OCL Library is defined as a separate archive
add_library(OCL_Library STATIC ocl.cpp ocl.h)

# example 1
add_executable(example1  example1.cpp)
target_link_libraries(example1 OCL_Library ${OPENCL_LIBRARIES})


#example2
add_executable(example2  example2.cpp)
target_link_libraries(example2 OCL_Library ${OPENCL_LIBRARIES})

#example3
add_executable(example3  example3.cpp)
target_link_libraries(example3 OCL_Library ${OPENCL_LIBRARIES})

install(TARGETS example1 example2 example3
        DESTINATION bin)

install(FILES vectoradd.cl
        DESTINATION bin)
