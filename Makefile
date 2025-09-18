# C语言学习项目 Makefile
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# 所有的C源文件
SOURCES = $(wildcard *.c)
# 对应的可执行文件
TARGETS = $(SOURCES:.c=.exe)

# 默认目标：编译所有程序
all: $(TARGETS)

# 通用规则：从.c文件生成.exe文件
%.exe: %.c
	$(CC) $(CFLAGS) -o $@ $<

# 清理生成的文件
clean:
	rm -f *.exe *.o

# 运行测试程序
run-test: test.exe
	./test.exe

run-test2: test2.exe
	./test2.exe

# 显示帮助信息
help:
	@echo "可用的命令："
	@echo "  make          - 编译所有C文件"
	@echo "  make clean    - 清理可执行文件"
	@echo "  make run-test - 运行test程序"
	@echo "  make run-test2 - 运行test2程序"
	@echo "  make help     - 显示此帮助信息"

.PHONY: all clean run-test run-test2 help
