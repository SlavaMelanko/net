cmake_minimum_required(VERSION 3.16.0)

project(sciter CXX)

set(SCITER_ROOT $ENV{SCITERSDK})
set(SCITER_BIN $ENV{SCITERSDK}/bin)

set(SCITER_MAIN_SOURCE_NAME
    $<$<CXX_COMPILER_ID:MSVC>:sciter-win-main.cpp>
    $<$<CXX_COMPILER_ID:Clang>:sciter-osx-main.mm>
)

set(SCITER_MAIN_SOURCE_PATH ${SCITER_ROOT}/include/${SCITER_MAIN_SOURCE_NAME})

set(SCITER_DYNAMIC_LIBRARY_PATH
    $<$<CXX_COMPILER_ID:MSVC>:${SCITER_BIN}/windows/x64/sciter.dll>
    $<$<CXX_COMPILER_ID:Clang>:${SCITER_BIN}/macosx/libsciter.dylib>
)

add_executable(${PROJECT_NAME} WIN32
    ${SCITER_MAIN_SOURCE_PATH}
    main.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${SCITER_ROOT}/include
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        fmt::fmt
)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
    COMMAND ${SCITER_BIN}/windows/packfolder.exe
        ${CMAKE_CURRENT_SOURCE_DIR}/ui
        ${CMAKE_CURRENT_SOURCE_DIR}/sciter-resources.cpp
        -v "resources"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SCITER_DYNAMIC_LIBRARY_PATH}
        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}
)

if (WIN32)
    set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DPI_AWARE "PerMonitor")
endif ()
