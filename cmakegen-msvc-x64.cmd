@echo off

set BUILD_DIR=.\build

echo [INFO] Creating a build directory...

if not exist %BUILD_DIR% mkdir %BUILD_DIR%
pushd %BUILD_DIR%

echo [CMake] Generating the project...

cmake -G "Visual Studio 16 2019" -A x64 ..

if errorlevel 1 goto :error

echo Project has been generated successfully!
popd

goto :eof

:error
echo [ERROR] Failed to generate the project.
popd
exit /b 1
