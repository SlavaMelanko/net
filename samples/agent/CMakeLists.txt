cmake_minimum_required(VERSION 3.16.0)

project(agent-sample CXX)

add_executable(${PROJECT_NAME}
    AgentApp.cpp
    AgentApp.h
    main.cpp
    NotificationConnection.cpp
    NotificationConnection.h
    PayloadConnection.cpp
    PayloadConnection.h
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        CONAN_PKG::CLI11
        CONAN_PKG::cppzmq
        CONAN_PKG::fmt
        CONAN_PKG::spdlog
        net::client
        net::subscriber
)

target_link_options(${PROJECT_NAME}
    PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:
            /ignore:4099 # warning LNK4099: PDB '.pdb' was not found ...
        >
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER samples)
