//218. The Skyline Problem
#include <stdlib.h>

typedef struct {
    int right;
    int height;
} Node;

typedef struct {
    Node *arr;
    int size;
    int cap;
} MaxHeap;

/* ---------- heap ---------- */
void heapInit(MaxHeap *h, int cap) {
    h->arr = (Node *)malloc(sizeof(Node) * cap);
    h->size = 0;
    h->cap = cap;
}

void heapSwap(Node *a, Node *b) {
    Node t = *a;
    *a = *b;
    *b = t;
}

int better(Node a, Node b) {
    /* 高度大的比較好；如果高度一樣，right 較大的比較好 */
    if (a.height != b.height) return a.height > b.height;
    return a.right > b.right;
}

void heapPush(MaxHeap *h, Node val) {
    h->arr[h->size] = val;
    int i = h->size;
    h->size++;

    while (i > 0) {
        int p = (i - 1) / 2;
        if (better(h->arr[p], h->arr[i])) break;
        heapSwap(&h->arr[p], &h->arr[i]);
        i = p;
    }
}

void heapPop(MaxHeap *h) {
    if (h->size == 0) return;
    h->arr[0] = h->arr[h->size - 1];
    h->size--;

    int i = 0;
    while (1) {
        int l = i * 2 + 1;
        int r = i * 2 + 2;
        int largest = i;

        if (l < h->size && better(h->arr[l], h->arr[largest])) largest = l;
        if (r < h->size && better(h->arr[r], h->arr[largest])) largest = r;

        if (largest == i) break;
        heapSwap(&h->arr[i], &h->arr[largest]);
        i = largest;
    }
}

Node heapTop(MaxHeap *h) {
    return h->arr[0];
}

/* ---------- sort buildings by left ---------- */
int cmpBuilding(const void *a, const void *b) {
    int *A = *(int **)a;
    int *B = *(int **)b;

    if (A[0] != B[0]) return A[0] - B[0];   // left 小的先
    if (A[2] != B[2]) return B[2] - A[2];   // 同 left，高的先
    return A[1] - B[1];                     // 再來 right 小的先
}

void addPoint(int ***ans, int *returnSize, int *cap, int x, int y) {
    if (*returnSize > 0 && (*ans)[*returnSize - 1][1] == y) {
        return; // 避免連續相同高度
    }

    if (*returnSize >= *cap) {
        *cap *= 2;
        *ans = (int **)realloc(*ans, sizeof(int *) * (*cap));
    }

    (*ans)[*returnSize] = (int *)malloc(sizeof(int) * 2);
    (*ans)[*returnSize][0] = x;
    (*ans)[*returnSize][1] = y;
    (*returnSize)++;
}

int** getSkyline(int** buildings, int buildingsSize, int* buildingsColSize,
                 int* returnSize, int** returnColumnSizes) {
    (void)buildingsColSize;  // 避免 warning

    *returnSize = 0;
    if (buildingsSize == 0) {
        *returnColumnSizes = NULL;
        return NULL;
    }

    qsort(buildings, buildingsSize, sizeof(int*), cmpBuilding);

    int cap = buildingsSize * 2 + 1;
    int **ans = (int **)malloc(sizeof(int *) * cap);

    MaxHeap heap;
    heapInit(&heap, buildingsSize + 5);

    int i = 0;

    while (i < buildingsSize || heap.size > 0) {
        int x;

        /* 情況1：heap是空的，或下一棟樓的 left <= 目前最高樓的 right
           => 先處理「新開始的建築」 */
        if (heap.size == 0 || (i < buildingsSize && buildings[i][0] <= heapTop(&heap).right)) {
            x = buildings[i][0];

            /* 把所有 left == x 的建築都加進 heap */
            while (i < buildingsSize && buildings[i][0] == x) {
                Node node;
                node.right = buildings[i][1];
                node.height = buildings[i][2];
                heapPush(&heap, node);
                i++;
            }
        } else {
            /* 情況2：目前最高的建築先結束 */
            x = heapTop(&heap).right;

            /* 把所有已經在 x 結束的建築移掉 */
            while (heap.size > 0 && heapTop(&heap).right <= x) {
                heapPop(&heap);
            }
        }

        /* 清掉所有已過期建築（lazy deletion） */
        while (heap.size > 0 && heapTop(&heap).right <= x) {
            heapPop(&heap);
        }

        int currHeight = (heap.size == 0) ? 0 : heapTop(&heap).height;
        addPoint(&ans, returnSize, &cap, x, currHeight);
    }

    *returnColumnSizes = (int *)malloc(sizeof(int) * (*returnSize));
    for (int k = 0; k < *returnSize; k++) {
        (*returnColumnSizes)[k] = 2;
    }

    free(heap.arr);
    return ans;
}
