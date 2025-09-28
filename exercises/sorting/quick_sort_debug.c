
#include <stdio.h>

// 打印数组的指定范围
void printRange(int arr[], int low, int high, const char* msg) {
    printf("%s [%d..%d]: ", msg, low, high);
    for (int i = low; i <= high; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 打印完整数组，高亮显示范围
void printArrayWithHighlight(int arr[], int n, int low, int high) {
    printf("完整数组: ");
    for (int i = 0; i < n; i++) {
        if (i >= low && i <= high) {
            printf("[%d] ", arr[i]);  // 用[]标记当前处理范围
        } else {
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}

// 交换两个元素
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 分区函数（带调试信息）
int partition(int arr[], int low, int high, int n) {
    printf("\n--- 分区操作 ---\n");
    printf("基准元素: %d (位置 %d)\n", arr[high], high);
    printRange(arr, low, high, "分区前");
    
    int pivot = arr[high];  // 选择最后一个元素作为基准
    int i = low - 1;        // 小于基准的元素的索引
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            if (i != j) {
                printf("交换: %d ↔ %d\n", arr[i], arr[j]);
                swap(&arr[i], &arr[j]);
            }
        }
    }
    
    swap(&arr[i + 1], &arr[high]);
    printf("基准 %d 放到最终位置 %d\n", pivot, i + 1);
    printRange(arr, low, high, "分区后");
    printArrayWithHighlight(arr, n, low, high);
    
    return i + 1;
}

// 快速排序（带调试信息）
void quickSort(int arr[], int low, int high, int n, int depth) {
    if (low < high) {
        printf("\n");
        for (int i = 0; i < depth; i++) printf("  "); // 缩进显示层次
        printf("快排 [%d..%d]\n", low, high);
        
        int pi = partition(arr, low, high, n);
        
        printf("基准位置: %d, 左半部分: [%d..%d], 右半部分: [%d..%d]\n", 
               pi, low, pi-1, pi+1, high);
        
        if (low < pi - 1) {
            quickSort(arr, low, pi - 1, n, depth + 1);   // 排序左半部分
        }
        if (pi + 1 < high) {
            quickSort(arr, pi + 1, high, n, depth + 1); // 排序右半部分
        }
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
    int arr[] = {90, 32, 25, 50, 60};
    int n = 5;
    
    printf("=== 快速排序过程演示 ===\n");
    printf("原始数组: ");
    printArray(arr, n);
    
    quickSort(arr, 0, n - 1, n, 0);
    
    printf("\n=== 排序完成 ===\n");
    printf("最终结果: ");
    printArray(arr, n);
    
    return 0;
}
