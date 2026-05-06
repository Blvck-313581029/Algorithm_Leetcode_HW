// 2366. Minimum Replacements to Sort the Array
long long minimumReplacement(int* nums, int numsSize) {
    long long ans = 0;

    // right 表示：目前左邊的數字，最多只能變成多少
    int right = nums[numsSize - 1];

    for (int i = numsSize - 2; i >= 0; i--) {
        int x = nums[i];

        if (x <= right) {
            // 不用拆，直接更新 right
            right = x;
        } else {
            // x 太大，要拆成 k 份
            // 每一份都要 <= right
            int k = (x + right - 1) / right;  // ceil(x / right)

            // 拆成 k 份，需要 k - 1 次操作
            ans += k - 1;

            // 拆完後，左邊最多只能接最小那份
            right = x / k;
        }
    }

    return ans;
}