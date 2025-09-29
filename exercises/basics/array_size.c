#include <stdio.h>

int main() {
    printf("=== 数组大小声明规则 ===\n\n");
    
    // 情况1：必须指定大小
    int nums[3];  // 必须写[3]
    nums[0] = 10;
    nums[1] = 20; 
    nums[2] = 30;
    
    // 情况2：可以省略大小（自动推断）
    int auto_nums[] = {100, 200, 300, 400};  // 自动是[4]
    char greeting[] = "Hello";               // 自动是[6]（包含\0）
    
    printf("手动指定: ");
    for (int i = 0; i < 3; i++) {
        printf("%d ", nums[i]);
    }
    
    printf("\n自动推断: ");
    for (int i = 0; i < 4; i++) {
        printf("%d ", auto_nums[i]);
    }
    
    printf("\n字符串: %s\n", greeting);
    
    // 显示实际大小
    printf("\n=== 实际大小 ===\n");
    printf("nums 大小: %zu 字节\n", sizeof(nums));
    printf("auto_nums 大小: %zu 字节\n", sizeof(auto_nums));
    printf("greeting 大小: %zu 字节\n", sizeof(greeting));
    
    return 0;
}
