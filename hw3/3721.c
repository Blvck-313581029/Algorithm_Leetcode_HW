//3721. Longest Balanced Subarray II
#include <stdlib.h>
#include <string.h>

#define MAXV 100000

typedef struct {
    int mn, mx, lz;
} Node;

static Node *sg;
static int *base;
static int nxt[MAXV + 1], seen[MAXV + 1];

static inline void pull(int i) {
    sg[i].mn = sg[i << 1].mn < sg[i << 1 | 1].mn ? sg[i << 1].mn : sg[i << 1 | 1].mn;
    sg[i].mx = sg[i << 1].mx > sg[i << 1 | 1].mx ? sg[i << 1].mx : sg[i << 1 | 1].mx;
}

static inline void addtag(int i, int v) {
    sg[i].mn += v;
    sg[i].mx += v;
    sg[i].lz += v;
}

static inline void push(int i) {
    if (sg[i].lz) {
        addtag(i << 1, sg[i].lz);
        addtag(i << 1 | 1, sg[i].lz);
        sg[i].lz = 0;
    }
}

static void build(int i, int l, int r) {
    sg[i].lz = 0;
    if (l == r) {
        sg[i].mn = sg[i].mx = base[l];
        return;
    }
    int m = (l + r) >> 1;
    build(i << 1, l, m);
    build(i << 1 | 1, m + 1, r);
    pull(i);
}

static void upd(int i, int l, int r, int ql, int qr, int v) {
    if (ql <= l && r <= qr) {
        addtag(i, v);
        return;
    }
    if (qr < l || r < ql) return;
    push(i);
    int m = (l + r) >> 1;
    if (ql <= m) upd(i << 1, l, m, ql, qr, v);
    if (qr > m)  upd(i << 1 | 1, m + 1, r, ql, qr, v);
    pull(i);
}

static int find0(int i, int l, int r, int ql) {
    if (r < ql || sg[i].mn > 0 || sg[i].mx < 0) return -1;
    if (l == r) return l;
    push(i);
    int m = (l + r) >> 1, x = find0(i << 1 | 1, m + 1, r, ql);
    return x != -1 ? x : find0(i << 1, l, m, ql);
}

int longestBalanced(int* nums, int n) {
    if (n == 0) return 0;

    int *nextSame = (int*)malloc(sizeof(int) * n);
    base = (int*)malloc(sizeof(int) * n);
    sg = (Node*)malloc(sizeof(Node) * (n * 4 + 5));

    for (int i = 0; i <= MAXV; i++) nxt[i] = n;
    for (int i = n - 1; i >= 0; --i) {
        nextSame[i] = nxt[nums[i]];
        nxt[nums[i]] = i;
    }

    memset(seen, 0, sizeof(seen));
    int odd = 0, even = 0;
    for (int i = 0; i < n; ++i) {
        int x = nums[i];
        if (!seen[x]) {
            seen[x] = 1;
            if (x & 1) ++odd;
            else ++even;
        }
        base[i] = odd - even;
    }

    build(1, 0, n - 1);

    int ans = 0;
    for (int l = 0; l < n; ++l) {
        int r = find0(1, 0, n - 1, l);
        if (r >= l && r - l + 1 > ans) ans = r - l + 1;

        int rr = nextSame[l] - 1;
        if (rr >= l) upd(1, 0, n - 1, l, rr, (nums[l] & 1) ? -1 : 1);
    }

    free(nextSame);
    free(base);
    free(sg);
    return ans;
}