cmake_minimum_required(VERSION 3.16.0)

project(subscriber CXX)

add_library(${PROJECT_NAME})
add_library(net::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        include/ISubscriber.h
        include/ZmqSubscriber.h
        src/ZmqSubscriber.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
        .. # for zhelpers.hpp
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        CONAN_PKG::cppzmq
        net::utils
    PRIVATE
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
)

target_link_options(${PROJECT_NAME}
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:
            /ignore:4099 # warning LNK4099: PDB '.pdb' was not found ...
        >
)
