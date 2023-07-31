# About

This (will be) a plugin for unescaping JSON strings with (optionally) recursive unescape.

# Functions

## Escape

Plain simple JSON escape.

`sample "string"\` => `"sample \"string\"\\"`

`{"a": "test"}` => `"{\"a\": \"test\"}"`

And so on.

## Unescape

Plain simple JSON unescape, but it can unescape both `some string` and `"somee string"`.

Input MUST be valid JSON escaped string.

`"test \"string\"\\n"` => `test "string"\n`

`test \"string\"\\n` => `test "string"\n`

`{\"a\": \"123\\n\"}` => `{"a": "123\n"}`

And so on.

## Recursive unescape

TODO


# How to build

## Prerequisites

Visual Studio 17 2022
- Desktop development with C++
  - WIndows SDK
  - C++ CMake tools for windows
- Python development
  - Python 3
  
## Get the code

`git clone https://github.com/RolandTaverner/npp-json-escape-unescape-plugin.git`

Open npp-jsonutils-plugin/vs.proj/NppJsonEscapeUnescapePlugin.sln

## Update jsoncpp .vcxproj file (note for myself)
```
rm -rf npp-jsonutils-plugin/3rdparty/jsoncppbuild
mkdir npp-jsonutils-plugin/3rdparty/jsoncppbuild
cd npp-jsonutils-plugin/3rdparty/jsoncppbuild
cmake ..\jsoncpp -G "Visual Studio 17 2022"
```
Add Win32 platform.

