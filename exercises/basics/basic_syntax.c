#include <stdio.h>

int main() {
    printf("=== C语言基础语法 ===\n\n");
    
    // 1. 循环 - 重复做事情
    printf("1. for循环 - 数1到5:\n");
    for (int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n\n");
    
    // 2. 条件判断 - 做选择
    printf("2. 条件判断:\n");
    int age = 18;
    if (age >= 18) {
        printf("已成年 ✅\n");
    } else {
        printf("未成年 ❌\n");
    }
    
    // 3. 数组遍历
    printf("\n3. 处理数组:\n");
    int numbers[] = {10, 20, 30};
    int size = 3;
    
    printf("数组: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");
    
    // 4. while循环
    printf("\n4. while循环倒计时:\n");
    int count = 3;
    while (count > 0) {
        printf("%d ", count);
        count--;
    }
    printf("发射! 🚀\n\n");
    
    // 5. switch选择
    printf("5. switch选择:\n");
    int choice = 2;
    switch (choice) {
        case 1: printf("选项1\n"); break;
        case 2: printf("选项2 ✅\n"); break;
        default: printf("其他选项\n"); break;
    }
    
    printf("\n=== 语法总结 ===\n");
    printf("• for: 知道次数的循环\n");
    printf("• while: 条件循环\n");
    printf("• if/else: 条件判断\n");
    printf("• switch: 多分支选择\n");
    
    return 0;
}
