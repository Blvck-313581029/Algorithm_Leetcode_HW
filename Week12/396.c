//396. Rotate Function
int maxRotateFunction(int* nums, int numsSize) {
    int n = numsSize;

    int sum = 0;
    int curr = 0;

    // 先算 sum 和 F(0)
    for (int i = 0; i < n; i++) {
        sum += nums[i];
        curr += i * nums[i];
    }

    int ans = curr;

    // 依序算 F(1), F(2), ..., F(n-1)
    for (int k = 1; k < n; k++) {
        curr = curr + sum - n * nums[n - k];

        if (curr > ans) {
            ans = curr;
        }
    }

    return ans;
}
