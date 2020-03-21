cmake_minimum_required(VERSION 3.16.0)

project(net CXX)

option(ENABLE_TESTS "Enable unit tests" ON)
if (ENABLE_TESTS)
    include(CTest)
    enable_testing()
endif ()

option(BUILD_SAMPLES "Build samples" OFF)

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
conan_basic_setup(TARGETS)

# Code Coverage Configuration
add_library(coverage_config INTERFACE)

option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
if (ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(coverage_config INTERFACE
        -O0        # no optimization
        -g         # generate debug info
        --coverage # sets all required flags
    )
    target_link_options(coverage_config INTERFACE --coverage)
endif ()

add_subdirectory(utils)
add_subdirectory(publisher)
add_subdirectory(subscriber)
add_subdirectory(client)

if (BUILD_SAMPLES)
    add_subdirectory(publisher/samples/simple)
    add_subdirectory(subscriber/samples/simple)
endif ()
