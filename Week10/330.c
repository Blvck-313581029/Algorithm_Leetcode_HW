// 330. Patching Array
// Base case / 最小輸入：O(1)
// Best case：O(m)
// Worst case：O(m + log n)
// Space：O(1)
//
// m = numsSize

int minPatches(int* nums, int numsSize, int n) {
    long long miss = 1;  // 目前最小還不能被組出來的數字
    int i = 0;
    int patches = 0;

    while (miss <= n) {
        // 如果 nums[i] <= miss
        // 代表 nums[i] 可以幫我們擴大覆蓋範圍
        if (i < numsSize && nums[i] <= miss) {
            miss += nums[i];
            i++;
        } 
        // 如果 nums[i] > miss
        // 代表 miss 這個數字目前組不出來
        // 最好的補法就是直接補 miss
        else {
            miss += miss;
            patches++;
        }
    }

    return patches;
}
