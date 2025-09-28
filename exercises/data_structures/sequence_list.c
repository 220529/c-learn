#include <stdio.h>
#define MAX_SIZE 100

// 顺序表结构
typedef struct {
    int data[MAX_SIZE];
    int length;
} SeqList;

// 初始化顺序表
void initList(SeqList* list) {
    list->length = 0;
}

// 插入元素到指定位置
int insert(SeqList* list, int pos, int value) {
    if (pos < 0 || pos > list->length || list->length >= MAX_SIZE) {
        return 0; // 插入失败
    }
    
    // 元素后移
    for (int i = list->length; i > pos; i--) {
        list->data[i] = list->data[i-1];
    }
    
    list->data[pos] = value;
    list->length++;
    return 1; // 插入成功
}

// 删除指定位置的元素
int delete(SeqList* list, int pos) {
    if (pos < 0 || pos >= list->length) {
        return 0; // 删除失败
    }
    
    // 元素前移
    for (int i = pos; i < list->length - 1; i++) {
        list->data[i] = list->data[i+1];
    }
    
    list->length--;
    return 1; // 删除成功
}

// 查找元素，返回位置
int search(SeqList* list, int value) {
    for (int i = 0; i < list->length; i++) {
        if (list->data[i] == value) {
            return i;
        }
    }
    return -1; // 未找到
}

// 打印顺序表
void printList(SeqList* list) {
    printf("顺序表: [");
    for (int i = 0; i < list->length; i++) {
        printf("%d", list->data[i]);
        if (i < list->length - 1) printf(", ");
    }
    printf("] 长度: %d\n", list->length);
}

int main() {
    SeqList list;
    initList(&list);
    
    printf("=== 顺序表操作演示 ===\n");
    
    // 插入操作
    insert(&list, 0, 10);
    insert(&list, 1, 20);
    insert(&list, 2, 30);
    insert(&list, 1, 15); // 在位置1插入15
    printf("插入后: ");
    printList(&list);
    
    // 查找操作
    int pos = search(&list, 20);
    printf("查找20的位置: %d\n", pos);
    
    // 删除操作
    delete(&list, 1);
    printf("删除位置1后: ");
    printList(&list);
    
    return 0;
}
