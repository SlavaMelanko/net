cmake_minimum_required(VERSION 3.16.0)

project(zmq CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
conan_basic_setup(TARGETS)

add_subdirectory(foundation)
add_subdirectory(client)
add_subdirectory(server)
