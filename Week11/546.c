// 546. Remove Boxes
// Base case / 最小輸入：O(1)
// Best case：O(n^3)
// Worst case：O(n^4)
// Space：O(n^3)

#include <stdlib.h>
#include <string.h>

int dp[100][100][100];

int max(int a, int b) {
    return a > b ? a : b;
}

// dfs(l, r, k)
// 處理 boxes[l...r]
// k 表示 boxes[r] 右邊還接著 k 個跟 boxes[r] 同色的盒子
int dfs(int* boxes, int l, int r, int k) {
    if (l > r) {
        return 0;
    }

    // 重點：先把尾巴連續同色合併
    // 這樣狀態會被標準化，dp 才能有效命中
    while (l < r && boxes[r] == boxes[r - 1]) {
        r--;
        k++;
    }

    // 合併完之後再查 dp
    if (dp[l][r][k] != 0) {
        return dp[l][r][k];
    }

    // Case 1：
    // 直接刪掉 boxes[r] + 右邊 k 個同色盒子
    int ans = dfs(boxes, l, r - 1, 0) + (k + 1) * (k + 1);

    // Case 2：
    // 找前面跟 boxes[r] 同色的位置
    // 先刪掉中間，讓 boxes[i] 和 boxes[r] 接起來
    for (int i = l; i < r; i++) {
        if (boxes[i] == boxes[r]) {
            int temp = dfs(boxes, l, i, k + 1)
                     + dfs(boxes, i + 1, r - 1, 0);

            ans = max(ans, temp);
        }
    }

    dp[l][r][k] = ans;
    return ans;
}

int removeBoxes(int* boxes, int boxesSize) {
    memset(dp, 0, sizeof(dp));
    return dfs(boxes, 0, boxesSize - 1, 0);
}
