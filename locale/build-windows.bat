@echo on
@rem Usage: build-windows {32|64} {msvc|mingw}
if %2 == msvc (
    if %1 == 64 (
       call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvars64.bat"
    ) else (
       call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Enterprise\VC\Auxiliary\Build\vcvars32.bat"
    )
    bash locale/build-windows %1 %2
) else (
    C:\msys64\usr\bin\env.exe MSYSTEM=MINGW64 /bin/bash -l %CD%/locale/build-windows %1 %2
)
