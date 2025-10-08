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
	rm -rf build/*
	rm -rf dist/

# 贪吃蛇游戏
snake: exercises/basics/snake.c
	mkdir -p build
	$(CC) $(CFLAGS) -o build/snake exercises/basics/snake.c $$(sdl2-config --cflags --libs)

run: snake
	./build/snake

# 打包为 Mac App
dmg:
	chmod +x scripts/build_app.sh
	./scripts/build_app.sh

# 显示帮助信息
help:
	@echo "🐍 贪吃蛇游戏"
	@echo ""
	@echo "运行游戏："
	@echo "  make run       - 编译并运行"
	@echo "  ./c snake      - 编译并运行"
	@echo ""
	@echo "打包："
	@echo "  make dmg       - 打包成Mac App"
	@echo ""
	@echo "其他："
	@echo "  make clean     - 清理文件"
	@echo "  make help      - 显示帮助"

.PHONY: all clean snake run dmg help
