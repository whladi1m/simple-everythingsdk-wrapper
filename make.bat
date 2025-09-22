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

REM Compile all .cpp files inside src folder
g++ -DUNICODE -D_UNICODE -D_WIN32_WINNT=0x0600 src\*.cpp -I"%EVERYTHING_INCLUDE%" -L"%EVERYTHING_LIB%" -lEverything64 -o search_tool.exe

if errorlevel 1 (
    echo [ERROR] Build failed!
    exit /b 1
)

echo [INFO] Build successful! Output: search_tool.exe
exit /b 0
