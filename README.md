# Network Project

| Release | Build Status | Code Quality | Code Coverage | Repo Info
| :---: | :---: | :---: | :---: | :---: |
| [![GitHub version](https://badge.fury.io/gh/SlavaMelanko%2Fnet.svg)](https://badge.fury.io/gh/SlavaMelanko%2Fnet) | [![macOS](https://img.shields.io/github/workflow/status/SlavaMelanko/net/macOS/master.svg?style=flat&logo=apple&label=macOS)](https://github.com/SlavaMelanko/net/actions?query=workflow%3AmacOS) [![Windows](https://img.shields.io/github/workflow/status/SlavaMelanko/net/Windows/master.svg?style=flat&logo=windows&label=Windows)](https://github.com/SlavaMelanko/net/actions?query=workflow%3AWindows) [![Ubuntu](https://img.shields.io/github/workflow/status/SlavaMelanko/net/Ubuntu/master.svg?style=flat&logo=linux&label=Ubuntu&logoColor=white)](https://github.com/SlavaMelanko/net/actions?query=workflow%3AUbuntu) | [![Sonar Quality Gate](https://img.shields.io/sonar/quality_gate/SMelanko_net?label=SonarCloud&logo=sonarcloud&server=https%3A%2F%2Fsonarcloud.io)](https://sonarcloud.io/dashboard?id=SMelanko_net) [![CodeFactor Grade](https://img.shields.io/codefactor/grade/github/SlavaMelanko/net?label=CodeFactor&logo=codefactor)](https://www.codefactor.io/repository/github/SlavaMelanko/net) [![Codacy Grade](https://img.shields.io/codacy/grade/e1cb282988f94e5f9625d48b2312b3ee?label=Codacy&logo=codacy)](https://www.codacy.com/gh/SMelanko/net/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=SMelanko/net&amp;utm_campaign=Badge_Grade) [![LGTM Grade: C++](https://img.shields.io/lgtm/grade/cpp/github/SlavaMelanko/net?label=LGTM&logo=lgtm&logoColor=white)](https://lgtm.com/projects/g/SlavaMelanko/net/context:cpp) | [![Codecov](https://codecov.io/gh/SlavaMelanko/net/branch/master/graph/badge.svg)](https://codecov.io/gh/SlavaMelanko/net) | ![GitHub repo size](https://img.shields.io/github/repo-size/SlavaMelanko/net?label=Repo%20Size&logo=github) ![Lines of code](https://img.shields.io/tokei/lines/github/SlavaMelanko/net?label=Lines%20of%20Code&logo=github) |

## 🧰 Set Up Development Environment

> ☝️ The latest versions is the best choice.

- [CMake](https://cmake.org/)
- [Conan Package Manager](https://conan.io/)
- C++ compiler (including 17 standard)

For more details, please look at [workflows](./.github/workflows) directory.

## 🛠️ How To Build

- **macOS with Xcode**
    - Run [python](https://www.python.org/downloads/) `cmakegen.py` script to make the project, e.g.
        ```bash
        >_ python3 cmakegen.py -t
        ```
    - Go to the build directory
    - Open `net.xcodeproj`
    - Build the project

- **Windows with Visual Studio**
    - Run [python](https://www.python.org/downloads/) `cmakegen.py` script to make the project
    - Go to the build directory
    - Open `net.sln`
    - Build the project

- **Ubuntu with CLion or QtCreator**
    - Launch IDE
    - Find the project directory and select it
        - In the QtCreator you have to choose the root `CMakeLists.txt`

## 🖤 Contribution

### Code Principle

- Keep it simple!

### Code Style

Please use [ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) tool to automatically format C++ code using rules from the [.clang-format](./.clang-format) file.
