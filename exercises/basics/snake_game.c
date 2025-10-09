// 贪吃蛇游戏 - Windows GUI 版本
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 游戏配置
#define CELL_SIZE 20        // 每个格子的像素大小
#define GRID_WIDTH 30       // 游戏区域宽度（格子数）
#define GRID_HEIGHT 25      // 游戏区域高度（格子数）
#define TIMER_ID 1
#define GAME_SPEED 200      // 游戏速度（毫秒，数值越大越慢）

// 方向
typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

// 蛇身节点
typedef struct {
    int x, y;
} Point;

// 游戏状态
Point snake[GRID_WIDTH * GRID_HEIGHT];  // 蛇身数组
int snake_length = 3;                    // 蛇的长度
Direction direction = RIGHT;             // 当前方向
Direction next_direction = RIGHT;        // 下一步方向（避免反向）
Point food;                              // 食物位置
int score = 0;                           // 分数
BOOL game_over = FALSE;                  // 游戏结束标志
BOOL paused = FALSE;                     // 暂停标志

// 随机生成食物
void generate_food() {
    BOOL valid;
    do {
        valid = TRUE;
        food.x = rand() % GRID_WIDTH;
        food.y = rand() % GRID_HEIGHT;
        
        // 确保食物不在蛇身上
        for (int i = 0; i < snake_length; i++) {
            if (snake[i].x == food.x && snake[i].y == food.y) {
                valid = FALSE;
                break;
            }
        }
    } while (!valid);
}

// 初始化游戏
void init_game() {
    snake_length = 3;
    direction = RIGHT;
    next_direction = RIGHT;
    score = 0;
    game_over = FALSE;
    paused = FALSE;
    
    // 初始化蛇的位置（屏幕中间）
    snake[0].x = GRID_WIDTH / 2;
    snake[0].y = GRID_HEIGHT / 2;
    snake[1].x = snake[0].x - 1;
    snake[1].y = snake[0].y;
    snake[2].x = snake[1].x - 1;
    snake[2].y = snake[1].y;
    
    generate_food();
}

// 游戏逻辑更新
void update_game() {
    if (game_over || paused) return;
    
    // 更新方向（防止180度转向）
    if ((direction == UP && next_direction != DOWN) ||
        (direction == DOWN && next_direction != UP) ||
        (direction == LEFT && next_direction != RIGHT) ||
        (direction == RIGHT && next_direction != LEFT)) {
        direction = next_direction;
    }
    
    // 计算蛇头新位置
    Point new_head = snake[0];
    switch (direction) {
        case UP:    new_head.y--; break;
        case DOWN:  new_head.y++; break;
        case LEFT:  new_head.x--; break;
        case RIGHT: new_head.x++; break;
    }
    
    // 检查撞墙
    if (new_head.x < 0 || new_head.x >= GRID_WIDTH ||
        new_head.y < 0 || new_head.y >= GRID_HEIGHT) {
        game_over = TRUE;
        return;
    }
    
    // 检查撞到自己
    for (int i = 0; i < snake_length; i++) {
        if (snake[i].x == new_head.x && snake[i].y == new_head.y) {
            game_over = TRUE;
            return;
        }
    }
    
    // 检查吃到食物
    BOOL ate_food = (new_head.x == food.x && new_head.y == food.y);
    
    if (ate_food) {
        score += 10;
        snake_length++;
        generate_food();
    }
    
    // 移动蛇身（从尾到头）
    for (int i = snake_length - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }
    snake[0] = new_head;
}

