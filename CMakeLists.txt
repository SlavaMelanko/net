cmake_minimum_required(VERSION 3.16.0)

project(net CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(ENABLE_TESTS "Enable unit tests" ON)
option(BUILD_SAMPLES "Build provided samples" ON)
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)

# Code Coverage Configuration
add_library(coverage_config INTERFACE)
add_library(coverage::config ALIAS coverage_config)
if (ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(coverage_config INTERFACE
        -O0        # no optimization
        -g         # generate debug info
        --coverage # sets all required flags
    )
    target_link_options(coverage_config INTERFACE --coverage)
endif ()

include(${CMAKE_BINARY_DIR}/conanbuildinfo_multi.cmake)
conan_basic_setup(TARGETS)

#add_subdirectory(addons/codecov)

add_subdirectory(utils)
add_subdirectory(publisher)
add_subdirectory(subscriber)
add_subdirectory(client)

if (BUILD_SAMPLES)
    add_subdirectory(publisher/samples/simple)
    add_subdirectory(subscriber/samples/simple)
endif ()
