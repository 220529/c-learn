#include <stdio.h>

// 直接插入排序（标准写法）
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        for (int j = i; j > 0; j--) {
            if (arr[j] < arr[j - 1]) {
                int temp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = temp;
            } else {
                break;
            }
        }
    }
}

int main() {
    int arr[] = {5, 2, 4, 6, 1, 3};
    int n = 6;
    
    printf("排序前: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    insertionSort(arr, n);
    
    printf("排序后: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    return 0;
}

