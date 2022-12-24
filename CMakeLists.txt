cmake_minimum_required(VERSION 3.16.0)

project(net
    VERSION 0.0.1
    DESCRIPTION "My Network Project"
    LANGUAGES CXX
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(BUILD_UI "Enable Sciter UI" OFF)
option(BUILD_TESTS "Enable unit tests" ON)
option(BUILD_SAMPLES "Build provided samples" OFF)
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)

include(cmake/Conan.cmake)
run_conan()

# Code Coverage Configuration
add_subdirectory(addons/codecov)

add_subdirectory(utils)
add_subdirectory(publisher)
add_subdirectory(subscriber)
add_subdirectory(client)
add_subdirectory(server)

if (WIN32 AND BUILD_UI)
    add_subdirectory(ui-sciter)
endif ()

if (BUILD_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(utils/tests)
    add_subdirectory(publisher/tests)
    add_subdirectory(subscriber/tests)
    add_subdirectory(client/tests)
    add_subdirectory(server/tests)
endif ()

if (BUILD_SAMPLES)
    add_subdirectory(samples/publisher)
    add_subdirectory(samples/subscriber)
    add_subdirectory(samples/client)
    add_subdirectory(samples/server)
    add_subdirectory(samples/agent)
    add_subdirectory(samples/service)
endif ()
