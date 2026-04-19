//1499. Max Value of Equation
#include <limits.h>
#include <stdlib.h>
//yi-xi+yj+xj max(yi+xi)
//xj-xi<=k
//[[1,3],[2,0],[5,10],[6,-10]], k = 1
// Base case / 最小輸入：O(1)
// Best case：O(n)
// Worst case：O(n)
// Space：O(n)
int findMaxValueOfEquation(int** points, int pointsSize, int* pointsColSize, int k) {
    // deque 裡面存的是 index
    int* deque = (int*)malloc(sizeof(int) * pointsSize);
    int front = 0, back = 0;

    int ans = INT_MIN;

    for (int j = 0; j < pointsSize; j++) {
        int xj = points[j][0];
        int yj = points[j][1];

        // 1. 把不合法的點從前面丟掉
        while (front < back && xj - points[deque[front]][0] > k) {
            front++;
        }

        // 2. 如果 deque 還有合法點，拿最前面那個來更新答案
        if (front < back) {
            int i = deque[front];
            int xi = points[i][0];
            int yi = points[i][1];

            int value = yi + yj + (xj - xi);
            if (value > ans) {
                ans = value;
            }
        }

        // 3. 現在要把 j 放進 deque
        //    但先把後面比它差的都丟掉
        int current = yj - xj;
        while (front < back) {
            int last = deque[back - 1];
            int lastValue = points[last][1] - points[last][0];

            if (lastValue <= current) {
                back--;
            } else {
                break;
            }
        }

        deque[back++] = j;
    }

    free(deque);
    return ans;
}
