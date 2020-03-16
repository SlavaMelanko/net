cmake_minimum_required(VERSION 3.16.0)

project(net CXX)

option(ENABLE_TESTING "Enable unit tests" ON)
option(BUILD_SAMPLES "Build samples" ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
conan_basic_setup(TARGETS)

add_subdirectory(utils)
add_subdirectory(publisher)
add_subdirectory(subscriber)
add_subdirectory(client)

if(BUILD_SAMPLES)
    add_subdirectory(publisher/samples/simple)
    add_subdirectory(subscriber/samples/simple)
endif()


