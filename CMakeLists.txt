cmake_minimum_required(VERSION 3.1.0)

project(qtzmq)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(VERSION 0.1)

# Extra modules for cmake
#-------------------------------------------------------------------------------

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_PREFIX_PATH "~/Qt/5.15.0/clang_64/" 
  "~/Documents/projects/libzmq/installation/" 
  "~/Documents/projects/cppzmq/install/"
  "~/Documents/projects/msgpack-c/install/")

#------------------------------------------------------------------------------

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(msgpack)
find_package(cppzmq)

# Compile target
#------------------------------------------------------------------------------

add_executable(server
    src/main.cpp
    src/mainwindow.cpp
    src/drape_thread.cpp)

add_executable(client
    src/client.cpp)

include_directories(src)
include_directories(${EIGEN3_INCLUDE_DIR})
target_link_libraries(server Qt5::Widgets cppzmq msgpackc-static)
target_link_libraries(client cppzmq msgpackc-static)
