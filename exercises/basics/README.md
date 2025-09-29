# 基础语法练习

这个目录包含C语言核心概念的练习文件，简洁实用。

## 📝 练习文件列表

### 🚀 入门
- `hello.c` - Hello World程序

### 🔧 语法基础
- `basic_syntax.c` - 循环、条件判断、数组遍历
- `array_size.c` - 数组基础规则

### 🧠 核心概念  
- `pointer_demo.c` - 指针基础
- `struct_test.c` - 结构体使用
- `malloc_demo.c` - 动态内存管理
- `dynamic_array.c` - 动态数组实现

## 🔧 编译和运行

```bash
# 从项目根目录编译任意文件
gcc -Wall -Wextra -std=c99 -g exercises/basics/hello.c -o hello.exe

# 运行
./hello.exe

# 或使用项目脚本
./c hello        # Unix/Linux/Git Bash
c.bat hello      # Windows CMD
```

## 🎯 学习建议

**推荐学习顺序**：
1. `hello.c` → `basic_syntax.c`
2. `array_size.c` → `pointer_demo.c` 
3. `struct_test.c` → `malloc_demo.c`
4. `dynamic_array.c` (综合应用)
