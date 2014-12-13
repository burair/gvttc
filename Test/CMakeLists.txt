set (nedges_EXE_SRCS mainwindow.cpp main.cpp)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt4)

INCLUDE(${QT_USE_FILE})

include_directories(${nedges_SOURCE_DIR} ${QT_INCLUDE_DIR})

add_executable(nedges ${nedges_EXE_SRCS})
target_link_libraries(nedges ${QT_LIBRARIES} Events Players Galois boost_date_time hpdf)
