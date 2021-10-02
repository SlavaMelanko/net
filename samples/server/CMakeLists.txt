cmake_minimum_required(VERSION 3.16.0)

project(server-sample CXX)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        CLI11::CLI11
        cppzmq::cppzmq
        fmt::fmt
        spdlog::spdlog
        net::server
)

target_link_options(${PROJECT_NAME}
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:
            /ignore:4099 # warning LNK4099: PDB '.pdb' was not found ...
        >
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER samples)
