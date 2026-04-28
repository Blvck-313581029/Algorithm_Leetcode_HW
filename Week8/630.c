//630. Course Schedule III
#include <stdlib.h>

int cmp(const void* a, const void* b) {
    int* c1 = *(int**)a;
    int* c2 = *(int**)b;
    return c1[1] - c2[1]; // 按 lastDay 排序
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// max heap：存 duration
void push(int* heap, int* size, int val) {
    heap[++(*size)] = val;

    int i = *size;
    while (i > 1) {
        int parent = i / 2;
        if (heap[parent] >= heap[i]) break;

        swap(&heap[parent], &heap[i]);
        i = parent;
    }
}

int pop(int* heap, int* size) {
    int ret = heap[1];
    heap[1] = heap[(*size)--];

    int i = 1;
    while (1) {
        int left = i * 2;
        int right = i * 2 + 1;
        int largest = i;

        if (left <= *size && heap[left] > heap[largest]) {
            largest = left;
        }
        if (right <= *size && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest == i) break;

        swap(&heap[i], &heap[largest]);
        i = largest;
    }

    return ret;
}

int scheduleCourse(int** courses, int coursesSize, int* coursesColSize) {
    qsort(courses, coursesSize, sizeof(int*), cmp);

    int* heap = (int*)malloc(sizeof(int) * (coursesSize + 1));
    int heapSize = 0;
    int totalTime = 0;

    for (int i = 0; i < coursesSize; i++) {
        int duration = courses[i][0];
        int lastDay = courses[i][1];

        totalTime += duration;
        push(heap, &heapSize, duration);

        // 如果目前總時間超過 deadline
        // 就丟掉目前修過最久的那門課
        if (totalTime > lastDay) {
            int longest = pop(heap, &heapSize);
            totalTime -= longest;
        }
    }

    int ans = heapSize;
    free(heap);

    return ans;
}