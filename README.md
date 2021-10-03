# Network Project

| Version | Windows | macOS | Ubuntu | Code Quality | Code Coverage |
| :---: | :---: | :---: | :---: | :---: | :---: |
| [![GitHub version](https://badge.fury.io/gh/SMelanko%2Fnet.svg)](https://badge.fury.io/gh/SMelanko%2Fnet) | [![Windows](https://github.com/SMelanko/net/workflows/Windows/badge.svg)](https://github.com/SMelanko/net/actions?query=workflow%3AWindows) | [![Build Status](https://travis-ci.com/SMelanko/net.svg?branch=master)](https://travis-ci.com/SMelanko/net)<br />[![macOS](https://github.com/SMelanko/net/workflows/macOS/badge.svg)](https://github.com/SMelanko/net/actions?query=workflow%3AmacOS) | [![Build Status](https://travis-ci.com/SMelanko/net.svg?branch=master)](https://travis-ci.com/SMelanko/net)<br />[![Ubuntu](https://github.com/SMelanko/net/workflows/Ubuntu/badge.svg)](https://github.com/SMelanko/net/actions?query=workflow%3AUbuntu) | [![CodeFactor](https://www.codefactor.io/repository/github/smelanko/net/badge)](https://www.codefactor.io/repository/github/smelanko/net) | [![codecov](https://codecov.io/gh/SMelanko/net/branch/master/graph/badge.svg)](https://codecov.io/gh/SMelanko/net) |

## Setup Development Environment

Prerequisites:

- [CMake](https://cmake.org/)
- [Conan Package Manager](https://conan.io/)
- C++ compiler (including 17 standard)

For more details, please look at [worflows](./.github/workflows) directory.

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
