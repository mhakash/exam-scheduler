cmake_minimum_required(VERSION 3.15.0)
project(main VERSION 1.0.0)
include(CTest)
enable_testing()

add_library(progress progress.h)
add_library(node node.h node.cpp)
add_library(fileutil file-utility.h file-utility.cpp)
add_library(graph graph.h graph.cpp)

add_executable(main main.cpp node progress)
target_link_libraries(main fileutil graph)
target_link_libraries(graph node)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++17")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set_target_properties(progress PROPERTIES LINKER_LANGUAGE CXX)

include(CPack)