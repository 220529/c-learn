#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void log(struct Node* head) {
    // head = head->next;
    while (head != NULL) {
        printf("%d", head->data);
        printf("\n");
        head = head->next;
    }
}

int split(struct Node* A, struct Node* B, struct Node* C) {
    struct Node* prev = A;
    struct Node* r;
    while (prev != NULL) {
        r = prev->next;
        if (prev->data < 0) {
            prev->next = B->next;
            B->next = prev;
        } else {
            prev->next = C->next;
            C->next = prev;
        }
        prev = r;
    }
}

struct Node* createHead() {
    struct Node* head = malloc(sizeof(struct Node));
    head->next = NULL;
    return head;
}

int main() {
    int arr[5] = {-1, 2, -3, 4, -5};
    struct Node* A = (struct Node*)malloc(sizeof(struct Node));
    struct Node* prev;
    for (int i = 0; i <5; i++) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = arr[i];
        if (i == 0) {
            A = newNode;
        } else {
            prev->next = newNode;
        }
        prev = newNode;
    }
    // log(A);
    struct Node* B = (struct Node*)malloc(sizeof(struct Node));
    struct Node* C = (struct Node*)malloc(sizeof(struct Node));
    split(A, B, C);
    log(A);
    log(B);
    log(C);
    free(A);
    free(B);
    free(C);
    return 0;
}
