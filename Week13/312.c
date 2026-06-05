// 312. Burst Balloons
// Time Best  = O(n^3)
// Time Worst = O(n^3)
// Space      = O(n^2)

#include <stdlib.h>

int maxCoins(int* nums, int numsSize) {
    int n = numsSize;

    // 建立新的陣列，左右補 1
    // nums = [3,1,5,8]
    // arr  = [1,3,1,5,8,1]
    int* arr = (int*)malloc(sizeof(int) * (n + 2));

    arr[0] = 1;
    arr[n + 1] = 1;

    for (int i = 0; i < n; i++) {
        arr[i + 1] = nums[i];
    }

    // dp[left][right]：
    // 代表「戳爆 left 和 right 中間所有氣球」可以拿到的最大分數
    //
    // 注意：left 和 right 本身不戳
    int** dp = (int**)malloc(sizeof(int*) * (n + 2));

    for (int i = 0; i < n + 2; i++) {
        dp[i] = (int*)calloc(n + 2, sizeof(int));
    }

    // len 是區間長度
    // 至少要 left 和 right 中間有氣球，所以 len 從 2 開始
    for (int len = 2; len <= n + 1; len++) {
        for (int left = 0; left + len <= n + 1; left++) {
            int right = left + len;

            // 嘗試讓 k 當作 left 和 right 中間最後被戳爆的氣球
            for (int k = left + 1; k < right; k++) {
                int coins =
                    dp[left][k]
                    + dp[k][right]
                    + arr[left] * arr[k] * arr[right];

                if (coins > dp[left][right]) {
                    dp[left][right] = coins;
                }
            }
        }
    }

    int ans = dp[0][n + 1];

    for (int i = 0; i < n + 2; i++) {
        free(dp[i]);
    }

    free(dp);
    free(arr);

    return ans;
}
