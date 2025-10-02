// 贪吃蛇游戏 - SDL2图形窗口版
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CELL_SIZE 20
#define WIDTH 30
#define HEIGHT 25
#define WINDOW_WIDTH (WIDTH * CELL_SIZE)
#define WINDOW_HEIGHT (HEIGHT * CELL_SIZE)
#define SPEED 300           // 速度（毫秒），数值越大越慢

typedef struct { int x, y; } Point;

Point snake[900];
int length = 3, score = 0, dir = 0; // 0=右 1=下 2=左 3=上
Point food;
int running = 1, paused = 0;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;

void gen_food() {
    do {
        food.x = rand() % WIDTH;
        food.y = rand() % HEIGHT;
        int ok = 1;
        for (int i = 0; i < length; i++)
            if (snake[i].x == food.x && snake[i].y == food.y) { ok = 0; break; }
        if (ok) break;
    } while (1);
}

void init_game() {
    length = 3; dir = 0; score = 0; paused = 0;
    for (int i = 0; i < 3; i++) {
        snake[i].x = WIDTH/2 - i;
        snake[i].y = HEIGHT/2;
    }
    gen_food();
}

int init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL初始化失败: %s\n", SDL_GetError());
        return 0;
    }
    
    window = SDL_CreateWindow("🐍 贪吃蛇游戏", 
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

void draw_rect(int x, int y, int w, int h, int r, int g, int b) {
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(renderer, r, g, b, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void draw() {
    // 更新窗口标题显示分数
    char title[100];
    snprintf(title, sizeof(title), "🐍 贪吃蛇 | 分数: %d | 长度: %d", score, length);
    SDL_SetWindowTitle(window, title);
    
    // 背景
    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
    SDL_RenderClear(renderer);
    
    // 游戏区域网格
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int px = x * CELL_SIZE;
            int py = y * CELL_SIZE;
            draw_rect(px, py, CELL_SIZE-1, CELL_SIZE-1, 50, 50, 50);
        }
    }
    
    // 食物（红色）
    int fx = food.x * CELL_SIZE;
    int fy = food.y * CELL_SIZE;
    draw_rect(fx+2, fy+2, CELL_SIZE-4, CELL_SIZE-4, 255, 50, 50);
    
    // 蛇
    for (int i = 0; i < length; i++) {
        int sx = snake[i].x * CELL_SIZE;
        int sy = snake[i].y * CELL_SIZE;
        
        if (i == 0) {
            // 蛇头（亮绿色）
            draw_rect(sx+2, sy+2, CELL_SIZE-4, CELL_SIZE-4, 100, 255, 100);
        } else {
            // 蛇身（浅绿）
            draw_rect(sx+3, sy+3, CELL_SIZE-6, CELL_SIZE-6, 150, 255, 150);
        }
    }
    
    SDL_RenderPresent(renderer);
}

void handle_input() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            running = 0;
        }
        else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_w:
                    if (dir != 1) dir = 3;
                    break;
                case SDLK_DOWN:
                case SDLK_s:
                    if (dir != 3) dir = 1;
                    break;
                case SDLK_LEFT:
                case SDLK_a:
                    if (dir != 0) dir = 2;
                    break;
                case SDLK_RIGHT:
                case SDLK_d:
                    if (dir != 2) dir = 0;
                    break;
                case SDLK_SPACE:
                    paused = !paused;
                    break;
                case SDLK_r:
                    init_game();
                    break;
                case SDLK_q:
                case SDLK_ESCAPE:
                    running = 0;
                    break;
            }
        }
    }
}

void update() {
    if (paused) return;
    
    Point new_head = snake[0];
    if (dir == 0) new_head.x++;
    else if (dir == 1) new_head.y++;
    else if (dir == 2) new_head.x--;
    else new_head.y--;
    
    // 检查撞墙
    if (new_head.x < 0 || new_head.x >= WIDTH || 
        new_head.y < 0 || new_head.y >= HEIGHT) {
        init_game();
        return;
    }
    
    // 检查撞自己
    for (int i = 0; i < length; i++) {
        if (snake[i].x == new_head.x && snake[i].y == new_head.y) {
            init_game();
            return;
        }
    }
    
    // 检查是否吃到食物
    int ate = (new_head.x == food.x && new_head.y == food.y);
    
    // 移动蛇身
    if (!ate) {
        // 没吃到食物，正常移动（去掉尾巴）
        for (int i = length - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }
    } else {
        // 吃到食物，蛇身后移但保留尾巴（相当于增长）
        for (int i = length; i > 0; i--) {
            snake[i] = snake[i - 1];
        }
        length++;
        score += 10;
        gen_food();
    }
    
    snake[0] = new_head;
}

void cleanup() {
    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    (void)argc; (void)argv; // 避免未使用警告
    
    srand(time(NULL));
    
    if (!init_sdl()) {
        cleanup();
        return 1;
    }
    
    init_game();
    
    Uint32 last_update = SDL_GetTicks();
    
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

