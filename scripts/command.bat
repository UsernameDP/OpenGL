@echo off

if "%~1" == "" GOTO PrintHelp
if "%~1" == "compile" GOTO CompileModes

pushd ..\
call vendor\bin\premake\premake5.exe %~1
popd

GOTO Done

:: -------------------------------------------------------------------------------
:PrintHelp

set "tab=   "

echo.
echo Enter 'build.bat action' where action is one of the following:
echo.
echo   compile           Will generate make file then compile using the make file.
echo   %tab%-Debug :          Compiles in debug mode
echo   %tab%%tab%-path.sln         Compiles the given .sln file  
echo   %tab%%tab%DEFAULT           Compiles all .sln files  
echo   %tab%-Release :        Compiles in release mode 
echo   %tab%%tab%-path.sln         Compiles the given .sln file   
echo   %tab%%tab%DEFAULT           Compiles all .sln files        
echo.
echo   clean             Remove all binaries and generated files
echo   codelite          Generate CodeLite project files
echo   gmake             Generate GNU makefiles for POSIX, MinGW, and Cygwin
echo   gmake2            Generate GNU makefiles for POSIX, MinGW, and Cygwin
echo   vs2005            Generate Visual Studio 2005 project files
echo   vs2008            Generate Visual Studio 2008 project files
echo   vs2010            Generate Visual Studio 2010 project files
echo   vs2012            Generate Visual Studio 2012 project files
echo   vs2013            Generate Visual Studio 2013 project files
echo   vs2015            Generate Visual Studio 2015 project files
echo   vs2017            Generate Visual Studio 2017 project files
echo   vs2019            Generate Visual Studio 2019 project files
echo   vs2022            Generate Visual Studio 2022 project files
echo   xcode4            Generate Apple Xcode 4 project files

GOTO Done

:: -------------------------------------------------------------------------------
:CompileModes

set "compileOptions=Debug Release"

for %%i in (%compileOptions%) do (
    if "%~2" == "%%i" (
        GOTO Compile
    )
)
GOTO PrintHelp

:: -------------------------------------------------------------------------------
:Compile

pushd ..\
call vendor\bin\premake\premake5.exe vs2022
popd

if not defined DevEnvDir (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
)

pushd ..\
if "%~3" == "" (
    for /r %%i in (*.sln) do (
    msbuild /t:Build /p:Configuration=%~2 /p:Platform=x64 %%i -m
)
) else if exist "%~3" (
    set "extension=%~x3"
    if "%extension%" == ".sln" (
        msbuild /t:Build /p:Configuration=%~2 /p:Platform=x64 %~3 -m
    )
) else (
    popd
    GOTO PrintHelp
)
popd

GOTO Done

:: -------------------------------------------------------------------------------
:Done