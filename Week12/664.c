// 664. Strange Printer
// Base case / 最小輸入：O(1)
// Best case：O(n^3)
// Worst case：O(n^3)
// Space：O(n^2)

#include <string.h>
#include <stdlib.h>

int minInt(int a, int b) {
    return a < b ? a : b;
}

int strangePrinter(char* s) {
    int n = strlen(s);

    if (n == 0) {
        return 0;
    }

    int dp[101][101];

    // 初始化
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;   // 單一字元，只要印一次
    }

    // len 表示目前處理的區間長度
    for (int len = 2; len <= n; len++) {
        for (int i = 0; i + len - 1 < n; i++) {
            int j = i + len - 1;

            // 最壞情況：s[j] 自己單獨印一次
            dp[i][j] = dp[i][j - 1] + 1;

            // 嘗試找前面有沒有跟 s[j] 一樣的字元
            for (int k = i; k < j; k++) {
                if (s[k] == s[j]) {
                    /*
                        如果 s[k] == s[j]
                        那 s[j] 不一定要自己多印一次
                        可以跟 s[k] 合併成同一次印
                    */
                    int cost;

                    if (k + 1 <= j - 1) {
                        cost = dp[i][k] + dp[k + 1][j - 1];
                    } else {
                        cost = dp[i][k];
                    }

                    dp[i][j] = minInt(dp[i][j], cost);
                }
            }
        }
    }

    return dp[0][n - 1];
}
