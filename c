#!/bin/bash
# C语言学习项目编译脚本 (跨平台版本)
# 支持: Mac, Linux, Windows(Git Bash/WSL)

# 编译输出目录
BUILD_DIR="build"

# 检测操作系统，设置可执行文件后缀
detect_os() {
    case "$OSTYPE" in
        msys*|cygwin*|win32*)
            EXEC_EXT=".exe"
            ;;
        *)
            EXEC_EXT=""
            ;;
    esac
}

# 确保编译目录存在
ensure_build_dir() {
    if [[ ! -d "$BUILD_DIR" ]]; then
        mkdir -p "$BUILD_DIR"
        echo "创建编译目录: $BUILD_DIR/"
    fi
}

print_help() {
    echo "C语言学习项目编译工具 (跨平台)"
    echo "支持: Mac, Linux, Windows(Git Bash/WSL)"
    echo ""
    echo "可用命令："
    echo "  ./c             - 编译所有C文件"
    echo "  ./c clean       - 清理可执行文件"
    echo "  ./c <程序名>     - 编译并运行指定程序"
    echo "  ./c help        - 显示此帮助信息"
    echo ""
    echo "编译输出目录: $BUILD_DIR/"
    echo ""
    echo "🎯 Windows用户建议:"
    echo "  • 使用 Git Bash 运行此脚本"
    echo "  • 或者使用 WSL (Windows Subsystem for Linux)"
    echo "  • 避免使用 CMD，功能受限"
    echo ""
    echo "可用的C文件:"
    find . -name "*.c" -type f 2>/dev/null | while read file; do
        name=$(basename "${file%.c}")
        echo "  ./c $name       - 编译并运行 $file"
    done
    echo ""
    echo "手动编译示例："
    local ext="exe"
    [[ "$OSTYPE" != "msys" && "$OSTYPE" != "cygwin" ]] && ext="out"
    echo "  gcc -Wall -Wextra -std=c99 -g test.c -o $BUILD_DIR/test.$ext"
}

compile_all() {
    ensure_build_dir
    detect_os
    echo "编译所有C文件到 $BUILD_DIR/..."
    
    find . -name "*.c" -type f 2>/dev/null | while read file; do
        echo "编译 $file..."
        name=$(basename "${file%.c}")
        if gcc -Wall -Wextra -std=c99 -g "$file" -o "$BUILD_DIR/${name}${EXEC_EXT}"; then
            echo "$file 编译成功 -> $BUILD_DIR/${name}${EXEC_EXT}"
        else
            echo "$file 编译失败！"
        fi
    done
}

clean_files() {
    echo "清理编译文件..."
    if [[ -d "$BUILD_DIR" ]]; then
        rm -rf "$BUILD_DIR"
        echo "已删除 $BUILD_DIR/ 目录"
    else
        echo "$BUILD_DIR/ 目录不存在"
    fi
    # 同时清理根目录遗留的exe文件
    rm -f *.exe
    echo "清理完成！"
}

compile_and_run() {
    local input="$1"
    local source=""
    local program=""
    
    ensure_build_dir
    detect_os
    
    # 判断输入是路径还是程序名
    if [[ "$input" == *"/"* ]] || [[ "$input" == *"\\"* ]]; then
        # 输入包含路径分隔符，认为是路径
        if [[ "$input" == *".c" ]]; then
            # 已有.c扩展名
            source="$input"
        else
            # 没有.c扩展名，自动添加
            source="${input}.c"
        fi
        program=$(basename "${source%.c}")
        
        # 检查文件是否存在
        if [[ ! -f "$source" ]]; then
            echo "错误: 找不到文件 $source"
            return 1
        fi
    else
        # 输入是程序名，自动搜索
        program="$input"
        source=$(find . -name "${program}.c" -type f 2>/dev/null | head -1)
        
        if [[ -z "$source" ]]; then
            echo "错误: 找不到 ${program}.c 文件"
            echo "可用的C文件:"
            find . -name "*.c" -type f 2>/dev/null | while read file; do
                name=$(basename "${file%.c}")
                echo "  ./c $name           # 程序名"
                echo "  ./c $file           # 路径"
            done
            return 1
        fi
    fi
    
    local executable="$BUILD_DIR/${program}${EXEC_EXT}"
    echo "源文件: $source"
    
    # 检查是否需要重新编译
    local need_compile=false
    
    if [[ ! -f "$executable" ]]; then
        echo "编译文件不存在，正在编译..."
        need_compile=true
    elif [[ "$source" -nt "$executable" ]]; then
        echo "源文件已修改，重新编译..."
        need_compile=true
    else
        echo "编译文件是最新的，直接运行..."
    fi
    
    # 编译（如果需要）
    if [[ "$need_compile" == true ]]; then
        if gcc -Wall -Wextra -std=c99 -g "$source" -o "$executable"; then
            echo "编译成功: $source -> $executable"
        else
            echo "编译失败！"
            return 1
        fi
    fi
    
    # 运行程序
    echo "运行程序..."
    ./"$executable"
}

# 主逻辑
case "$1" in
    "clean")
        clean_files
        ;;
    "help"|"-h"|"--help")
        print_help
        ;;
    "")
        compile_all
        ;;
    *)
        compile_and_run "$1"
        ;;
esac
