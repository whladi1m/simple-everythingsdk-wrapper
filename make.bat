@echo off
REM === Configuration ===
REM Before running make.bat, set these:
REM   set EVERYTHING_INCLUDE=C:\path\to\EverythingSDK\include
REM   set EVERYTHING_LIB=C:\path\to\EverythingSDK\lib

if "%EVERYTHING_INCLUDE%"=="" (
    echo [ERROR] EVERYTHING_INCLUDE is not set. Use: set EVERYTHING_INCLUDE=C:\path\to\EverythingSDK\include
    exit /b 1
)

if "%EVERYTHING_LIB%"=="" (
    echo [ERROR] EVERYTHING_LIB is not set. Use: set EVERYTHING_LIB=C:\path\to\EverythingSDK\lib
    exit /b 1
)

echo [INFO] Building search_tool.exe from src\...

REM Collect all .cpp files in src folder into a variable
setlocal enabledelayedexpansion
set "SOURCES="
for %%f in (src\*.cpp) do (
    if defined SOURCES (
        set "SOURCES=!SOURCES! %%f"
    ) else (
        set "SOURCES=%%f"
    )
)

REM Check if any .cpp files were found
if not defined SOURCES (
    echo [ERROR] No .cpp files found in src\ folder!
    exit /b 1
)

REM Compile using all collected .cpp files
g++ -DUNICODE -D_UNICODE -D_WIN32_WINNT=0x0600 !SOURCES! -I"%EVERYTHING_INCLUDE%" -L"%EVERYTHING_LIB%" -lEverything64 -o search_tool.exe

if errorlevel 1 (
    echo [ERROR] Build failed!
    exit /b 1
)

echo [INFO] Build successful! Output: search_tool.exe
endlocal
exit /b 0