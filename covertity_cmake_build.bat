@set ABI=armeabi-v7a
set covertiy_path=D:\ProgramFiles\cov-analysis-win64-2021.03\bin\cov-build

@if DEFINED ANDROID_NDK_ROOT (
    @set ANDROID_NDK=%ANDROID_NDK_ROOT%
) else (
    @set ANDROID_NDK=C:\Users\Admin\AppData\Local\Android\sdk\ndk-bundle
)
@if DEFINED ANDROID_SDK_ROOT (
    @set CMAKE=%ANDROID_SDK_ROOT%\cmake\3.18.1\bin\cmake.exe
) else (
    @set CMAKE=C:\Users\Admin\AppData\Local\Android\sdk\cmake\3.18.1\bin\cmake.exe
)
@cd %~dp0
@set BUILD_DIR=_build_%ABI%

if not exist %BUILD_DIR% (
    @rd /s /q %BUILD_DIR%
    @mkdir %BUILD_DIR% 
)

@cd %BUILD_DIR%

@%CMAKE% -G "Unix Makefiles" ^
  -DCMAKE_TOOLCHAIN_FILE=%ANDROID_NDK%\build\cmake\android.toolchain.cmake ^
  -DANDROID_ABI=%ABI% ^
  -DANDROID_NATIVE_API_LEVEL=16 ^
  -DCMAKE_MAKE_PROGRAM=%ANDROID_NDK%\prebuilt\windows-x86_64\bin\make.exe ^
  -DANDROID_STL=c++_static ^
  -DCMAKE_BUILD_TYPE=Debug ^
  -DCMAKE_C_FLAGS_DEBUG="-g -O0" ^
  -DCMAKE_CXX_FLAGS_DEBUG="-g -O0" ^
  -DCMAKE_LIBRARY_OUTPUT_DIRECTORY=%~dp0\built\%ABI% ^
  -DCMAKE_RUNTIME_OUTPUT_DIRECTORY=%~dp0\built\%ABI% ^
  ..

@%covertiy_path% --dir=./tmp %CMAKE% --build . -- VERBOSE=1

@echo cd %%~dp0 >> REBUILD.cmd
@echo %CMAKE% --build . >> REBUILD.cmd
@echo @ping -n 5 127.0.0.1 ^> nul >> REBUILD.cmd
@cd ..