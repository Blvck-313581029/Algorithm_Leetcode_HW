// 581. Shortest Unsorted Continuous Subarray
// Base case / 最小輸入：O(1)
// Best case：O(n)
// Worst case：O(n)
// Space：O(1)

int findUnsortedSubarray(int* nums, int numsSize) {
    int left = -1;
    int right = -1;

    int maxSeen = nums[0];
    int minSeen = nums[numsSize - 1];

    // 從左到右掃
    // 如果 nums[i] 比前面看過的最大值還小
    // 代表 nums[i] 位置不對，right 要更新
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < maxSeen) {
            right = i;
        } else {
            maxSeen = nums[i];
        }
    }

    // 從右到左掃
    // 如果 nums[i] 比右邊看過的最小值還大
    // 代表 nums[i] 位置不對，left 要更新
    for (int i = numsSize - 2; i >= 0; i--) {
        if (nums[i] > minSeen) {
            left = i;
        } else {
            minSeen = nums[i];
        }
    }

    // 如果 right 沒被更新，代表本來就是排序好的
    if (right == -1) {
        return 0;
    }

    return right - left + 1;
}
