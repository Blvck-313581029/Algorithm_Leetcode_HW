//995. Minimum Number of K Consecutive Bit Flips
#include <stdlib.h>

int minKBitFlips(int* nums, int numsSize, int k) {
    int* isFlipped = (int*)calloc(numsSize, sizeof(int));
    int flipCount = 0;   // 目前有效的 flip 次數（只看奇偶）
    int ans = 0;

    for (int i = 0; i < numsSize; i++) {
        // 如果有一個 flip 在 i-k 開始，現在它的影響範圍結束了
        if (i >= k) {
            flipCount -= isFlipped[i - k];
        }

        // nums[i] 在目前 flipCount 影響下的實際值
        // flipCount % 2 == 0: 沒翻奇數次，值不變
        // flipCount % 2 == 1: 被翻奇數次，值反轉
        if ((flipCount % 2) == nums[i]) {
            // 代表現在這格實際上是 0，需要從這裡開始 flip
            if (i + k > numsSize) {
                free(isFlipped);
                return -1;
            }

            isFlipped[i] = 1;
            flipCount++;
            ans++;
        }
    }

    free(isFlipped);
    return ans;
}
