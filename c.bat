@echo off
REM C Language Learning Project Build Script (Windows Batch Version)
echo C Language Learning Project Build Tool

if "%1"=="clean" goto :clean
if "%1"=="test" goto :test
if "%1"=="test2" goto :test2
if "%1"=="help" goto :help
if "%1"=="" goto :all

:all
echo Compiling all C files...
for %%f in (*.c) do (
    echo Compiling %%f...
    gcc -Wall -Wextra -std=c99 -g "%%f" -o "%%~nf.exe"
    if errorlevel 1 (
        echo Failed to compile %%f!
    ) else (
        echo %%f compiled successfully!
    )
)
goto :end

:clean
echo Cleaning executable files...
del /Q *.exe 2>nul
echo Cleanup complete!
goto :end

:test
if exist test.exe (
    echo Running test.exe...
    test.exe
) else (
    echo test.exe does not exist, compiling...
    gcc -Wall -Wextra -std=c99 -g test.c -o test.exe
    if errorlevel 1 (
        echo Compilation failed!
    ) else (
        echo Compilation successful, running program...
        test.exe
    )
)
goto :end

:test2
if exist test2.exe (
    echo Running test2.exe...
    test2.exe
) else (
    echo test2.exe does not exist, compiling...
    gcc -Wall -Wextra -std=c99 -g test2.c -o test2.exe
    if errorlevel 1 (
        echo Compilation failed!
    ) else (
        echo Compilation successful, running program...
        test2.exe
    )
)
goto :end

:help
echo Available commands:
echo   .\c.bat        - Compile all C files
echo   .\c.bat clean  - Clean executable files
echo   .\c.bat test   - Compile and run test program
echo   .\c.bat test2  - Compile and run test2 program
echo   .\c.bat help   - Show this help message
echo.
echo Manual compilation example:
echo   gcc -Wall -Wextra -std=c99 -g test.c -o test.exe
echo.
echo Note: You need to install GCC compiler first!
echo   Download from: https://sourceforge.net/projects/mingw-w64/
goto :end

:end
