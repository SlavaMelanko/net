# Network Project

| Version | Windows | macOS & Linux | Code Quality | Code Coverage |
| :---: | :---: | :---: | :---: | :---: |
| [![GitHub version](https://badge.fury.io/gh/SMelanko%2Fnet.svg)](https://badge.fury.io/gh/SMelanko%2Fnet) | [![Build status](https://ci.appveyor.com/api/projects/status/hl6u3jinuhpq0w88?svg=true)](https://ci.appveyor.com/project/SMelanko/net) | [![Build Status](https://travis-ci.com/SMelanko/net.svg?branch=master)](https://travis-ci.com/SMelanko/net) | [![CodeFactor](https://www.codefactor.io/repository/github/smelanko/net/badge)](https://www.codefactor.io/repository/github/smelanko/net) | [![codecov](https://codecov.io/gh/SMelanko/net/branch/master/graph/badge.svg)](https://codecov.io/gh/SMelanko/net) |

## Setup Development Environment

Prerequisites:

- [CMake](https://cmake.org/)
- [Conan package manager](https://conan.io/)
- C++ compiler (including 17 standard)

For more details, please look at [travis](./.travis.yml) or [appveyor](./.appveyor.yml) script.

## How to Build and Run

- **macOS**
    - Run `cmakegen-xcode.sh` script to generate project
    - Go to the build directory
    - Open `net.xcodeproj`
    - Build project

- **Windows**
    - Run `cmakegen-msvc-x64.cmd` script to generate project
    - Go to the build directory
    - Open `net.sln`
    - Build project

## Contribution

### Code Principles

- Keep it simple

### Code Style

[ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) is a tool to automatically format C++ code.

```bash
find . -name '*.h' -or -name '*.cpp' -not -path "./build/*" | \
    xargs -I {} sh -c 'echo {}; clang-format -style=file -i {};'
```
