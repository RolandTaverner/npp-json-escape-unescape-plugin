# About

This is Notepad++ plugin for escaping/unescaping JSON strings.

# Functions

## Escape

Plain simple JSON escape.

`sample "string"\` => `"sample \"string\"\\"`

`{"a": "test"}` => `"{\"a\": \"test\"}"`

And so on.

## Unescape

Plain simple JSON unescape, but it can unescape both `some string` and `"some string"`.

Input MUST be valid JSON escaped string.

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

Examples:
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

Open npp-jsonutils-plugin/vs.proj/NppJsonEscapeUnescapePlugin.sln

## Update jsoncpp .vcxproj file (note for myself)
```
rm -rf npp-jsonutils-plugin/3rdparty/jsoncppbuild
mkdir npp-jsonutils-plugin/3rdparty/jsoncppbuild
cd npp-jsonutils-plugin/3rdparty/jsoncppbuild
cmake ..\jsoncpp -G "Visual Studio 17 2022"
```
Add Win32 platform.

