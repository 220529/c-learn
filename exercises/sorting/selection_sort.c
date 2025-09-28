#include <stdio.h>

// 简单选择排序
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int minIndex = i;
        
        // 找最小值的位置
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        // 交换
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

// 打印数组
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {64, 25, 12, 22, 11, 90};
    int n = 6;
    
    printf("排序前: ");
    printArray(arr, n);
    
    selectionSort(arr, n);
    
    printf("排序后: ");
    printArray(arr, n);
    
    return 0;
}