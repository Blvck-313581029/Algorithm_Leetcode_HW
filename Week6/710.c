#include <stdlib.h>
#include <time.h>

typedef struct {
    int key;
    int val;
    int used;
} Entry;

typedef struct {
    int M;
    Entry* table;
    int tableSize;
} Solution;

int hashGet(Entry* table, int tableSize, int key) {
    int idx = (key % tableSize + tableSize) % tableSize;
    while (table[idx].used && table[idx].key != key) {
        idx = (idx + 1) % tableSize;
    }
    return idx;
}

void hashSet(Entry* table, int tableSize, int key, int val) {
    int idx = hashGet(table, tableSize, key);
    table[idx].key  = key;
    table[idx].val  = val;
    table[idx].used = 1;
}

// 找到回傳 val（可能是 -2 或正數），找不到回傳 -1
int hashFind(Entry* table, int tableSize, int key) {
    int idx = hashGet(table, tableSize, key);
    if (table[idx].used) return table[idx].val;
    return -1;
}

Solution* solutionCreate(int n, int* blacklist, int blacklistSize) {
    Solution* obj = (Solution*)malloc(sizeof(Solution));

    obj->M = n - blacklistSize;
    obj->tableSize = (blacklistSize == 0) ? 1 : blacklistSize * 2;
    obj->table = (Entry*)calloc(obj->tableSize, sizeof(Entry));

    // Step 1: 標記所有黑名單，val = -2（代表「黑名單」）
    for (int i = 0; i < blacklistSize; i++) {
        hashSet(obj->table, obj->tableSize, blacklist[i], -2); // ? 改 -2
    }

    // Step 2: 把 [0, M-1] 的黑名單映射到 [M, n-1] 的好人
    int last = n - 1;
    for (int i = 0; i < blacklistSize; i++) {
        int b = blacklist[i];

        if (b < obj->M) {
            // val == -2 代表是黑名單，跳過
            while (hashFind(obj->table, obj->tableSize, last) == -2) { // ? 改 == -2
                last--;
            }
            hashSet(obj->table, obj->tableSize, b, last);
            last--;
        }
    }

    srand(time(NULL));
    return obj;
}

int solutionPick(Solution* obj) {
    int idx = rand() % obj->M;

    int mapped = hashFind(obj->table, obj->tableSize, idx);
    return (mapped >= 0) ? mapped : idx; // ? 改 >= 0
}

void solutionFree(Solution* obj) {
    free(obj->table);
    free(obj);
}
