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

## Do a security audit

Since this is some random repo from random guy do not trust it.

### Check git externals

`.gitmodules` should contain reference to official JsonCpp repo ( https://github.com/open-source-parsers/jsoncpp.git ).

### Check *.bat files

`build_jsoncpp_x32.bat` and `build_jsoncpp_x64.bat` should contain only build-related commands.

### Read the code

Well, just do it. Its tiny. There should be no suspicious things like network operations, process creation, obfuscated stuff and so on.

## Prerequisites

Visual Studio 17 2022
- Desktop development with C++
  - WIndows SDK
  - C++ CMake tools for windows
- Python development
  - Python 3
  
## Get the code

`git clone https://github.com/RolandTaverner/npp-json-escape-unescape-plugin.git`

## Build JsonCpp's static libraries

You can build 32 bit, 64 bit library versions or both if you need them all.

If you installed Visual Studio to non-standard location change path to `vcvarsall.bat` at the beginning of `build_jsoncpp_x32.bat` and `build_jsoncpp_x64.bat`. Also you can open VS 2022 x64 tools console and run commands manually without explicit call to `vcvarsall.bat`.

### 32 bit

Run `build_jsoncpp_x32.bat`. 

After successful build there should be files located at
- `npp-json-escape-unescape-plugin\3rdparty\jsoncppbuild\build_Win32\lib\Debug\jsoncpp.lib`
- `npp-json-escape-unescape-plugin\3rdparty\jsoncppbuild\build_Win32\lib\Release\jsoncpp.lib`

### 64 bit

Run `build_jsoncpp_x64.bat`.

After successful build there should be files located at
- `npp-json-escape-unescape-plugin\3rdparty\jsoncppbuild\build_x64\lib\Debug\jsoncpp.lib`
- `npp-json-escape-unescape-plugin\3rdparty\jsoncppbuild\build_x64\lib\Release\jsoncpp.lib`

## Open solution

Solution file located at `npp-json-escape-unescape-plugin/vs.proj/NppJsonEscapeUnescapePlugin.sln`

## Enjoy

# Thanks to

## Don Ho

The author of the famous lovely [Notepad++](https://notepad-plus-plus.org).

## JsonCpp community

Authors and maintainers of [JsonCpp](https://github.com/open-source-parsers/jsoncpp) library.

## Rajendra Singh

The author of [URL plugin](https://github.com/SinghRajenM/nppURLPlugin) which I used as a reference.

## molsonkiko

The author of the [JsonTools plugin](https://github.com/molsonkiko/JsonToolsNppPlugin) which I use every day.
