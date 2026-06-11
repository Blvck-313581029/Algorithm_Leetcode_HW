// 1187. Make Array Strictly Increasing
// Time Best  = O(arr2Size log arr2Size + arr1Size^2 log arr2Size)

// Time Worst = O(arr2Size log arr2Size + arr1Size^2 log arr2Size)

// Space      = O(arr1Size)


#include <stdlib.h>
#include <limits.h>

#define INF 1000000000

int cmp(const void* a, const void* b) {
    return (*(int*)a) - (*(int*)b);
}

// т arr い材 > target 竚
int upperBound(int* arr, int size, int target) {
    int left = 0;
    int right = size;

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] <= target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}

int makeArrayIncreasing(int* arr1, int arr1Size, int* arr2, int arr2Size) {
    // 逼 arr2
    qsort(arr2, arr2Size, sizeof(int), cmp);

    // 埃 arr2 狡じ
    int m = 0;
    for (int i = 0; i < arr2Size; i++) {
        if (i == 0 || arr2[i] != arr2[i - 1]) {
            arr2[m++] = arr2[i];
        }
    }

    /*
        dp[k] = 暗 k Ω蠢传
                ヘ玡程计程琌ぶ

        ぐ或璶癘程程计
        程计禫禫甧钡计
    */
    int maxOps = arr1Size;

    int* dp = (int*)malloc(sizeof(int) * (maxOps + 1));
    int* next = (int*)malloc(sizeof(int) * (maxOps + 1));

    for (int i = 0; i <= maxOps; i++) {
        dp[i] = INF;
    }

    // 秨﹍临⊿Τヴ计程计跌璽礚
    dp[0] = INT_MIN;

    for (int i = 0; i < arr1Size; i++) {
        for (int k = 0; k <= maxOps; k++) {
            next[k] = INF;
        }

        for (int k = 0; k <= i; k++) {
            if (dp[k] == INF) {
                continue;
            }

            int prev = dp[k];

            // 匡拒 1玂痙 arr1[i]
            if (arr1[i] > prev) {
                if (arr1[i] < next[k]) {
                    next[k] = arr1[i];
                }
            }

            // 匡拒 2ノ arr2 柑材 > prev 计蠢传 arr1[i]
            int idx = upperBound(arr2, m, prev);

            if (idx < m && k + 1 <= maxOps) {
                if (arr2[idx] < next[k + 1]) {
                    next[k + 1] = arr2[idx];
                }
            }
        }

        int* temp = dp;
        dp = next;
        next = temp;
    }

    for (int k = 0; k <= maxOps; k++) {
        if (dp[k] != INF) {
            free(dp);
            free(next);
            return k;
        }
    }

    free(dp);
    free(next);
    return -1;
}
