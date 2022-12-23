cmake_minimum_required(VERSION 3.16.0)

project(sciter CXX)

set(SCITER_ROOT $ENV{SCITERSDK})
set(SCITER_BIN $ENV{SCITERSDK}/bin)

add_executable(${PROJECT_NAME} WIN32
    main.cpp
    sciter-win-main.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${SCITER_ROOT}/include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        fmt::fmt
)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${SCITER_BIN}/windows/packfolder.exe
        ${CMAKE_CURRENT_SOURCE_DIR}/ui
        ${CMAKE_CURRENT_SOURCE_DIR}/resources.cpp
        -v "resources"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SCITER_BIN}/windows/x64/sciter.dll
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DPI_AWARE "PerMonitor")
