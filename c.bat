@echo off
REM C语言学习项目编译脚本 (Windows批处理版本)
echo C语言学习项目编译工具

if "%1"=="clean" goto :clean
if "%1"=="test" goto :test
if "%1"=="test2" goto :test2
if "%1"=="help" goto :help
if "%1"=="" goto :all

:all
echo 编译所有C文件...
for %%f in (*.c) do (
    echo 编译 %%f...
    gcc -Wall -Wextra -std=c99 -g "%%f" -o "%%~nf.exe"
    if errorlevel 1 (
        echo 编译 %%f 失败！
    ) else (
        echo %%f 编译成功！
    )
)
goto :end

:clean
echo 清理可执行文件...
del /Q *.exe 2>nul
echo 清理完成！
goto :end

:test
if exist test.exe (
    echo 运行 test.exe...
    test.exe
) else (
    echo test.exe 不存在，正在编译...
    gcc -Wall -Wextra -std=c99 -g test.c -o test.exe
    if errorlevel 1 (
        echo 编译失败！
    ) else (
        echo 编译成功，运行程序...
        test.exe
    )
)
goto :end

:test2
if exist test2.exe (
    echo 运行 test2.exe...
    test2.exe
) else (
    echo test2.exe 不存在，正在编译...
    gcc -Wall -Wextra -std=c99 -g test2.c -o test2.exe
    if errorlevel 1 (
        echo 编译失败！
    ) else (
        echo 编译成功，运行程序...
        test2.exe
    )
)
goto :end

:help
echo 可用命令：
echo   c.bat        - 编译所有C文件
echo   c.bat clean  - 清理可执行文件
echo   c.bat test   - 编译并运行test程序
echo   c.bat test2  - 编译并运行test2程序
echo   c.bat help   - 显示此帮助信息
echo.
echo 手动编译示例：
echo   gcc -Wall -Wextra -std=c99 -g test.c -o test.exe
goto :end

:end
