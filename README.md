# Network Project

| Version | Windows | macOS & Linux | Code Quality | Code Coverage |
| :---: | :---: | :---: | :---: | :---: |
| [![GitHub version](https://badge.fury.io/gh/SMelanko%2Fnet.svg)](https://badge.fury.io/gh/SMelanko%2Fnet) | [![Build status](https://ci.appveyor.com/api/projects/status/hl6u3jinuhpq0w88?svg=true)](https://ci.appveyor.com/project/SMelanko/net) | [![Build Status](https://travis-ci.com/SMelanko/net.svg?branch=master)](https://travis-ci.com/SMelanko/net) | [![CodeFactor](https://www.codefactor.io/repository/github/smelanko/net/badge)](https://www.codefactor.io/repository/github/smelanko/net) | [![codecov](https://codecov.io/gh/SMelanko/net/branch/master/graph/badge.svg)](https://codecov.io/gh/SMelanko/net) |

## Contribution

### Code Formatting

[ClangFormat](https://clang.llvm.org/docs/ClangFormat.html) is a tool to automatically format C++ code.

```bash
find . -name '*.h' -or -name '*.cpp' -not -path "./build/*" | xargs -I {} sh -c 'echo {}; clang-format -style=file -i {};'
```
