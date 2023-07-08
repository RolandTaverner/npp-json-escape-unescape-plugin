# About

This (will be) a plugin for unescaping JSON strings with (optionally) recursive unescape.

TODO

# How to build

## Prerequisites

Visual Studio 17 2022
- Desktop development with C++
  - WIndows SDK
  - C++ CMake tools for windows
- Python development
  - Python 3
  
TODO

`git clone https://github.com/RolandTaverner/npp-jsonutils-plugin.git`

```
mkdir npp-jsonutils-plugin/3rdparty/jsoncppbuild
cd npp-jsonutils-plugin/3rdparty/jsoncppbuild
cmake ..\jsoncpp -G "Visual Studio 17 2022"
```

Open npp-jsonutils-plugin/vs.proj/NppJsonUtilsPlugin.sln
