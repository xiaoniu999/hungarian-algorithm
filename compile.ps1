# Hungarian Algorithm Compilation Script for PowerShell
Write-Host "=== Hungarian Algorithm Compilation Script ===" -ForegroundColor Cyan
Write-Host

# Check if build directory exists
if (!(Test-Path "build")) {
    New-Item -ItemType Directory -Path "build" -Force | Out-Null
}

# Check for g++ compiler
try {
    $null = Get-Command g++ -ErrorAction Stop
    Write-Host "✓ Found g++ compiler" -ForegroundColor Green
} catch {
    Write-Host "✗ g++ compiler not found. Please install MinGW-w64 or Visual Studio." -ForegroundColor Red
    Write-Host "Download from: https://www.mingw-w64.org/" -ForegroundColor Yellow
    Read-Host "Press Enter to exit"
    exit 1
}

Write-Host "Compiling Hungarian Algorithm library..." -ForegroundColor Yellow
$result = Start-Process -FilePath "g++" -ArgumentList @("-std=c++17", "-c", "src/hungarian.cpp", "-Iinclude", "-o", "build/hungarian.o") -Wait -PassThru -NoNewWindow
if ($result.ExitCode -ne 0) {
    Write-Host "✗ Failed to compile hungarian.cpp" -ForegroundColor Red
    Read-Host "Press Enter to exit"
    exit 1
}
Write-Host "✓ Library compiled successfully" -ForegroundColor Green

Write-Host "Compiling example program..." -ForegroundColor Yellow
$result = Start-Process -FilePath "g++" -ArgumentList @("-std=c++17", "examples/main.cpp", "build/hungarian.o", "-Iinclude", "-o", "build/hungarian_example.exe") -Wait -PassThru -NoNewWindow
if ($result.ExitCode -ne 0) {
    Write-Host "✗ Failed to compile example program" -ForegroundColor Red
    Read-Host "Press Enter to exit"
    exit 1
}
Write-Host "✓ Example program compiled successfully" -ForegroundColor Green

Write-Host "Compiling test program..." -ForegroundColor Yellow
$result = Start-Process -FilePath "g++" -ArgumentList @("-std=c++17", "tests/test_hungarian.cpp", "build/hungarian.o", "-Iinclude", "-o", "build/hungarian_test.exe") -Wait -PassThru -NoNewWindow
if ($result.ExitCode -ne 0) {
    Write-Host "✗ Failed to compile test program" -ForegroundColor Red
    Read-Host "Press Enter to exit"
    exit 1
}
Write-Host "✓ Test program compiled successfully" -ForegroundColor Green

Write-Host
Write-Host "=== Compilation completed successfully! ===" -ForegroundColor Green
Write-Host
Write-Host "Available executables:" -ForegroundColor Cyan
Write-Host "- hungarian_example.exe: Demo program" -ForegroundColor White
Write-Host "- hungarian_test.exe: Test suite" -ForegroundColor White
Write-Host
Write-Host "To run the demo: " -NoNewline -ForegroundColor Cyan
Write-Host ".\build\hungarian_example.exe" -ForegroundColor Yellow
Write-Host "To run tests: " -NoNewline -ForegroundColor Cyan
Write-Host ".\build\hungarian_test.exe" -ForegroundColor Yellow
Write-Host

Read-Host "Press Enter to continue"
