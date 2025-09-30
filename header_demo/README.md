# 头文件示例

这是一个简单的 `.h` 头文件使用示例。

## 文件说明

- `utils.h` - 头文件（函数声明）
- `utils.c` - 实现文件（函数定义）
- `test.c` - 测试文件（使用函数）

## 编译运行

```bash
# 方法1：一次性编译所有.c文件
gcc test.c utils.c -o test.exe
./test.exe

# 方法2：分步编译（先编译成.o文件再链接）
gcc -c utils.c -o utils.o
gcc -c test.c -o test.o
gcc utils.o test.o -o test.exe
./test.exe
```

## 重点

1. **头文件只写声明**，不写实现
2. **编译时需要包含所有.c文件**
3. **#ifndef 防止重复包含**
