//1383. Maximum Performance of a Team
#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

// 最小堆 (min-heap) 結構
int heap[100001];
int heapSize = 0;

void push(int val) {
    heap[heapSize++] = val;
    // 向上調整 (bubble up)
    int i = heapSize - 1;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent] > heap[i]) {
            int tmp = heap[parent];
            heap[parent] = heap[i];
            heap[i] = tmp;
            i = parent;
        } else break;
    }
}

void pop() {
    heap[0] = heap[--heapSize];
    // 向下調整 (bubble down)
    int i = 0;
    while (1) {
        int smallest = i;
        int l = 2 * i + 1, r = 2 * i + 2;
        if (l < heapSize && heap[l] < heap[smallest]) smallest = l;
        if (r < heapSize && heap[r] < heap[smallest]) smallest = r;
        if (smallest == i) break;
        int tmp = heap[smallest];
        heap[smallest] = heap[i];
        heap[i] = tmp;
        i = smallest;
    }
}

int top() { return heap[0]; }

// 排序用：按效率由高到低
int engineers[100001][2]; // [efficiency, speed]

int cmp(const void* a, const void* b) {
    return ((int*)b)[0] - ((int*)a)[0]; // 效率降序
}

int maxPerformance(int n, int* speed, int speedSize, int* efficiency, int efficiencySize, int k) {
    heapSize = 0;

    // 把 speed 和 efficiency 配對，並按效率排序
    for (int i = 0; i < n; i++) {
        engineers[i][0] = efficiency[i];
        engineers[i][1] = speed[i];
    }
    qsort(engineers, n, sizeof(engineers[0]), cmp);

    long long speedSum = 0;
    long long maxPerf = 0;

    for (int i = 0; i < n; i++) {
        int eff = engineers[i][0];
        int spd = engineers[i][1];

        // 將當前工程師加入堆
        push(spd);
        speedSum += spd;

        // 若超過 k 人，移除速度最慢的
        if (heapSize > k) {
            speedSum -= top();
            pop();
        }

        // 計算以當前 eff 為最小效率的績效
        long long perf = speedSum * eff;
        if (perf > maxPerf) maxPerf = perf;
    }

    return (int)(maxPerf % MOD);
}
