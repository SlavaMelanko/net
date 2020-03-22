cmake_minimum_required(VERSION 3.12.0)

project(publisher-tests CXX)

file(GLOB_RECURSE ${PROJECT_NAME}_SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SOURCES})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        CONAN_PKG::gtest
        net::publisher
)

add_test(NAME publisher COMMAND ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER tests)
