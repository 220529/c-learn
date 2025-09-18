#include <stdio.h>

int main() {
    // 正确的用法
    char* ptr = NULL;    // ✅ NULL是正确的
    
    printf("ptr = %p\n", ptr);
    printf("NULL在C语言中表示空指针\n");
    
    // 下面这行如果取消注释会编译错误：
    // char* ptr2 = null;  // ❌ 编译错误！null不存在
    
    return 0;
}
