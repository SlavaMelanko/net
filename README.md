# Network Project

| Version | Build Status | Code Quality | Code Coverage |
| :---: | :---: | :---: | :---: |
| [![GitHub version](https://badge.fury.io/gh/SMelanko%2Fnet.svg)](https://badge.fury.io/gh/SMelanko%2Fnet) | [![macOS](https://img.shields.io/github/workflow/status/SMelanko/net/macOS/master.svg?style=flat&logo=apple&label=macOS)](https://github.com/SMelanko/net/actions?query=workflow%3AmacOS) [![Windows](https://img.shields.io/github/workflow/status/SMelanko/net/Windows/master.svg?style=flat&logo=windows&label=Windows)](https://github.com/SMelanko/net/actions?query=workflow%3AWindows) [![Ubuntu](https://img.shields.io/github/workflow/status/SMelanko/net/Ubuntu/master.svg?style=flat&logo=linux&label=Ubuntu)](https://github.com/SMelanko/net/actions?query=workflow%3AUbuntu) | ![CodeFactor Grade](https://img.shields.io/codefactor/grade/github/SMelanko/net?label=CodeFactor) | [![codecov](https://codecov.io/gh/SMelanko/net/branch/master/graph/badge.svg)](https://codecov.io/gh/SMelanko/net) |

## Setup Development Environment

Prerequisites:

- [CMake](https://cmake.org/)
- [Conan Package Manager](https://conan.io/)
- C++ compiler (including 17 standard)

For more details, please look at [worflows](./.github/workflows) directory.

## How to Build and Run

- **macOS**
    - Run `cmakegen.py` script using python3 to generate the project
    - Go to the build directory
    - Open `net.xcodeproj`
    - Build the project

- **Windows**
    - Run `cmakegen.py` script using python3 to generate the project
    - Go to the build directory
    - Open `net.sln`
    - Build the project

## Contribution

### Code Principles

- Keep it simple

### Code Style

[ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) is a tool to automatically format C++ code.

```bash
find . -name '*.h' -or -name '*.cpp' -not -path "./build/*" | \
    xargs -I {} sh -c 'echo {}; clang-format -style=file -i {};'
```
