
project(nedges)
cmake_minimum_required(VERSION 2.8)

# Add the main source directory to the include path
include_directories(${CMAKE_SOURCE_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory (Participants)
add_subdirectory (Events)
add_subdirectory (Output)
add_subdirectory (Test)



