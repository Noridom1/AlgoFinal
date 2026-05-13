@echo off
setlocal

if "%~1"=="" (
    echo Usage: %~nx0 path\to\file.cpp [output.exe]
    exit /b 1
)

set "SRC=%~1"

if not exist "%SRC%" (
    echo Source file not found: %SRC%
    exit /b 1
)

if "%~2"=="" (
    for %%F in ("%SRC%") do set "OUT=%%~dpnF.exe"
) else (
    set "OUT=%~2"
)

g++ -std=c++17 -O2 -Wall -Wextra -o "%OUT%" "%SRC%"

if errorlevel 1 (
    echo Build failed.
    exit /b %errorlevel%
)

echo Built "%OUT%"
echo Running "%OUT%"
"%OUT%"