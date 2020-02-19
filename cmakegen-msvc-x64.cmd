@echo off

set BUILD_DIR=.\build

echo [INFO] Creating a build directory...

if not exist %BUILD_DIR% mkdir %BUILD_DIR%

pushd %BUILD_DIR%

echo [Conan] Downloading third-party packages...

conan install ^
    --build missing ^
    -s build_type=Debug ^
    -s compiler="Visual Studio" ^
    -s compiler.version=16 ^
    ..

if errorlevel 1 goto :error

conan install ^
    --build missing ^
    -s build_type=Release ^
    -s compiler="Visual Studio" ^
    -s compiler.version=16 ^
    ..

if errorlevel 1 goto :error

echo [CMake] Generating the project...

cmake ^
    -G "Visual Studio 16 2019" -A x64 ^
    ..

if errorlevel 1 goto :error

echo Project has been generated successfully!
popd

goto :eof

:error
echo [ERROR] Failed to generate the project.
popd
exit /b 1