// 绘制游戏画面
void draw_game(HDC hdc) {
    // 背景
    HBRUSH bg_brush = CreateSolidBrush(RGB(240, 240, 240));
    RECT bg_rect = {0, 0, GRID_WIDTH * CELL_SIZE, GRID_HEIGHT * CELL_SIZE};
    FillRect(hdc, &bg_rect, bg_brush);
    DeleteObject(bg_brush);
    
    // 绘制网格（可选，轻微的网格线）
    HPEN grid_pen = CreatePen(PS_SOLID, 1, RGB(220, 220, 220));
    HPEN old_pen = SelectObject(hdc, grid_pen);
    for (int i = 0; i <= GRID_WIDTH; i++) {
        MoveToEx(hdc, i * CELL_SIZE, 0, NULL);
        LineTo(hdc, i * CELL_SIZE, GRID_HEIGHT * CELL_SIZE);
    }
    for (int i = 0; i <= GRID_HEIGHT; i++) {
        MoveToEx(hdc, 0, i * CELL_SIZE, NULL);
        LineTo(hdc, GRID_WIDTH * CELL_SIZE, i * CELL_SIZE);
    }
    SelectObject(hdc, old_pen);
    DeleteObject(grid_pen);
    
    // 绘制食物（红色圆形）
    HBRUSH food_brush = CreateSolidBrush(RGB(255, 0, 0));
    SelectObject(hdc, food_brush);
    Ellipse(hdc, 
            food.x * CELL_SIZE + 2, 
            food.y * CELL_SIZE + 2,
            (food.x + 1) * CELL_SIZE - 2,
            (food.y + 1) * CELL_SIZE - 2);
    DeleteObject(food_brush);
    
    // 绘制蛇（绿色）
    for (int i = 0; i < snake_length; i++) {
        // 蛇头颜色深一点
        COLORREF color = (i == 0) ? RGB(0, 150, 0) : RGB(0, 200, 0);
        HBRUSH snake_brush = CreateSolidBrush(color);
        SelectObject(hdc, snake_brush);
        
        Rectangle(hdc,
                 snake[i].x * CELL_SIZE + 1,
                 snake[i].y * CELL_SIZE + 1,
                 (snake[i].x + 1) * CELL_SIZE - 1,
                 (snake[i].y + 1) * CELL_SIZE - 1);
        DeleteObject(snake_brush);
    }
    
    // 绘制计分板（大字体高亮显示）
    char info[128];
    SetBkMode(hdc, TRANSPARENT);
    
    // 分数（大号红色）
    HFONT score_font = CreateFont(24, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, "Arial");
    HFONT old_font = SelectObject(hdc, score_font);
    SetTextColor(hdc, RGB(255, 0, 0));
    sprintf(info, "得分: %d", score);
    TextOut(hdc, 10, GRID_HEIGHT * CELL_SIZE + 5, info, strlen(info));
    
    // 蛇长度（绿色）
    SetTextColor(hdc, RGB(0, 150, 0));
    sprintf(info, "长度: %d", snake_length);
    TextOut(hdc, 150, GRID_HEIGHT * CELL_SIZE + 5, info, strlen(info));
    SelectObject(hdc, old_font);
    DeleteObject(score_font);
    
    // 操作提示（小字）
    HFONT tip_font = CreateFont(14, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, 0, 0, 0, 0, "微软雅黑");
    SelectObject(hdc, tip_font);
    SetTextColor(hdc, RGB(100, 100, 100));
    sprintf(info, "[空格]暂停 [R]重开");
    TextOut(hdc, 350, GRID_HEIGHT * CELL_SIZE + 10, info, strlen(info));
    SelectObject(hdc, old_font);
    DeleteObject(tip_font);
    
    // 游戏结束提示
    if (game_over) {
        SetTextColor(hdc, RGB(255, 0, 0));
        HFONT font = CreateFont(30, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, "Arial");
        HFONT old_font = SelectObject(hdc, font);
        sprintf(info, "游戏结束！最终分数: %d", score);
        TextOut(hdc, 150, GRID_HEIGHT * CELL_SIZE / 2, info, strlen(info));
        SelectObject(hdc, old_font);
        DeleteObject(font);
    }
    
    // 暂停提示
    if (paused && !game_over) {
        SetTextColor(hdc, RGB(0, 0, 255));
        sprintf(info, "已暂停");
        TextOut(hdc, GRID_WIDTH * CELL_SIZE / 2 - 30, GRID_HEIGHT * CELL_SIZE / 2, info, strlen(info));
    }
}

// 窗口消息处理
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_CREATE:
            srand(time(NULL));
            init_game();
            SetTimer(hwnd, TIMER_ID, GAME_SPEED, NULL);
            break;
            
        case WM_TIMER:
            update_game();
            InvalidateRect(hwnd, NULL, FALSE);  // 触发重绘
            break;
            
        case WM_KEYDOWN:
            switch (wp) {
                case VK_UP:    next_direction = UP; break;
                case VK_DOWN:  next_direction = DOWN; break;
                case VK_LEFT:  next_direction = LEFT; break;
                case VK_RIGHT: next_direction = RIGHT; break;
                case VK_SPACE: paused = !paused; break;  // 暂停/继续
                case 'R':      init_game(); break;       // 重新开始
                case VK_ESCAPE: PostQuitMessage(0); break;
            }
            break;
            
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            
            // 双缓冲绘制（防止闪烁）
            HDC mem_dc = CreateCompatibleDC(hdc);
            HBITMAP mem_bmp = CreateCompatibleBitmap(hdc, 
                GRID_WIDTH * CELL_SIZE, 
                GRID_HEIGHT * CELL_SIZE + 50);
            SelectObject(mem_dc, mem_bmp);
            
            draw_game(mem_dc);
            
            BitBlt(hdc, 0, 0, 
                   GRID_WIDTH * CELL_SIZE, 
                   GRID_HEIGHT * CELL_SIZE + 50,
                   mem_dc, 0, 0, SRCCOPY);
            
            DeleteObject(mem_bmp);
            DeleteDC(mem_dc);
            EndPaint(hwnd, &ps);
            break;
        }
            
        case WM_DESTROY:
            KillTimer(hwnd, TIMER_ID);
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

// 程序入口
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmd, int show) {
    // 注册窗口类
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "SnakeGame";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    RegisterClass(&wc);
    
    // 创建窗口
    int window_width = GRID_WIDTH * CELL_SIZE + 16;
    int window_height = GRID_HEIGHT * CELL_SIZE + 90;
    
    HWND hwnd = CreateWindow(
        "SnakeGame", "🐍 贪吃蛇游戏 | 方向键移动 | 空格暂停 | R重新开始",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, CW_USEDEFAULT,
        window_width, window_height,
        NULL, NULL, hInst, NULL
    );
    
    ShowWindow(hwnd, show);
    UpdateWindow(hwnd);
    
    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}
