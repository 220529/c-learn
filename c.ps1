# C语言学习项目编译脚本 (PowerShell跨平台版本)
# 支持: Windows, Mac (需安装PowerShell Core), Linux

# 没有参数声明，直接使用$args

# 编译输出目录
$BuildDir = "build"

# 检测操作系统
function Get-ExecutableExtension {
    if ($IsWindows -or $env:OS -eq "Windows_NT") {
        return ".exe"
    }
    return ""
}

# 确保编译目录存在
function Ensure-BuildDir {
    if (-not (Test-Path $BuildDir)) {
        New-Item -ItemType Directory -Path $BuildDir -Force | Out-Null
        Write-Host "创建编译目录: $BuildDir/"
    }
}

# 显示帮助信息
function Show-Help {
    Write-Host "C语言学习项目编译工具 (跨平台PowerShell版本)"
    Write-Host "支持: Windows, Mac(PowerShell Core), Linux(PowerShell Core)"
    Write-Host ""
    Write-Host "可用命令:"
    Write-Host "  .\c.ps1                    - 编译所有C文件"
    Write-Host "  .\c.ps1 clean              - 清理可执行文件"
    Write-Host "  .\c.ps1 <程序名>            - 编译并运行指定程序(自动搜索)"
    Write-Host "  .\c.ps1 <相对路径>          - 编译并运行指定路径的文件"
    Write-Host "  .\c.ps1 help               - 显示此帮助信息"
    Write-Host ""
    Write-Host "编译输出目录: $BuildDir/"
    Write-Host ""
    
    if ($IsWindows -or $env:OS -eq "Windows_NT") {
        Write-Host "🎯 Windows用户:"
        Write-Host "  • 直接在PowerShell中运行"
        Write-Host "  • 或者使用 Git Bash 运行 Shell 版本的 'c' 脚本"
    } else {
        Write-Host "🎯 Mac/Linux用户:"
        Write-Host "  • 需要安装 PowerShell Core"
        Write-Host "  • 或者直接使用 Shell 版本的 './c' 脚本"
    }
    Write-Host ""
    
    Write-Host "使用示例:"
    Write-Host "  .\c.ps1 hello                                    # 程序名(自动搜索)"
    Write-Host "  .\c.ps1 .\exercises\basics\hello.c               # 相对路径"
    Write-Host "  .\c.ps1 exercises\data_structures\split_linked.c # 相对路径"
    Write-Host ""
    Write-Host "可用的C文件:"
    Get-ChildItem -Recurse -Filter "*.c" | ForEach-Object {
        $name = $_.BaseName
        $relativePath = $_.FullName.Replace((Get-Location).Path + "\", "")
        Write-Host "  程序名: $name    路径: $relativePath"
    }
    Write-Host ""
    
    $ext = Get-ExecutableExtension
    Write-Host "手动编译示例:"
    Write-Host "  gcc -Wall -Wextra -std=c99 -g test.c -o $BuildDir/test$ext"
}

# 编译所有C文件
function Compile-All {
    Ensure-BuildDir
    $ext = Get-ExecutableExtension
    Write-Host "编译所有C文件到 $BuildDir/..."
    
    Get-ChildItem -Recurse -Filter "*.c" | ForEach-Object {
        Write-Host "编译 $($_.FullName)..."
        $name = $_.BaseName
        
        # 检查是否需要特殊的链接库
        $extraFlags = ""
        if ($name -eq "sound_app") {
            $extraFlags = "-mwindows -lole32 -luuid"
        } elseif ($name -eq "http_server") {
            $extraFlags = "-lws2_32"
        } elseif ($name -eq "snake_game") {
            $extraFlags = "-mwindows -lgdi32"
        }
        
        $result = & gcc -Wall -Wextra -std=c99 -g $_.FullName -o "$BuildDir/$name$ext" $extraFlags.Split() 2>&1
        
        if ($LASTEXITCODE -eq 0) {
            Write-Host "$($_.FullName) 编译成功 -> $BuildDir/$name$ext" -ForegroundColor Green
        } else {
            Write-Host "$($_.FullName) 编译失败!" -ForegroundColor Red
            Write-Host $result -ForegroundColor Red
        }
    }
}

# 清理编译文件
function Clean-Files {
    Write-Host "清理编译文件..."
    if (Test-Path $BuildDir) {
        Remove-Item $BuildDir -Recurse -Force
        Write-Host "已删除 $BuildDir/ 目录" -ForegroundColor Green
    } else {
        Write-Host "$BuildDir/ 目录不存在"
    }
    
    # 同时清理根目录遗留的exe文件
    Get-ChildItem -Filter "*.exe" | Remove-Item -Force
    Write-Host "清理完成!" -ForegroundColor Green
}

# 编译并运行指定程序
function Compile-And-Run {
    $Input = $args[0]
    
    Ensure-BuildDir
    $ext = Get-ExecutableExtension
    
    # 判断输入是路径还是程序名
    if ($Input.Contains("\") -or $Input.Contains("/")) {
        # 输入包含路径分隔符，认为是路径
        if ($Input.EndsWith(".c")) {
            # 已有.c扩展名
            $sourcePath = $Input
        } else {
            # 没有.c扩展名，自动添加
            $sourcePath = "$Input.c"
        }
        
        $sourceFile = Get-Item $sourcePath -ErrorAction SilentlyContinue
        if (-not $sourceFile) {
            Write-Host "错误: 找不到文件 $sourcePath" -ForegroundColor Red
            return
        }
        $programName = $sourceFile.BaseName
    } else {
        # 输入是程序名，自动搜索
        $programName = $Input
        $sourceFile = Get-ChildItem -Recurse -Filter "$programName.c" | Select-Object -First 1
        
        if (-not $sourceFile) {
            Write-Host "错误: 找不到 $programName.c 文件" -ForegroundColor Red
            Write-Host "可用的C文件:"
            Get-ChildItem -Recurse -Filter "*.c" | ForEach-Object {
                Write-Host "  .\c.ps1 $($_.BaseName)    # 程序名方式"
                Write-Host "  .\c.ps1 $($_.FullName)    # 路径方式"
            }
            return
        }
    }
    
    $executable = "$BuildDir/$programName$ext"
    Write-Host "源文件: $($sourceFile.FullName)"
    
    # 检查是否需要重新编译
    $needCompile = $false
    
    if (-not (Test-Path $executable)) {
        Write-Host "编译文件不存在，正在编译..."
        $needCompile = $true
    } elseif ($sourceFile.LastWriteTime -gt (Get-Item $executable).LastWriteTime) {
        Write-Host "源文件已修改，重新编译..."
        $needCompile = $true
    } else {
        Write-Host "编译文件是最新的，直接运行..."
    }
    
    # 编译（如果需要）
    if ($needCompile) {
        # 检查是否需要特殊的链接库
        $extraFlags = ""
        if ($programName -eq "sound_app") {
            # sound_app 需要 Windows COM 库
            $extraFlags = "-mwindows -lole32 -luuid"
        } elseif ($programName -eq "http_server") {
            # http_server 需要 Winsock 库
            $extraFlags = "-lws2_32"
        } elseif ($programName -eq "snake_game") {
            # snake_game 需要 GDI 库
            $extraFlags = "-mwindows -lgdi32"
        }
        
        $result = & gcc -Wall -Wextra -std=c99 -g $sourceFile.FullName -o $executable $extraFlags.Split() 2>&1
        
        if ($LASTEXITCODE -eq 0) {
            Write-Host "编译成功: $($sourceFile.FullName) -> $executable" -ForegroundColor Green
        } else {
            Write-Host "编译失败!" -ForegroundColor Red
            Write-Host $result -ForegroundColor Red
            return
        }
    }
    
    # 运行程序
    Write-Host "运行程序..." -ForegroundColor Yellow
    & $executable
}

# 主逻辑
if ($args.Count -eq 0) {
    Compile-All
} elseif ($args[0].ToLower() -eq "clean") {
    Clean-Files
} elseif ($args[0].ToLower() -eq "help") {
    Show-Help
} else {
    Compile-And-Run $args[0]
}
