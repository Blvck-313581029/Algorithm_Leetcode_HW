//3165. Maximum Sum of Subsequence With Non-adjacent Elements
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














#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 50005
#define MOD 1000000007LL

typedef long long ll;
#define NEG_INF (-4000000000000LL)

// 每個節點儲存 f[first_taken][last_taken]
typedef struct {
    ll f[2][2];
} Node;

Node tree[4 * MAXN];
int N;

// 合併左右子節點
Node combine(Node L, Node R) {
    Node res;
    for (int a = 0; a < 2; a++) {
        for (int b = 0; b < 2; b++) {
            res.f[a][b] = NEG_INF;
            // 三種合法的 (左末c, 右首d) 組合
            // (c=0, d=0)
            if (L.f[a][0] != NEG_INF && R.f[0][b] != NEG_INF) {
                ll v = L.f[a][0] + R.f[0][b];
                if (v > res.f[a][b]) res.f[a][b] = v;
            }
            // (c=0, d=1)
            if (L.f[a][0] != NEG_INF && R.f[1][b] != NEG_INF) {
                ll v = L.f[a][0] + R.f[1][b];
                if (v > res.f[a][b]) res.f[a][b] = v;
            }
            // (c=1, d=0)
            if (L.f[a][1] != NEG_INF && R.f[0][b] != NEG_INF) {
                ll v = L.f[a][1] + R.f[0][b];
                if (v > res.f[a][b]) res.f[a][b] = v;
            }
        }
    }
    return res;
}

// 設定葉節點
void setLeaf(int node, int val) {
    tree[node].f[0][0] = 0;
    tree[node].f[1][1] = val;
    tree[node].f[0][1] = NEG_INF;
    tree[node].f[1][0] = NEG_INF;
}

// 建樹 它把整個 array 一直切一半一半
void build(int node, int l, int r, int* nums) {
    if (l == r) {
        setLeaf(node, nums[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(2 * node,     l,   mid, nums);
    build(2 * node + 1, mid + 1, r, nums);
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}

// 某個位置數字改掉了 那個位置的小表格也要重做
void update(int node, int l, int r, int pos, int val) {
    //看這段是不是只剩一格
	if (l == r) {
        setLeaf(node, val);
        return;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) update(2 * node,     l,   mid, pos, val);
    else            update(2 * node + 1, mid + 1, r, pos, val);
    tree[node] = combine(tree[2 * node], tree[2 * node + 1]);
}

int maximumSumSubsequence(int* nums, int numsSize,
                          int** queries, int queriesSize,
                          int* queriesColSize) {
    N = numsSize;//3
    build(1, 0, N - 1, nums);

    ll ans = 0;
    for (int i = 0; i < queriesSize; i++) {
        int pos = queries[i][0];//index
        int x   = queries[i][1];//value

        // 更新位置 pos 的值
        update(1, 0, N - 1, pos, x);

        // 從根節點取出最大值（可選空子序列，所以至少是 0）
        Node* root = &tree[1];
        ll maxSum = 0;
        for (int a = 0; a < 2; a++)
            for (int b = 0; b < 2; b++)
                if (root->f[a][b] > maxSum)
                    maxSum = root->f[a][b];

        ans = (ans + maxSum) % MOD;
    }

    return (int)ans;
}
// #include <stdlib.h>

// #define MOD 1000000007LL
// #define NEG -(1LL<<60)

// typedef struct {
//     long long a00, a01, a10, a11;
// } Node;

// static Node *seg;

// static inline long long mx(long long a, long long b) {
//     return a > b ? a : b;
// }

// static inline Node merge(Node L, Node R) {
//     Node C;
//     C.a00 = mx(R.a00 + L.a00, R.a01 + L.a10);
//     C.a01 = mx(R.a00 + L.a01, R.a01 + L.a11);
//     C.a10 = mx(R.a10 + L.a00, R.a11 + L.a10);
//     C.a11 = mx(R.a10 + L.a01, R.a11 + L.a11);
//     return C;
// }

// static inline Node leaf(int x) {
//     Node t;
//     t.a00 = 0;
//     t.a01 = 0;
//     t.a10 = x;
//     t.a11 = NEG;
//     return t;
// }

// static void build(int i, int l, int r, int *nums) {
//     if (l == r) {
//         seg[i] = leaf(nums[l]);
//         return;
//     }
//     int m = (l + r) >> 1;
//     build(i << 1, l, m, nums);
//     build(i << 1 | 1, m + 1, r, nums);
//     seg[i] = merge(seg[i << 1], seg[i << 1 | 1]);
// }

// static void update(int i, int l, int r, int p, int x) {
//     if (l == r) {
//         seg[i] = leaf(x);
//         return;
//     }
//     int m = (l + r) >> 1;
//     if (p <= m) update(i << 1, l, m, p, x);
//     else update(i << 1 | 1, m + 1, r, p, x);
//     seg[i] = merge(seg[i << 1], seg[i << 1 | 1]);
// }

// int maximumSumSubsequence(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
//     seg = (Node*)malloc(sizeof(Node) * (numsSize * 4 + 5));
//     build(1, 0, numsSize - 1, nums);

//     long long ans = 0;
//     for (int i = 0; i < queriesSize; i++) {
//         int pos = queries[i][0];
//         int x = queries[i][1];
//         update(1, 0, numsSize - 1, pos, x);
//         ans = (ans + mx(seg[1].a00, seg[1].a10)) % MOD;
//     }

//     free(seg);
//     return (int)ans;
// }
