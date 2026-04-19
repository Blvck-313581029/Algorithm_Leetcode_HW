//45. Jump Game II
int jump(int* nums, int numsSize) {
    if (numsSize <= 1) return 0;

    int jumps = 0;
    int currentEnd = 0;   // 目前這一跳能覆蓋到的最遠位置
    int farthest = 0;     // 下一跳最多能延伸到哪

    for (int i = 0; i < numsSize - 1; i++) {
        // 在目前這一跳可達範圍內，持續更新下一跳最遠能到哪
        if (i + nums[i] > farthest) {
            farthest = i + nums[i];
        }

        // 走到目前這一跳的邊界，代表該跳了
        if (i == currentEnd) {
            jumps++;
            currentEnd = farthest;
        }
    }

    return jumps;
}
