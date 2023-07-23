@echo off

IF "%~1" == "" GOTO PrintHelp
IF "%~1" == "compile" GOTO Compile

pushd ..\
call vendor\bin\premake\premake5.exe %~1
popd

GOTO Done

@REM -------------------------------------------------------------------------------
:PrintHelp

echo.
echo Enter 'build.bat action' where action is one of the following:
echo.
echo   compile           Will generate make file then compile using the make file.
echo   -All :     Compiles all the solutions
echo   -name :    enter solution name to compile that specific solution          
echo .             
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

@REM -------------------------------------------------------------------------------
:Compile
@REM You first need to create the solutions to compile
pushd ..\
call vendor\bin\premake\premake5.exe vs2022
popd

if not defined DevEnvDir (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"
)

pushd ..\
IF "%~2" == "" GOTO All 
IF "%~2" == "OpenGL-Core.sln" GOTO OpenGL-Core
IF "%~2" == "OpenGL-Examples.sln" GOTO OpenGL-Core

    :All
    set "solutions=OpenGL-Core.sln OpenGL-Examples.sln"
    for %%i in (%solutions%) do (
        msbuild /t:Build /p:Configuration=Debug /p:Platform=x64 %%i
    )
    popd
    Goto Done

    :OpenGL-Core
    set "solutionFile=OpenGL-Core.sln"
    msbuild /t:Build /p:Configuration=Debug /p:Platform=x64 %solutionFile%
    popd
    Goto Done

    :OpenGL-Examples
    set "solutionFile=OpenGL-Examples.sln"
    msbuild /t:Build /p:Configuration=Debug /p:Platform=x64 %solutionFile%
    popd
    GOTO Done

@REM -------------------------------------------------------------------------------
:Done