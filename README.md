# C语言学习项目

这是一个用于学习C语言的项目，包含各种练习和示例代码。

## 项目结构

```
c-learn/
├── README.md          # 项目说明文档
├── Makefile          # 编译管理文件（跨平台）
├── c                 # Shell编译脚本（跨平台）
├── c.bat             # 批处理编译脚本（Windows专用）
├── .gitignore        # Git忽略文件配置
├── test.c            # 基础测试程序
├── test2.c           # 基础测试程序2
└── exercises/        # 练习目录（建议创建）
    ├── basics/       # 基础语法练习
    ├── arrays/       # 数组练习
    ├── pointers/     # 指针练习
    ├── structures/   # 结构体练习
    └── algorithms/   # 算法练习
```

## 如何使用

### 编译和运行

#### 跨平台使用（推荐）

```bash
# 使用Shell脚本（Mac/Linux/Git Bash通用）
./c              # 编译所有程序
./c test         # 编译并运行test程序
./c test2        # 编译并运行test2程序
./c clean        # 清理编译文件
./c help         # 查看帮助

# 使用Makefile（需要安装make工具，跨平台）
make             # 编译所有程序
make run-test    # 编译并运行test程序
make clean       # 清理编译文件
make help        # 查看帮助
```

#### Windows专用

```batch
# 使用批处理脚本（仅Windows CMD）
c.bat            # 编译所有程序
c.bat test       # 编译并运行test程序
c.bat test2      # 编译并运行test2程序
c.bat clean      # 清理编译文件
c.bat help       # 查看帮助
```

### 手动编译（如果不使用Makefile）

```bash
# 编译单个文件
gcc -Wall -Wextra -std=c99 -g test.c -o test.exe

# 运行程序
./test.exe
```

## 学习计划

### 阶段1：基础语法
- [x] Hello World程序 (`test.c`, `test2.c`)
- [ ] 变量和数据类型
- [ ] 输入输出操作
- [ ] 运算符和表达式
- [ ] 条件语句(if/else/switch)
- [ ] 循环语句(for/while/do-while)

### 阶段2：函数和数组
- [ ] 函数定义和调用
- [ ] 参数传递
- [ ] 作用域和生命周期
- [ ] 一维数组
- [ ] 多维数组
- [ ] 字符串处理

### 阶段3：指针和内存管理
- [ ] 指针基础
- [ ] 指针与数组
- [ ] 指针与函数
- [ ] 动态内存分配
- [ ] 内存泄漏预防

### 阶段4：高级特性
- [ ] 结构体(struct)
- [ ] 联合体(union)
- [ ] 枚举(enum)
- [ ] 文件操作
- [ ] 预处理器指令

### 阶段5：数据结构与算法
- [x] 单链表递增判断 (`simple_list.c`)
- [ ] 链表反转
- [ ] 栈的实现和应用
- [ ] 队列的实现
- [ ] 简单排序算法

### 阶段6：实践项目
- [ ] 计算器程序
- [ ] 简单的文本编辑器
- [ ] 小型项目

## 编码规范

- 使用4个空格缩进
- 变量名使用小写字母和下划线
- 函数名使用小写字母和下划线
- 常量使用大写字母和下划线
- 每个函数前添加注释说明功能

## 学习资源

- [C语言程序设计现代方法](https://book.douban.com/subject/4279678/)
- [C Primer Plus](https://book.douban.com/subject/26792521/)
- [Learn C the Hard Way](https://learncodethehardway.org/c/)
- [C语言中文网](http://c.biancheng.net/c/)

## 练习记录

| 日期 | 练习内容 | 完成情况 | 备注 |
|------|----------|----------|------|
| 2025-09-18 | Hello World | ✅ | 完成基础程序 |
| 2025-09-18 | 单链表递增判断 | ✅ | 简单版算法练习 |

## 平台兼容性

| 平台 | 推荐工具 | 说明 |
|------|----------|------|
| **Mac** | `./c` 或 `make` | 优先使用Shell脚本，需要安装Xcode Command Line Tools |
| **Linux** | `./c` 或 `make` | 默认支持，确保安装gcc |
| **Windows (Git Bash)** | `./c` 或 `make` | 推荐使用，跨平台兼容 |
| **Windows (CMD)** | `c.bat` | 原生Windows批处理 |

## 常见问题

### 编译错误
- 确保安装了GCC编译器
- 检查语法错误
- 确保包含必要的头文件

### 运行时错误
- 检查数组越界
- 检查空指针访问
- 检查内存泄漏

### 平台特定问题
- **Mac**: 如果gcc命令不存在，运行 `xcode-select --install`
- **Windows**: 推荐使用Git Bash或安装MinGW-w64
- **Linux**: 运行 `sudo apt install build-essential`（Ubuntu/Debian）

---

**祝你学习愉快！记得定期更新学习进度。**
