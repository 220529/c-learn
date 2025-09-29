#include <stdio.h>

int main() {
    printf("=== C语言指针演示 ===\n\n");
    
    // 原子类型变量
    int age = 25;
    
    // 指针变量（派生类型）
    int* ptr = &age;  // ptr存储age的内存地址
    
    printf("变量 age 的值: %d\n", age);
    printf("变量 age 的地址: %p\n", &age);
    printf("指针 ptr 的值: %p\n", ptr);
    printf("通过指针访问age: %d\n", *ptr);
    
    // 修改值
    *ptr = 30;  // 通过指针修改age的值
    printf("\n修改后:\n");
    printf("age的值: %d\n", age);
    printf("通过指针访问: %d\n", *ptr);
    
    printf("\n=== 指针特点 ===\n");
    printf("1. 存储其他变量的内存地址\n");
    printf("2. & = 取地址符\n");
    printf("3. * = 解引用符（通过地址访问值）\n");
    printf("4. 指针本身也是变量\n");
    
    return 0;
}
