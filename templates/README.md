# SDL2 游戏模板使用说明

## 🎮 快速开始

### 1. 复制模板

```bash
cp templates/sdl_game_template.c exercises/basics/my_game.c
```

### 2. 修改标注了【需修改】的部分

模板中标注了 4 个主要修改点：

#### ① 游戏配置

```c
#define CELL_SIZE 20    // 格子大小
#define WIDTH 30        // 区域宽度
#define HEIGHT 25       // 区域高度
#define SPEED 150       // 游戏速度
```

#### ② 游戏数据

```c
// 定义你的游戏变量
int player_x, player_y;
int enemy_x, enemy_y;
// ...
```

#### ③ 渲染画面

```c
void draw() {
    // 在这里绘制你的游戏元素
    draw_rect(x, y, w, h, r, g, b);
}
```

#### ④ 游戏逻辑

```c
void update() {
    // 在这里写游戏逻辑
    // 移动、碰撞、计分等
}
```

### 3. 编译运行

修改 `Makefile`：

```makefile
my_game: exercises/basics/my_game.c
	gcc -o build/my_game exercises/basics/my_game.c $(sdl2-config --cflags --libs)

run-my_game: my_game
	./build/my_game
```

然后：

```bash
make run-my_game
```

## 📋 不需要修改的部分

- `init_sdl()` - SDL 初始化
- `cleanup()` - 资源清理
- `main()` - 主循环
- `draw_rect()` - 绘制工具函数

## 🎯 示例：从贪吃蛇学习

查看 `exercises/basics/snake.c` 看完整示例

## 💡 提示

1. **颜色代码**: RGB(红, 绿, 蓝)，范围 0-255

   - 红色: `(255, 0, 0)`
   - 绿色: `(0, 255, 0)`
   - 蓝色: `(0, 0, 255)`

2. **坐标系**: 左上角是 (0, 0)，向右向下增加

3. **按键**: 已经设置好 WASD 和方向键，直接用即可
