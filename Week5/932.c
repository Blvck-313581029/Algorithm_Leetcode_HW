//932. Beautiful Array
#include <stdlib.h>
int* beautifulArray(int n, int* returnSize) {
    int* arr = (int*)malloc(sizeof(int) * n);
    int* tmp = (int*)malloc(sizeof(int) * n);

    int size = 1;
    arr[0] = 1;

    while (size < n) {
        int idx = 0;

        // 先放奇數: 2*x - 1
        for (int i = 0; i < size; i++) {
            int val = arr[i] * 2 - 1;
            if (val <= n) {
                tmp[idx++] = val;
            }
        }

        // 再放偶數: 2*x
        for (int i = 0; i < size; i++) {
            int val = arr[i] * 2;
            if (val <= n) {
                tmp[idx++] = val;
            }
        }

        // 把 tmp 複製回 arr
        for (int i = 0; i < idx; i++) {
            arr[i] = tmp[i];
        }

        size = idx;
    }

    free(tmp);
    *returnSize = n;
    return arr;
}
