// 410. Split Array Largest Sum
// Base case / 程块O(n)
// Best caseO(n log S)
// Worst caseO(n log S)
// SpaceO(1)
//
// S = sum(nums) - max(nums)

#include <stdbool.h>

bool canSplit(int* nums, int numsSize, int k, int maxAllowedSum) {
    int count = 1;       // ぶΤ琿
    long long curr = 0;  // ヘ玡硂琿羆㎝

    for (int i = 0; i < numsSize; i++) {
        // 狦 nums[i] 穦禬筁碞ち琿穝
        if (curr + nums[i] > maxAllowedSum) {
            count++;
            curr = nums[i];

            // 狦琿计禬筁 k maxAllowedSum び
            if (count > k) {
                return false;
            }
        } else {
            curr += nums[i];
        }
    }

    return true;
}

int splitArray(int* nums, int numsSize, int k) {
    int left = 0;
    int right = 0;

    // left = 虫じ程
    // right = 场じ羆㎝
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > left) {
            left = nums[i];
        }
        right += nums[i];
    }

    // Binary Search т程︽程皚㎝
    while (left < right) {
        int mid = left + (right - left) / 2;

        if (canSplit(nums, numsSize, k, mid)) {
            // mid 暗氮
            right = mid;
        } else {
            // mid びちㄓ穦禬筁 k 琿
            left = mid + 1;
        }
    }

    return left;
}
