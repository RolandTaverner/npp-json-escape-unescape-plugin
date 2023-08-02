# About

This is Notepad++ plugin for escaping/unescaping JSON strings.

# Installation

TL;DR [Official plugin installation HOWTO](https://npp-user-manual.org/docs/plugins/)

Open [Releases page](https://github.com/RolandTaverner/npp-json-escape-unescape-plugin/releases) to see all releases.

## 32-bit (x86) Notepad++

Download the latest 32-bit version (`Release_x86.zip`).

Unzip the `Release_x86.zip` to `%PROGRAMFILES(x86)%\Notepad++\plugins\NppJsonEscapeUnescapePlugin\NppJsonEscapeUnescapePlugin.dll`.

Usually `%PROGRAMFILES(x86)%` = `C:\Program Files (x86)`.

## 64-bit (x86-64) Notepad++

Download the latest 64-bit version (`Release_x64.zip`).

Unzip the `Release_x64.zip` to `%PROGRAMFILES%\Notepad++\plugins\NppJsonEscapeUnescapePlugin\NppJsonEscapeUnescapePlugin.dll`.

Usually `%PROGRAMFILES%` = `C:\Program Files`.

# Functions

## Escape

Plain simple JSON escape.

### Examples

`sample "string"\` => `"sample \"string\"\\"`

`{"a": "test"}` => `"{\"a\": \"test\"}"`

And so on.

## Unescape

Plain simple JSON unescape, but it can unescape both `some string` and `"some string"`.

Input MUST be valid JSON escaped string.

### Examples

`"test \"string\"\\n"` => `test "string"\n`

`test \"string\"\\n` => `test "string"\n`

`{\"a\": \"123\\n\"}` => `{"a": "123\n"}`

And so on.

## Recursive unescape

This is a bit tricky.

If input is `"some string"` or `some string` it behaves as simple unescape (see above).

If input is valid JSON (like `{"a": 1}`) or valid escaped JSON (like `"{\"a\": \"string\"}"` with or without outer quotes), it does:
- Parse input to JSON
- Recursively traverse all nodes
- For string nodes try parse string content as JSON and replace string value with object value

### Examples

`"{\"a\": \"string\"}"` => `{"a":"string"}`

`{\"a\": \"string\"}` => `{"a":"string"}` (same as above but without outer quotes)

`"{\"a\":1,\"b\":\"{\\\"c\\\": 1}\"}"` => `{"a":1,"b":{"c":1}}`

`{"a": "{\"b\":\"{\\\"c\\\": \\\"string\\\"}\"}"}` => `{"a":{"b":{"c":"string"}}}`

And so on.

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

Open `npp-json-escape-unescape-plugin/vs.proj/NppJsonEscapeUnescapePlugin.sln`.

## Update jsoncpp .vcxproj file (note for myself)
```
rm -rf npp-json-escape-unescape-plugin/3rdparty/jsoncppbuild
mkdir npp-json-escape-unescape-plugin/3rdparty/jsoncppbuild
cd npp-json-escape-unescape-plugin/3rdparty/jsoncppbuild
cmake ..\jsoncpp -G "Visual Studio 17 2022"
```
Add Win32 platform.

