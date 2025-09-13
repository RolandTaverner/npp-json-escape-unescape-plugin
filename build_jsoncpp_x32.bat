SETLOCAL

call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

cmake 3rdparty\jsoncpp -DJSONCPP_WITH_TESTS=OFF -DJSONCPP_WITH_POST_BUILD_UNITTEST=OFF -DJSONCPP_STATIC_WINDOWS_RUNTIME=ON -DBUILD_SHARED_LIBS=OFF -DBUILD_OBJECT_LIBS=OFF -DJSONCPP_WITH_PKGCONFIG_SUPPORT=OFF -DCMAKE_CONFIGURATION_TYPES=Debug;Release -A Win32 -B "3rdparty\jsoncppbuild\build_Win32"

cmake --build "3rdparty\jsoncppbuild\build_Win32" --config Debug
cmake --build "3rdparty\jsoncppbuild\build_Win32" --config Release

ENDLOCAL
