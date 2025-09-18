#include <stdio.h>

// 链表节点
struct Node {
    int data;
    struct Node* next;
};

// 判断链表是否递增
int isIncreasing(struct Node* head) {
    // 空链表或只有一个节点就是递增
    if (head == NULL || head->next == NULL) {
        return 1;  // 1表示真
    }
    
    // 检查每相邻两个数
    while (head->next != NULL) {
        if (head->data >= head->next->data) {
            return 0;  // 0表示假，不是递增
        }
        head = head->next;
    }
    
    return 1;  // 是递增的
}

// 自动打印链表的函数
void printList(struct Node* head) {
    printf("链表: ");
    
    // 用循环遍历每个节点
    while (head != NULL) {
        printf("%d", head->data);       // 打印当前节点的数字
        if (head->next != NULL) {       // 如果不是最后一个节点
            printf(" -> ");             // 就打印箭头
        }
        head = head->next;              // 移动到下一个节点
    }
    
    printf("\n");  // 换行
}

int main() {
    // 手动创建一个简单链表: 1 -> 3 -> 5
    struct Node node3 = {5, NULL};
    struct Node node2 = {3, &node3};
    struct Node node1 = {1, &node2};
    
    printList(&node1);  // 自动打印！
    if (isIncreasing(&node1)) {
        printf("结果: 是递增的!\n");
    } else {
        printf("结果: 不是递增的!\n");
    }
    
    // 再测试一个非递增的: 1 -> 3 -> 2
    struct Node bad_node3 = {2, NULL};
    struct Node bad_node2 = {3, &bad_node3};
    struct Node bad_node1 = {1, &bad_node2};
    
    printf("\n");
    printList(&bad_node1);  // 自动打印！
    if (isIncreasing(&bad_node1)) {
        printf("结果: 是递增的!\n");
    } else {
        printf("结果: 不是递增的!\n");
    }
    
    return 0;
}
