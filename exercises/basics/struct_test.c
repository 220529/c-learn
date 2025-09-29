#include <stdio.h>
#include <string.h>

struct Student {
    int id;
    char name[20];
    float score;
};

int main() {
    // 创建结构体变量
    struct Student s1 = {1001, "Tom", 95.5};
    
    // 直接访问
    printf("直接访问: %d, %s, %.1f\n", s1.id, s1.name, s1.score);
    
    // 指针访问
    struct Student *ptr = &s1;
    printf("指针访问: %d, %s, %.1f\n", ptr->id, ptr->name, ptr->score);
    
    // 修改值
    ptr->id = 1002;
    strcpy(ptr->name, "Alice");
    ptr->score = 88.0;
    
    printf("修改后: %d, %s, %.1f\n", s1.id, s1.name, s1.score);
    
    return 0;
}