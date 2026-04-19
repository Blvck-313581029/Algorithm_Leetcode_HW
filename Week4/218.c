//218. The Skyline Problem
//Base case / 最小輸入：O(1)
//Best case：O(n log n)
//Worst case：O(n log n)
//Space：O(n)
#include <stdlib.h>

/* ── 兩個 max-heap，共用同一組 push/pop ── */
static int A[20005], B[20005], sa, sb;

static void push(int *h, int *n, int v) {
    h[*n] = v;
    for (int i = (*n)++; i > 0;) {
        int p = (i-1)/2;
        if (h[p] >= h[i]) break;
        int t = h[p]; h[p] = h[i]; h[i] = t;
        i = p;
    }
}

static void pop(int *h, int *n) {
    h[0] = h[--(*n)];
    for (int i = 0;;) {
        int l = 2*i+1, r = 2*i+2, m = i;
        if (l < *n && h[l] > h[m]) m = l;
        if (r < *n && h[r] > h[m]) m = r;
        if (m == i) break;
        int t = h[i]; h[i] = h[m]; h[m] = t;
        i = m;
    }
}

/* A 頂端若等於 B 頂端 → 兩邊對消，直到不同 */
static int top() {
    while (sa && sb && A[0] == B[0]) { pop(A,&sa); pop(B,&sb); }
    return sa ? A[0] : 0;
}

/* ── Events ── */
typedef struct { int x, h; } Ev;

static int cmpEv(const void *a, const void *b) {
    Ev *P = a, *Q = b;
    if (P->x != Q->x) return P->x - Q->x;
    return P->h - Q->h;  // 負(enter) 排在 正(exit) 前
}

int **getSkyline(int **b, int n, int *cs, int *rSz, int **rCS) {
    sa = sb = 0;

    /* enter = (x, -h)，exit = (x, +h) */
    Ev *ev = malloc(2*n * sizeof *ev);
    for (int i = 0; i < n; i++) {
        ev[2*i]   = (Ev){ b[i][0], -b[i][2] };
        ev[2*i+1] = (Ev){ b[i][1],  b[i][2] };
    }
    qsort(ev, 2*n, sizeof *ev, cmpEv);

    push(A, &sa, 0);  // 地面

    int **ans = malloc((2*n+1) * sizeof *ans);
    int *rcs  = malloc((2*n+1) * sizeof *rcs);
    int sz = 0;

    for (int i = 0; i < 2*n; i++) {
        int x = ev[i].x;
        int h = ev[i].h;

        if (h < 0) push(A, &sa, -h);
        else       push(B, &sb,  h);
		//  if ans is empty OR ans.last.height ≠ curHeight:
        if (!sz || ans[sz-1][1] != top()) {
            ans[sz] = malloc(2 * sizeof(int));
            ans[sz][0] = x;
            ans[sz][1] = top();
            rcs[sz++] = 2;
        }
    }
    *rSz = sz; *rCS = rcs;
    free(ev);
    return ans;
}
