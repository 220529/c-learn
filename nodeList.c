#include <stdio.h>

struct Node {
    int data;
    struct Node* next;
};

void printNodeList(struct Node* head) {
    printf("NodeList: ");
    while(head != NULL) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
};

int main() {
    printf("hello world\n");
    struct Node node5 = {5, NULL};
    struct Node node4 = {4, &node5};
    struct Node node3 = {3, &node4};
    struct Node node2 = {2, &node3};
    struct Node node1 = {1, &node2};
    printNodeList(&node1);
    // node3.data = node4.data;
    // node3.next = node4.next;
    struct Node node6 = {6, NULL};
    node6.next = node3.next;
    node3.next = &node6;
    printNodeList(&node1);
    return 0;
}