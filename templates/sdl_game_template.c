// SDL2 游戏模板 - 适合小白
// 使用方法：复制这个文件，修改标注了【需修改】的部分即可

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ========== 【需修改】游戏配置 ==========
#define CELL_SIZE 20          // 每个格子大小
#define WIDTH 30              // 游戏区域宽度
#define HEIGHT 25             // 游戏区域高度
#define INFO_HEIGHT 40        // 顶部信息栏高度
#define WINDOW_WIDTH (WIDTH * CELL_SIZE)
#define WINDOW_HEIGHT (HEIGHT * CELL_SIZE + INFO_HEIGHT)
#define SPEED 150             // 游戏速度（毫秒，越小越快）

// ========== 【需修改】游戏数据 ==========
// 这里定义你的游戏需要的全局变量
// 示例：
int score = 0;
int running = 1;
int paused = 0;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

// ========== 【保持不变】SDL初始化 ==========
int init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL初始化失败: %s\n", SDL_GetError());
        return 0;
    }
    
    window = SDL_CreateWindow("🎮 我的游戏",  // 【可修改】窗口标题
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("窗口创建失败: %s\n", SDL_GetError());
        return 0;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("渲染器创建失败: %s\n", SDL_GetError());
        return 0;
    }
    
    return 1;
}

// ========== 【工具函数】绘制矩形 ==========
void draw_rect(int x, int y, int w, int h, int r, int g, int b) {
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

// ========== 【需修改】初始化游戏 ==========
void init_game() {
    // 重置游戏状态
    score = 0;
    paused = 0;
    
    // 初始化你的游戏数据
    // 例如：重置玩家位置、敌人、道具等
}

// ========== 【需修改】渲染游戏画面 ==========
void draw() {
    // 1. 清空背景
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
    
    // 2. 绘制信息栏背景
    draw_rect(0, 0, WINDOW_WIDTH, INFO_HEIGHT, 45, 45, 45);
    
    // 3. 绘制游戏区域背景（网格）
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int px = x * CELL_SIZE;
            int py = y * CELL_SIZE + INFO_HEIGHT;
            draw_rect(px, py, CELL_SIZE-1, CELL_SIZE-1, 50, 50, 50);
        }
    }
    
    // 4. 【修改这里】绘制你的游戏元素
    // 例如：
    // - 玩家
    // - 敌人
    // - 道具
    // - 得分显示等
    
    // 示例：绘制一个红色方块
    // draw_rect(100, 100, 40, 40, 255, 0, 0);
    
    // 5. 显示到屏幕
    SDL_RenderPresent(renderer);
}

// ========== 【需修改】处理输入 ==========
void handle_input() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = 0;
        }
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                // 【修改这里】添加你的按键处理
                case SDLK_UP:
                case SDLK_w:
                    // 上键逻辑
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    // 下键逻辑
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    // 左键逻辑
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    // 右键逻辑
                    break;
                case SDLK_SPACE:
                    paused = !paused;  // 暂停/继续
                    break;
                case SDLK_r:
                    init_game();  // 重新开始
                    break;
                case SDLK_q:
                case SDLK_ESCAPE:
                    running = 0;  // 退出
                    break;
            }
        }
    }
}

// ========== 【需修改】更新游戏逻辑 ==========
void update() {
    if (paused) return;
    
    // 【修改这里】写你的游戏逻辑
    // 例如：
    // - 移动玩家
    // - 移动敌人
    // - 碰撞检测
    // - 生成道具
    // - 更新分数等
}

// ========== 【保持不变】清理资源 ==========
void cleanup() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

// ========== 【保持不变】主程序 ==========
int main(int argc, char *argv[]) {
    (void)argc; (void)argv;
    
    srand(time(NULL));
    
    if (!init_sdl()) {
        cleanup();
        return 1;
    }
    
    init_game();
    
    Uint32 last_update = SDL_GetTicks();
    
    // 主循环
    while (running) {
        handle_input();
        
        Uint32 current = SDL_GetTicks();
        if (current - last_update >= SPEED) {
            update();
            last_update = current;
        }
        
        draw();
        SDL_Delay(10);
    }
    
    cleanup();
    return 0;
}

