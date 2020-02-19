cmake_minimum_required(VERSION 3.16.0)

project(server CXX)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        CONAN_PKG::cppzmq
        CONAN_PKG::fmt
)

target_link_options(${PROJECT_NAME}
    PRIVATE
        "/ignore:4099" # warning LNK4099: PDB '.pdb' was not found ...
)
