project(coverage_config)

add_library(${PROJECT_NAME} INTERFACE)

add_library(coverage::config ALIAS ${PROJECT_NAME})

if (ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(${PROJECT_NAME} INTERFACE
        -O0        # no optimization
        -g         # generate debug info
        --coverage # sets all required flags
    )
    target_link_options(${PROJECT_NAME} INTERFACE --coverage)
endif ()
