# Network Project

| Version | Build Status | Code Quality | Code Coverage | Repo Info
| :---: | :---: | :---: | :---: | :---: |
| [![GitHub version](https://badge.fury.io/gh/SMelanko%2Fnet.svg)](https://badge.fury.io/gh/SMelanko%2Fnet) | [![macOS](https://img.shields.io/github/workflow/status/SMelanko/net/macOS/master.svg?style=flat&logo=apple&label=macOS)](https://github.com/SMelanko/net/actions?query=workflow%3AmacOS) [![Windows](https://img.shields.io/github/workflow/status/SMelanko/net/Windows/master.svg?style=flat&logo=windows&label=Windows)](https://github.com/SMelanko/net/actions?query=workflow%3AWindows) [![Ubuntu](https://img.shields.io/github/workflow/status/SMelanko/net/Ubuntu/master.svg?style=flat&logo=linux&label=Ubuntu&logoColor=white)](https://github.com/SMelanko/net/actions?query=workflow%3AUbuntu) | [![CodeFactor Grade](https://img.shields.io/codefactor/grade/github/SMelanko/net?label=CodeFactor&logo=codefactor)](https://www.codefactor.io/repository/github/smelanko/net) [![Codacy grade](https://img.shields.io/codacy/grade/e1cb282988f94e5f9625d48b2312b3ee?label=Codacy&logo=codacy)](https://www.codacy.com/gh/SMelanko/net/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=SMelanko/net&amp;utm_campaign=Badge_Grade) [![LGTM Grade: C++](https://img.shields.io/lgtm/grade/cpp/github/SMelanko/net?label=LGTM&logo=lgtm&logoColor=white)](https://lgtm.com/projects/g/SMelanko/net/context:cpp) | [![Codecov](https://codecov.io/gh/SMelanko/net/branch/master/graph/badge.svg)](https://codecov.io/gh/SMelanko/net) | ![GitHub repo size](https://img.shields.io/github/repo-size/SMelanko/net?label=Repo%20Size&logo=github) ![Lines of code](https://img.shields.io/tokei/lines/github/SMelanko/net?label=Lines%20of%20Code&logo=github) |

## Setup Development Environment

Prerequisites:

- [CMake](https://cmake.org/)
- [Conan Package Manager](https://conan.io/)
- C++ compiler (including 17 standard)

For more details, please look at [worflows](./.github/workflows) directory.

## How to Build and Run

- **macOS with Xcode**
    - Run `cmakegen.py` script using python3 to generate the project
    - Go to the build directory
    - Open `net.xcodeproj`
    - Build the project

- **Windows with Visual Studio**
    - Run `cmakegen.py` script using python3 to generate the project
    - Go to the build directory
    - Open `net.sln`
    - Build the project

- **Ubuntu with CLion or QtCreator**
    - Launch IDE
    - Find the project directory and select it
        - In the QtCreator you have to choose the root `CMakeLists.txt`

## Contribution

### Code Principles

- Keep it simple

### Code Style

[ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) is a tool to automatically format C++ code.

```bash
find . -name '*.h' -or -name '*.cpp' -not -path "./build/*" | \
    xargs -I {} sh -c 'echo {}; clang-format -style=file -i {};'
```
