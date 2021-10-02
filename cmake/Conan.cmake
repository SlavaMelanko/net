macro(run_conan)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
    list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

    # Download automatically, you can also just copy the conan.cmake file.
    if (NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
        file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake"
        )
    endif ()

    include(${CMAKE_BINARY_DIR}/conan.cmake)

    conan_cmake_configure(
        REQUIRES
            cli11/2.0.0
            concurrentqueue/1.0.3
            cppzmq/4.8.1
            fmt/8.0.1
            gtest/cci.20210126
            ms-gsl/3.1.0
            nlohmann_json/3.10.2
            spdlog/1.9.2
        GENERATORS
            cmake_find_package_multi
    )

    foreach(TYPE ${CMAKE_CONFIGURATION_TYPES})
        conan_cmake_autodetect(settings BUILD_TYPE ${TYPE})
        conan_cmake_install(
            PATH_OR_REFERENCE .
            BUILD missing
            REMOTE conancenter
            SETTINGS ${settings}
        )
    endforeach()

    find_package(CLI11 CONFIG)
    find_package(concurrentqueue CONFIG)
    find_package(cppzmq CONFIG)
    find_package(fmt CONFIG)
    find_package(GTest CONFIG)
    find_package(Microsoft.GSL CONFIG)
    find_package(nlohmann_json CONFIG)
    find_package(spdlog CONFIG)
endmacro()
