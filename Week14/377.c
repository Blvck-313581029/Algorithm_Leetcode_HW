// 377. Combination Sum IV
// Time Best  = O(target * numsSize)
// Time Worst = O(target * numsSize)
// Space      = O(target)
#include <stdlib.h>

int combinationSum4(int* nums, int numsSize, int target) {
    // dp[i] = 湊出總和 i 的方法數
    unsigned int* dp = (unsigned int*)calloc(target + 1, sizeof(unsigned int));

    // 湊出 0 的方法有 1 種：什麼都不選
    dp[0] = 1;

    for (int sum = 1; sum <= target; sum++) {
        for (int i = 0; i < numsSize; i++) {
            int num = nums[i];

            if (sum >= num) {
                dp[sum] += dp[sum - num];
            }
        }
    }

    int ans = dp[target];
    free(dp);

    return ans;
}
