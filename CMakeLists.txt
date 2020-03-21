cmake_minimum_required(VERSION 3.16.0)

project(net CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(ENABLE_TESTS "Enable unit tests" ON)
option(BUILD_SAMPLES "Build samples" ON)
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
include(CodeCoverageConfiguration)

include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
conan_basic_setup(TARGETS)

add_subdirectory(utils)
add_subdirectory(publisher)
add_subdirectory(subscriber)
add_subdirectory(client)

if (BUILD_SAMPLES)
    add_subdirectory(publisher/samples/simple)
    add_subdirectory(subscriber/samples/simple)
endif ()
