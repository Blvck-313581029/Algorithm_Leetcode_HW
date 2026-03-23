//493. Reverse Pairs
#include <stdlib.h>

// 優化點：傳入輔助空間 temp，避免在遞歸中反覆 malloc
long long mergeAndCount(int* nums, int* temp, int left, int mid, int right) {
    long long count = 0;
    
    // 1. 計算 Reverse Pairs (維持不變，這步是 O(n))
    int j = mid + 1;
    for (int i = left; i <= mid; i++) {
        while (j <= right && (long long)nums[i] > 2 * (long long)nums[j]) {
            j++;
        }
        count += (j - (mid + 1));
    }

    // 2. 合併過程：使用 temp 數組減少分配開銷
    int i = left;
    int k = left;
    int right_start = mid + 1;
    int p1 = left, p2 = mid + 1;

    while (p1 <= mid && p2 <= right) {
        if (nums[p1] <= nums[p2]) {
            temp[k++] = nums[p1++];
        } else {
            temp[k++] = nums[p2++];
        }
    }
    while (p1 <= mid) temp[k++] = nums[p1++];
    while (p2 <= right) temp[k++] = nums[p2++];

    // 將合併後的結果考回原數組
    for (i = left; i <= right; i++) {
        nums[i] = temp[i];
    }

    return count;
}

long long solve(int* nums, int* temp, int left, int right) {
    if (left >= right) return 0;
    int mid = left + (right - left) / 2;
    
    long long count = solve(nums, temp, left, mid);
    count += solve(nums, temp, mid + 1, right);
    count += mergeAndCount(nums, temp, left, mid, right);
    
    return count;
}

int reversePairs(int* nums, int numsSize) {
    if (numsSize < 2) return 0;
    
    // 在這裡一次性分配輔助空間
    int* temp = (int*)malloc(sizeof(int) * numsSize);
    long long result = solve(nums, temp, 0, numsSize - 1);
    free(temp);
    
    return (int)result;
}