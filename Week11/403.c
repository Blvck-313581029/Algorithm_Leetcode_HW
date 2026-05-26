// 403. Frog Jump
// Base case / 最小輸入：O(1)
// Best case：O(n^2 log n)
// Worst case：O(n^2 log n)
// Space：O(n^2)

#include <stdbool.h>
#include <stdlib.h>

int findStone(int* stones, int stonesSize, int target) {
    int left = 0;
    int right = stonesSize - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (stones[mid] == target) {
            return mid;
        } else if (stones[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}

bool canCross(int* stones, int stonesSize) {
    if (stonesSize <= 1) {
        return true;
    }

    // 第一跳一定要是 1
    if (stones[1] != 1) {
        return false;
    }

    // 只有兩顆石頭：[0,1]
    // 第一跳成功後就已經到終點
    if (stonesSize == 2) {
        return true;
    }

    int n = stonesSize;

    // dp[i][k] = true
    // 代表可以用「上一跳長度 k」跳到第 i 顆石頭
    bool** dp = (bool**)malloc(n * sizeof(bool*));
    for (int i = 0; i < n; i++) {
        dp[i] = (bool*)calloc(n + 1, sizeof(bool));
    }

    dp[1][1] = true;

    for (int i = 1; i < n; i++) {
        for (int k = 1; k <= n; k++) {
            if (!dp[i][k]) {
                continue;
            }

            for (int jump = k - 1; jump <= k + 1; jump++) {
                if (jump <= 0) {
                    continue;
                }

                int nextPos = stones[i] + jump;
                int nextIndex = findStone(stones, n, nextPos);

                if (nextIndex != -1) {
                    if (nextIndex == n - 1) {
                        for (int a = 0; a < n; a++) {
                            free(dp[a]);
                        }
                        free(dp);
                        return true;
                    }

                    if (jump <= n) {
                        dp[nextIndex][jump] = true;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return false;
}
