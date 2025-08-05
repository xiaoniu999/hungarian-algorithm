@echo off
echo === Hungarian Algorithm Compilation Script ===
echo.

echo Compiling Hungarian Algorithm library...
g++ -std=c++17 -c src/hungarian.cpp -Iinclude -o build/hungarian.o
if %errorlevel% neq 0 (
    echo Error: Failed to compile hungarian.cpp
    pause
    exit /b 1
)

echo Compiling example program...
g++ -std=c++17 examples/main.cpp build/hungarian.o -Iinclude -o build/hungarian_example.exe
if %errorlevel% neq 0 (
    echo Error: Failed to compile example program
    pause
    exit /b 1
)

echo Compiling test program...
g++ -std=c++17 tests/test_hungarian.cpp build/hungarian.o -Iinclude -o build/hungarian_test.exe
if %errorlevel% neq 0 (
    echo Error: Failed to compile test program
    pause
    exit /b 1
)

echo.
echo === Compilation completed successfully! ===
echo.
echo Available executables:
echo - hungarian_example.exe: Demo program
echo - hungarian_test.exe: Test suite
echo.
echo To run the demo: build\hungarian_example.exe
echo To run tests: build\hungarian_test.exe
echo.
pause
