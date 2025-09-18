#!/bin/bash
# C语言学习项目编译脚本 (跨平台Shell版本)

print_help() {
    echo "C语言学习项目编译工具"
    echo "可用命令："
    echo "  ./c             - 编译所有C文件"
    echo "  ./c clean       - 清理可执行文件"
    echo "  ./c <程序名>     - 编译并运行指定程序"
    echo "  ./c help        - 显示此帮助信息"
    echo ""
    echo "当前目录的C文件:"
    for file in *.c; do
        if [[ -f "$file" ]]; then
            name="${file%.c}"
            echo "  ./c $name       - 编译并运行 $file"
        fi
    done
    echo ""
    echo "手动编译示例："
    echo "  gcc -Wall -Wextra -std=c99 -g test.c -o test.exe"
}

compile_all() {
    echo "编译所有C文件..."
    for file in *.c; do
        if [[ -f "$file" ]]; then
            echo "编译 $file..."
            name="${file%.c}"
            if gcc -Wall -Wextra -std=c99 -g "$file" -o "${name}.exe"; then
                echo "$file 编译成功！"
            else
                echo "$file 编译失败！"
            fi
        fi
    done
}

clean_files() {
    echo "清理可执行文件..."
    rm -f *.exe
    echo "清理完成！"
}

compile_and_run() {
    local program="$1"
    local source="${program}.c"
    local executable="${program}.exe"
    
    # 检查源文件是否存在
    if [[ ! -f "$source" ]]; then
        echo "错误: $source 文件不存在"
        return 1
    fi
    
    # 检查是否需要重新编译
    local need_compile=false
    
    if [[ ! -f "$executable" ]]; then
        echo "$executable 不存在，正在编译..."
        need_compile=true
    elif [[ "$source" -nt "$executable" ]]; then
        echo "$source 已修改，重新编译..."
        need_compile=true
    else
        echo "$executable 是最新的，直接运行..."
    fi
    
    # 编译（如果需要）
    if [[ "$need_compile" == true ]]; then
        if gcc -Wall -Wextra -std=c99 -g "$source" -o "$executable"; then
            echo "编译成功，运行程序..."
        else
            echo "编译失败！"
            return 1
        fi
    fi
    
    # 运行程序
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
        # 检查是否存在对应的.c文件
        if [[ -f "${1}.c" ]]; then
            compile_and_run "$1"
        else
            echo "错误: 找不到 ${1}.c 文件"
            echo "可用的C文件:"
            for file in *.c; do
                if [[ -f "$file" ]]; then
                    name="${file%.c}"
                    echo "  ./c $name"
                fi
            done
            echo ""
            echo "使用 './c help' 查看帮助"
            exit 1
        fi
        ;;
esac
