//3165. Maximum Sum of Subsequence With Non-adjacent Elements
#include <stdlib.h>

#define MOD 1000000007LL
#define NEG -(1LL<<60)

typedef struct {
    long long a00, a01, a10, a11;
} Node;

static Node *seg;

static inline long long mx(long long a, long long b) {
    return a > b ? a : b;
}

static inline Node merge(Node L, Node R) {
    Node C;
    C.a00 = mx(R.a00 + L.a00, R.a01 + L.a10);
    C.a01 = mx(R.a00 + L.a01, R.a01 + L.a11);
    C.a10 = mx(R.a10 + L.a00, R.a11 + L.a10);
    C.a11 = mx(R.a10 + L.a01, R.a11 + L.a11);
    return C;
}

static inline Node leaf(int x) {
    Node t;
    t.a00 = 0;
    t.a01 = 0;
    t.a10 = x;
    t.a11 = NEG;
    return t;
}

static void build(int i, int l, int r, int *nums) {
    if (l == r) {
        seg[i] = leaf(nums[l]);
        return;
    }
    int m = (l + r) >> 1;
    build(i << 1, l, m, nums);
    build(i << 1 | 1, m + 1, r, nums);
    seg[i] = merge(seg[i << 1], seg[i << 1 | 1]);
}

static void update(int i, int l, int r, int p, int x) {
    if (l == r) {
        seg[i] = leaf(x);
        return;
    }
    int m = (l + r) >> 1;
    if (p <= m) update(i << 1, l, m, p, x);
    else update(i << 1 | 1, m + 1, r, p, x);
    seg[i] = merge(seg[i << 1], seg[i << 1 | 1]);
}

int maximumSumSubsequence(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    seg = (Node*)malloc(sizeof(Node) * (numsSize * 4 + 5));
    build(1, 0, numsSize - 1, nums);

    long long ans = 0;
    for (int i = 0; i < queriesSize; i++) {
        int pos = queries[i][0];
        int x = queries[i][1];
        update(1, 0, numsSize - 1, pos, x);
        ans = (ans + mx(seg[1].a00, seg[1].a10)) % MOD;
    }

    free(seg);
    return (int)ans;
}