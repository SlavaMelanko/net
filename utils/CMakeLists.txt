cmake_minimum_required(VERSION 3.16.0)

project(utils CXX)

add_library(${PROJECT_NAME})
add_library(net::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE
        include/ConcurrentQueue.h
        include/Json.h
        include/Log.h
        include/Randomizer.h
        src/Json.cpp
        src/Log.cpp
        src/Randomizer.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        include
        .. # for zhelpers.hpp
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        concurrentqueue::concurrentqueue
        fmt::fmt
        nlohmann_json::nlohmann_json
        spdlog::spdlog
        coverage::config
)

target_link_options(${PROJECT_NAME}
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:
            /ignore:4099 # warning LNK4099: PDB '.pdb' was not found ...
        >
)
