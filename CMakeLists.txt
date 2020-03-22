cmake_minimum_required(VERSION 3.16.0)

project(net CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(ENABLE_TESTS "Enable unit tests" ON)
option(BUILD_SAMPLES "Build provided samples" ON)
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)

include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
conan_basic_setup(TARGETS)

# Code Coverage Configuration
add_subdirectory(addons/codecov)

add_subdirectory(utils)
add_subdirectory(publisher)
add_subdirectory(subscriber)
add_subdirectory(client)

if (BUILD_SAMPLES)
    add_subdirectory(publisher/samples/simple)
    add_subdirectory(subscriber/samples/simple)
endif ()

if (ENABLE_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(utils/tests)
    add_subdirectory(client/tests)
endif ()
