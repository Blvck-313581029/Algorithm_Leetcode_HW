#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 * int val;
 * struct TreeNode *left;
 * struct TreeNode *right;
 * };
 */

bool isEvenOddTree(struct TreeNode* root) {
    if (!root) return true;

    // 根據題目限制，節點數最多 10^5
    struct TreeNode** queue = (struct TreeNode**)malloc(100001 * sizeof(struct TreeNode*));
    int head = 0, tail = 0;
    
    // 將根節點放入佇列
    queue[tail++] = root;
    int level = 0;

    while (head < tail) {
        int size = tail - head; // 當前層的節點數量
        int prev_val;
        
        // 根據層數初始化前一個比較的值
        if (level % 2 == 0) {
            prev_val = INT_MIN; // 偶數層找嚴格遞增，起始設最小
        } else {
            prev_val = INT_MAX; // 奇數層找嚴格遞減，起始設最大
        }

        for (int i = 0; i < size; i++) {
            struct TreeNode* node = queue[head++];
            int val = node->val;

            if (level % 2 == 0) {
                // 偶數層：必須是奇數，且嚴格遞增
                if (val % 2 == 0 || val <= prev_val) {
                    free(queue);
                    return false;
                }
            } else {
                // 奇數層：必須是偶數，且嚴格遞減
                if (val % 2 != 0 || val >= prev_val) {
                    free(queue);
                    return false;
                }
            }
            
            prev_val = val;

            // 將下一層節點加入佇列
            if (node->left) queue[tail++] = node->left;
            if (node->right) queue[tail++] = node->right;
        }
        level++;
    }

    free(queue);
    return true;
}
