//25. Reverse Nodes in k-
// Base case: O(1)
// Best case: O(n)
// Worst case: O(n)
// Space: O(1)
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    if (!head || k == 1) return head;
    
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode *groupPrev = &dummy;
    
    while (true) {
        // 找第 k 個節點
        struct ListNode* kth = groupPrev;
        for (int i = 0; i < k && kth; i++) kth = kth->next;
        if (!kth) break; // 不夠 k 個，結束
        
        struct ListNode* prev = kth->next;; // 讓原本的首節點翻轉後指向下一組的頭
        struct ListNode* curr = groupPrev->next;
        
        // 翻轉這組內部的指標
        for (int i = 0; i < k; i++) {
            struct ListNode* tmp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = tmp;
        }
        
        // 將上一組的結尾指向這一組翻轉後的新開頭
        //dummy->2 groupPrev=1
        struct ListNode* temp = groupPrev->next;
        groupPrev->next = kth;
        groupPrev = temp;
    }
    return dummy.next;
}
