macro(run_conan)
    # Download automatically, you can also just copy the conan.cmake file.
    if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.15/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
        )
    endif ()

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_cmake_run(
        REQUIRES
            CLI11/1.9.0@cliutils/stable
            concurrentqueue/1.0.1
            cppzmq/4.6.0
            fmt/6.1.2
            gtest/1.10.0
            ms-gsl/2.0.0
            nlohmann_json/3.7.3
            spdlog/1.5.0
        BASIC_SETUP CMAKE_TARGETS
        CONFIGURATION_TYPES "Release;Debug"
        BUILD missing
    )
endmacro()
