// test.c - 使用工具函数
#include <stdio.h>
#include "utils.h"  // 引入头文件

int main() {
    // 测试 swap
    int x = 10, y = 20;
    printf("交换前: x=%d, y=%d\n", x, y);
    swap(&x, &y);
    printf("交换后: x=%d, y=%d\n\n", x, y);
    
    // 测试 max
    printf("max(15, 8) = %d\n", max(15, 8));
    printf("max(100, 200) = %d\n\n", max(100, 200));
    
    // 测试 print_array
    int arr[] = {3, 1, 4, 1, 5, 9};
    printf("数组内容: ");
    print_array(arr, 6);
    
    return 0;
}
