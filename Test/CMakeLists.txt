set (nedges_EXE_SRCS main.cpp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt4)

INCLUDE(${QT_USE_FILE})

include_directories(${nedges_SOURCE_DIR} ${QT_INCLUDE_DIR})
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
SET(BUILD_SHARED_LIBS OFF)
SET(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(nedges ${nedges_EXE_SRCS})
target_link_libraries(nedges Events Players Galois boost_date_time mysqlcppconn-static)
