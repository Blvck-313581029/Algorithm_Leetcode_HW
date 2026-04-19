//710. Random Pick with Blacklist
#include <stdlib.h>
#include <time.h>

// Hash map node
typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

#define TABLE_SIZE 10007

typedef struct {
    Node* table[TABLE_SIZE];
    int M;
} Solution;

// Hash function
int hash(int key) {
    return abs(key) % TABLE_SIZE;
}

// Insert or update key-value into hash map
void mapPut(Node** table, int key, int value) {
    int h = hash(key);
    Node* cur = table[h];
    while (cur) {
        if (cur->key == key) {
            cur->value = value;
            return;
        }
        cur = cur->next;
    }
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key   = key;
    newNode->value = value;
    newNode->next  = table[h];
    table[h]       = newNode;
}

// Check if key exists in hash map
int mapContains(Node** table, int key) {
    int h = hash(key);
    Node* cur = table[h];
    while (cur) {
        if (cur->key == key) return 1;
        cur = cur->next;
    }
    return 0;
}

// Get value by key, return defaultVal if not found
int mapGet(Node** table, int key, int defaultVal) {
    int h = hash(key);
    Node* cur = table[h];
    while (cur) {
        if (cur->key == key) return cur->value;
        cur = cur->next;
    }
    return defaultVal;
}

// Constructor
Solution* solutionCreate(int n, int* blacklist, int blacklistSize) {
    srand((unsigned int)time(NULL));

    Solution* obj = (Solution*)malloc(sizeof(Solution));
    for (int i = 0; i < TABLE_SIZE; i++) obj->table[i] = NULL;

    int B  = blacklistSize;
    obj->M = n - B;

    // Step 1: 把所有黑名單先放入 mapping（value 先填 0）
    for (int i = 0; i < B; i++) {
        mapPut(obj->table, blacklist[i], 0);
    }

    // Step 2: 把 [0, M-1] 內的黑名單，映射到 [M, n-1] 內的好人
    int last = n - 1;
    for (int i = 0; i < B; i++) {
        if (blacklist[i] < obj->M) {
            // 跳過 [M, n-1] 中也是黑名單的位置
            while (mapContains(obj->table, last)) {
                last--;
            }
            mapPut(obj->table, blacklist[i], last);
            last--;
        }
    }

    return obj;
}

// Pick
int solutionPick(Solution* obj) {
    int idx = rand() % obj->M;
    return mapGet(obj->table, idx, idx);
}

// Free
void solutionFree(Solution* obj) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* cur = obj->table[i];
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(obj);
}
