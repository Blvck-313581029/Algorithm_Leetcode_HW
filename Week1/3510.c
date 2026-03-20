//3510. Minimum Pair Removal to Sort Array II
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    long long sum;
    int left_idx;
    int l_ver;  
    int r_idx;  
    int r_ver; 
} HeapNode;

typedef struct {
    HeapNode* arr;
    int size;
    int capacity;
} MinHeap;

void heap_push(MinHeap* h, HeapNode val) {
    if (h->size == h->capacity) {
        h->capacity *= 2;
        h->arr = realloc(h->arr, sizeof(HeapNode) * h->capacity);
    }
    int i = h->size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (val.sum < h->arr[p].sum || (val.sum == h->arr[p].sum && val.left_idx < h->arr[p].left_idx)) {
            h->arr[i] = h->arr[p];
            i = p;
        } else break;
    }
    h->arr[i] = val;
}

HeapNode heap_pop(MinHeap* h) {
    HeapNode res = h->arr[0];
    HeapNode last = h->arr[--h->size];
    int i = 0;
    while (i * 2 + 1 < h->size) {
        int child = i * 2 + 1;
        if (child + 1 < h->size && (h->arr[child+1].sum < h->arr[child].sum || 
           (h->arr[child+1].sum == h->arr[child].sum && h->arr[child+1].left_idx < h->arr[child].left_idx))) {
            child++;
        }
        if (h->arr[child].sum < last.sum || (h->arr[child].sum == last.sum && h->arr[child].left_idx < last.left_idx)) {
            h->arr[i] = h->arr[child];
            i = child;
        } else break;
    }
    if (h->size > 0) h->arr[i] = last;
    return res;
}

typedef struct {
    long long val;
    int prev, next;
    int version;
    bool active;
} ListNode;

bool is_bad(ListNode* nodes, int i) {
    if (i == -1 || !nodes[i].active || nodes[i].next == -1) return false;
    return nodes[i].val > nodes[nodes[i].next].val;
}

int minimumPairRemoval(int* nums, int numsSize) {
    if (numsSize <= 1) return 0;

    ListNode* nodes = malloc(sizeof(ListNode) * numsSize);
    int violations = 0;
    MinHeap h;
    h.size = 0;
    h.capacity = numsSize * 2 + 10;
    h.arr = malloc(sizeof(HeapNode) * h.capacity);

    for (int i = 0; i < numsSize; i++) {
        nodes[i].val = nums[i];
        nodes[i].prev = i - 1;
        nodes[i].next = (i == numsSize - 1) ? -1 : i + 1;
        nodes[i].version = 0;
        nodes[i].active = true;
    }

    for (int i = 0; i < numsSize - 1; i++) {
        if (is_bad(nodes, i)) violations++;
        HeapNode hn = {(long long)nums[i] + nums[i+1], i, 0, i+1, 0};
        heap_push(&h, hn);
    }

    int ops = 0;
    while (violations > 0 && h.size > 0) {
        HeapNode top = heap_pop(&h);
        int L = top.left_idx, R = top.r_idx;

        // 1. 檢查對象是否仍然有效
        if (!nodes[L].active || !nodes[R].active || 
            nodes[L].version != top.l_ver || nodes[R].version != top.r_ver ||
            nodes[L].next != R) continue;

        int LL = nodes[L].prev;
        int RR = nodes[R].next;

        // 2. 移除合併前受影響的違規計數
        if (is_bad(nodes, LL)) violations--;
        if (is_bad(nodes, L)) violations--;
        if (is_bad(nodes, R)) violations--;

        // 3. 執行合併
        nodes[L].val += nodes[R].val;
        nodes[L].next = RR;
        nodes[L].version++; // 只有修改值的 L 需要增加版本
        nodes[R].active = false;
        if (RR != -1) nodes[RR].prev = L; 
        // 注意：這裡不可增加 nodes[RR].version，因為 RR 的值沒變
        
        ops++;

        // 4. 更新違規計數
        if (is_bad(nodes, LL)) violations++;
        if (is_bad(nodes, L)) violations++;

        if (violations == 0) break;

        // 5. 將新產生的對加入堆積
        if (LL != -1) {
            HeapNode hn = {nodes[LL].val + nodes[L].val, LL, nodes[LL].version, L, nodes[L].version};
            heap_push(&h, hn);
        }
        if (RR != -1) {
            HeapNode hn = {nodes[L].val + nodes[RR].val, L, nodes[L].version, RR, nodes[RR].version};
            heap_push(&h, hn);
        }
    }

    free(h.arr);
    free(nodes);
    return ops;
}