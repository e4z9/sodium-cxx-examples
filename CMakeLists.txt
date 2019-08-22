cmake_minimum_required(VERSION 3.5)

project(sodium-cxx-examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

find_package(SodiumCxx REQUIRED)
find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

add_subdirectory(qt)
add_subdirectory(examples)
