cmake_minimum_required(VERSION 3.16.0)

project(utils CXX)

add_library(${PROJECT_NAME}
    include/Log.h
    include/Randomizer.h
    src/Log.cpp
    src/Randomizer.cpp
)

add_library(net::utils ALIAS ${PROJECT_NAME})

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
        .. # for zhelpers.hpp
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        coverage_config
)

target_link_options(${PROJECT_NAME}
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:
            /ignore:4099 # warning LNK4099: PDB '.pdb' was not found ...
        >
)

if (ENABLE_TESTS)
    include(CTest)
    enable_testing()
    add_subdirectory(tests)
endif ()
