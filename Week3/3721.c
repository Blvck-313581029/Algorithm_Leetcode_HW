//3721. Longest Balanced Subarray II
#include <stdlib.h>
#include <string.h>
#define SEG 400020
static int smin[SEG], smax[SEG], slazy[SEG];
//lazy更新左右子樹的smin、smax
static void push(int nd) {
    int lz = slazy[nd]; if (!lz) return;
    smin[2*nd]+=lz; smax[2*nd]+=lz; slazy[2*nd]+=lz;
    smin[2*nd+1]+=lz; smax[2*nd+1]+=lz; slazy[2*nd+1]+=lz;
    slazy[nd] = 0;
}

static void radd(int nd, int a, int b, int l, int r, int v) {
    if (b < l || a > r) return;
    if (l <= a && b <= r) { smin[nd]+=v; smax[nd]+=v; slazy[nd]+=v; return; }
    push(nd); int m = (a+b) >> 1;
    radd(2*nd, a, m, l, r, v); radd(2*nd+1, m+1, b, l, r, v);
    smin[nd] = smin[2*nd] < smin[2*nd+1] ? smin[2*nd] : smin[2*nd+1];
    smax[nd] = smax[2*nd] > smax[2*nd+1] ? smax[2*nd] : smax[2*nd+1];
}

// 在 [l, r] 中找最左邊值為 0 的位置
static int lz0(int nd, int a, int b, int l, int r) {
    if (a > r || b < l) return -1;
    if (a >= l && b <= r) {
        if (smin[nd] > 0 || smax[nd] < 0) return -1;
		//葉子直接回傳。
        if (a == b) return a;
    }
    push(nd); int m = (a+b) >> 1;
    int res = lz0(2*nd, a, m, l, r);
    return res != -1 ? res : lz0(2*nd+1, m+1, b, l, r);
}

int longestBalanced(int* nums, int numsSize) {
    int n = numsSize; if (!n) return 0;
    memset(smin, 0, sizeof(smin));
    memset(smax, 0, sizeof(smax));
    memset(slazy, 0, sizeof(slazy));
    int *last = (int*)calloc(100001, sizeof(int));
    int ans = 0;
    for (int r = 0; r < n; r++) {
        int v = nums[r], p = last[v] - 1;
        last[v] = r + 1;
        radd(1, 0, n-1, p+1, r, (v & 1) ? -1 : 1);
        int l = lz0(1, 0, n-1, 0, r);
        if (l >= 0 && r - l + 1 > ans) ans = r - l + 1;
    }
    free(last); return ans;
}



// #include <stdlib.h>
// #include <string.h>

// #define MAXV 100000

// typedef struct {
//     int mn, mx, lz;
// } Node;

// static Node *sg;
// static int *base;
// static int nxt[MAXV + 1], seen[MAXV + 1];

// static inline void pull(int i) {
//     sg[i].mn = sg[i << 1].mn < sg[i << 1 | 1].mn ? sg[i << 1].mn : sg[i << 1 | 1].mn;
//     sg[i].mx = sg[i << 1].mx > sg[i << 1 | 1].mx ? sg[i << 1].mx : sg[i << 1 | 1].mx;
// }

// static inline void addtag(int i, int v) {
//     sg[i].mn += v;
//     sg[i].mx += v;
//     sg[i].lz += v;
// }

// static inline void push(int i) {
//     if (sg[i].lz) {
//         addtag(i << 1, sg[i].lz);
//         addtag(i << 1 | 1, sg[i].lz);
//         sg[i].lz = 0;
//     }
// }

// static void build(int i, int l, int r) {
//     sg[i].lz = 0;
//     if (l == r) {
//         sg[i].mn = sg[i].mx = base[l];
//         return;
//     }
//     int m = (l + r) >> 1;
//     build(i << 1, l, m);
//     build(i << 1 | 1, m + 1, r);
//     pull(i);
// }

// static void upd(int i, int l, int r, int ql, int qr, int v) {
//     if (ql <= l && r <= qr) {
//         addtag(i, v);
//         return;
//     }
//     if (qr < l || r < ql) return;
//     push(i);
//     int m = (l + r) >> 1;
//     if (ql <= m) upd(i << 1, l, m, ql, qr, v);
//     if (qr > m)  upd(i << 1 | 1, m + 1, r, ql, qr, v);
//     pull(i);
// }

// static int find0(int i, int l, int r, int ql) {
//     if (r < ql || sg[i].mn > 0 || sg[i].mx < 0) return -1;
//     if (l == r) return l;
//     push(i);
//     int m = (l + r) >> 1, x = find0(i << 1 | 1, m + 1, r, ql);
//     return x != -1 ? x : find0(i << 1, l, m, ql);
// }

// int longestBalanced(int* nums, int n) {
//     if (n == 0) return 0;

//     int *nextSame = (int*)malloc(sizeof(int) * n);
//     base = (int*)malloc(sizeof(int) * n);
//     sg = (Node*)malloc(sizeof(Node) * (n * 4 + 5));

//     for (int i = 0; i <= MAXV; i++) nxt[i] = n;
//     for (int i = n - 1; i >= 0; --i) {
//         nextSame[i] = nxt[nums[i]];
//         nxt[nums[i]] = i;
//     }

//     memset(seen, 0, sizeof(seen));
//     int odd = 0, even = 0;
//     for (int i = 0; i < n; ++i) {
//         int x = nums[i];
//         if (!seen[x]) {
//             seen[x] = 1;
//             if (x & 1) ++odd;
//             else ++even;
//         }
//         base[i] = odd - even;
//     }

//     build(1, 0, n - 1);

//     int ans = 0;
//     for (int l = 0; l < n; ++l) {
//         int r = find0(1, 0, n - 1, l);
//         if (r >= l && r - l + 1 > ans) ans = r - l + 1;

//         int rr = nextSame[l] - 1;
//         if (rr >= l) upd(1, 0, n - 1, l, rr, (nums[l] & 1) ? -1 : 1);
//     }

//     free(nextSame);
//     free(base);
//     free(sg);
//     return ans;
// }
