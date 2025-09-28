#include <stdio.h>
#include <stdlib.h>

// 链表结点结构
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// 创建新结点
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// 创建带头结点的空链表
Node* createListWithHead() {
    return createNode(0); // 头结点data可以是任意值
}

// 在链表尾部插入结点
void appendNode(Node* head, int data) {
    Node* newNode = createNode(data);
    Node* current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
}

// 打印带头结点的链表
void printList(Node* head, const char* name) {
    printf("%s: ", name);
    Node* current = head->next; // 跳过头结点
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 核心算法：拆分链表（简洁版）
void splitList(Node* A, Node* B, Node* C) {
    // B复用A的头结点，C新建头结点
    *B = *A;        // B使用A的头结点
    B->next = NULL; // B初始化为空
    C->next = NULL; // C初始化为空
    
    Node* p = A->next; // 工作指针
    Node* r;
    
    while (p != NULL) {
        r = p->next; // 保存后继
        
        if (p->data < 0) {
            // 头插法插入B表
            p->next = B->next;
            B->next = p;
        } else {
            // 头插法插入C表
            p->next = C->next;
            C->next = p;
        }
        
        p = r; // 移动到下一个结点
    }
}

// 释放链表（包括头结点）
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    printf("=== 链表拆分算法演示 ===\n");
    
    // 创建带头结点的链表A
    Node* A = createListWithHead();
    
    // 添加测试数据（正负混合）
    int data[] = {-2, 5, -7, 3, -1, 8, -4, 6};
    int n = sizeof(data) / sizeof(data[0]);
    
    for (int i = 0; i < n; i++) {
        appendNode(A, data[i]);
    }
    
    printf("原链表A: ");
    printList(A, "A");
    
    // 创建C链表头结点，B将复用A的头结点
    Node* B = (Node*)malloc(sizeof(Node));
    Node* C = createListWithHead();
    
    // 执行拆分
    splitList(A, B, C);
    
    printf("\n拆分后:\n");
    printList(A, "链表A"); // 应该只剩头结点
    printList(B, "链表B（负数）");
    printList(C, "链表C（正数）");
    
    // 释放内存
    freeList(A);
    freeList(B);
    freeList(C);
    
    return 0;
}
