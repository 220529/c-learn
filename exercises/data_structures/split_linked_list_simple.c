#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// 创建空链表头结点
struct Node* createHead() {
    struct Node* head = malloc(sizeof(struct Node));
    head->next = NULL;
    return head;
}

// 打印链表
void printList(struct Node* head, const char* name) {
    printf("%s: ", name);
    struct Node* p = head->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 拆分链表：负数放B表，正数放C表
void splitList(struct Node* A, struct Node** B, struct Node** C) {
    struct Node* p = A->next;  // 当前处理的节点
    
    *B = createHead();  // 创建B表头结点
    *C = createHead();  // 创建C表头结点
    
    while (p) {
        struct Node* next = p->next;  // 保存下一个节点
        
        if (p->data < 0) {
            // 头插法插入B表
            p->next = (*B)->next;
            (*B)->next = p;
        } else {
            // 头插法插入C表
            p->next = (*C)->next;
            (*C)->next = p;
        }
        
        p = next;
    }
}

int main() {
    // 创建测试链表：-2 -> 5 -> -1 -> 3 -> -4 -> 7
    struct Node* A = createHead();
    
    int data[] = {-2, 5, -1, 3, -4, 7};
    struct Node* tail = A;
    
    for (int i = 0; i < 6; i++) {
        struct Node* node = malloc(sizeof(struct Node));
        node->data = data[i];
        node->next = NULL;
        tail->next = node;
        tail = node;
    }
    
    printList(A, "拆分前");
    
    struct Node* B, *C;
    splitList(A, &B, &C);
    
    printList(B, "负数表");
    printList(C, "正数表");
    
    // 释放内存
    free(A);
    free(B);
    free(C);
    
    return 0;
}
