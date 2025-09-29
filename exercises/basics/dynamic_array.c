#include <stdio.h>
#include <stdlib.h>  // malloc, free

int main() {
    printf("=== 不确定数量时的解决方案 ===\n\n");
    
    // 方案1：预设足够大的数组（简单但浪费）
    printf("方案1 - 预设大数组:\n");
    int numbers[1000];  // 假设最多1000个
    int count = 0;
    printf("预设1000个位置，实际可能只用几个\n");
    printf("优点：简单  缺点：浪费内存\n\n");
    
    // 方案2：运行时确定大小（C99特性）
    printf("方案2 - 运行时确定:\n");
    printf("请输入数组大小: ");
    int size;
    scanf("%d", &size);
    
    int runtime_array[size];  // 运行时才知道大小
    printf("创建了大小为%d的数组\n", size);
    printf("优点：不浪费  缺点：大小固定后不能改\n\n");
    
    // 方案3：动态内存分配（最灵活）
    printf("方案3 - 动态分配:\n");
    int *dynamic_array = malloc(size * sizeof(int));  // 动态申请内存
    if (dynamic_array == NULL) {
        printf("内存分配失败!\n");
        return 1;
    }
    
    // 使用数组
    for (int i = 0; i < size; i++) {
        dynamic_array[i] = i * 10;
    }
    
    printf("动态分配%d个整数:\n", size);
    for (int i = 0; i < size; i++) {
        printf("%d ", dynamic_array[i]);
    }
    printf("\n");
    
    // 不用了要释放内存！
    free(dynamic_array);
    printf("优点：最灵活  缺点：要手动管理内存\n\n");
    
    // 方案4：可扩展数组（高级）
    printf("方案4 - 可扩展数组:\n");
    int capacity = 2;  // 初始容量
    int used = 0;      // 已使用
    int *expandable = malloc(capacity * sizeof(int));
    
    // 模拟添加数据
    for (int i = 0; i < 5; i++) {
        if (used >= capacity) {
            // 容量不够，扩大一倍
            capacity *= 2;
            expandable = realloc(expandable, capacity * sizeof(int));
            printf("扩容到%d个位置\n", capacity);
        }
        expandable[used] = i * 5;
        used++;
    }
    
    printf("最终数据: ");
    for (int i = 0; i < used; i++) {
        printf("%d ", expandable[i]);
    }
    printf("\n优点：按需扩展  缺点：复杂\n");
    
    free(expandable);
    
    printf("\n=== 推荐选择 ===\n");
    printf("• 简单程序：方案1（预设大数组）\n");
    printf("• 知道范围：方案2（运行时确定）\n");
    printf("• 专业开发：方案3（动态分配）\n");
    
    return 0;
}
