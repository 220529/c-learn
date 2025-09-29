#include <stdio.h>
#include <stdlib.h>  // 必须包含这个！malloc/free在这里定义

int main() {
    printf("=== malloc/free 不是关键字！===\n\n");
    
    printf("1. malloc/free 是标准库函数\n");
    printf("2. 定义在 <stdlib.h> 头文件中\n");
    printf("3. 如果不#include <stdlib.h>，编译会警告\n\n");
    
    // 演示malloc的函数特性
    printf("=== malloc的函数签名 ===\n");
    printf("void* malloc(size_t size);\n");
    printf("void free(void* ptr);\n\n");
    
    // 实际使用
    printf("=== 实际使用 ===\n");
    int *ptr = malloc(5 * sizeof(int));  // 函数调用！
    
    if (ptr != NULL) {
        printf("成功分配内存\n");
        ptr[0] = 100;
        printf("存储数据: %d\n", ptr[0]);
        
        free(ptr);  // 也是函数调用！
        printf("释放内存\n");
    }
    
    printf("\n=== 证明它们是函数 ===\n");
    printf("• 可以通过函数指针使用\n");
    printf("• 可以被重新实现\n");
    printf("• 有返回值和参数\n");
    printf("• 需要#include才能使用\n");
    
    return 0;
}
