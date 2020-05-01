cmake_minimum_required(VERSION 3.16.0)

project(net
    VERSION 0.0.1
    DESCRIPTION "My Network Project"
    LANGUAGES CXX
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(ENABLE_TESTS "Enable unit tests" ON)
option(BUILD_SAMPLES "Build provided samples" ON)
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
add_subdirectory(broker)
add_subdirectory(worker)

if (ENABLE_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(utils/tests)
    add_subdirectory(publisher/tests)
    add_subdirectory(subscriber/tests)
    add_subdirectory(client/tests)
    add_subdirectory(server/tests)
    add_subdirectory(broker/tests)
    add_subdirectory(worker/tests)
endif ()

if (BUILD_SAMPLES)
    add_subdirectory(samples/publisher)
    add_subdirectory(samples/subscriber)
    add_subdirectory(samples/client)
    add_subdirectory(samples/server)
    add_subdirectory(samples/broker)
    add_subdirectory(samples/worker)
endif ()
