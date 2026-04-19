//154
//M<R 砍R //M>R 砍L //M=R r-=1 
// Base case: O(1)
// Best case: O(log n)
// Worst case: O(n)
// Space: O(1)
int findMin(int* nums, int numsSize) {
    // O(logn)（若有很多重複值，最差可能退化成 O(n)）

    int l = 0;
    int r = numsSize - 1;

    // only 2 element
    if (r < 2) {
        return nums[0] < nums[numsSize - 1] ? nums[0] : nums[numsSize - 1];
    }

    while (1) {
        // if slice elements shorter than 3 element (index)
         if (r - l <= 2) {
            break;
        }

        int mid = (l + r) / 2;

        if (nums[mid] > nums[r]) {
            // 斷層在右邊，最小值一定在 mid 右側
            l = mid + 1;
        } else if (nums[mid] < nums[r]) {
            // 右半邊是升序，最小值在左邊（包含 mid 本身）
            r = mid;
        } else {
            // 遇到重複值，無法判斷方向，右界縮小一格
            r -= 1;
        }
    }

    // fewer than 3 elements
    int ans = nums[l];
    for (int i = l + 1; i <= r; i++) {
        if (nums[i] < ans) {
            ans = nums[i];
        }
    }

    return ans;
}
