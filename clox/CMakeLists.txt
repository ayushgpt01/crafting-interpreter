cmake_minimum_required(VERSION 3.10.0)
project(clox VERSION 0.1.0 LANGUAGES C CXX)

# Set C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source directory to include paths
include_directories(${CMAKE_SOURCE_DIR}/src)

# Add all .cpp files inside src
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(clox main.cpp ${SOURCES})

