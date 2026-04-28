//23. Merge k Sorted Lists
#include <stdlib.h>
// mergesort(linklist)
// Base case: listsSize == 0¡Aª½±µ¦^¶Ç NULL
// Base case time: O(1)
// Best case: O(N log k)
// Worst case: O(N log k)
// Space: O(log k)
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    if (!l1) return l2;
    if (!l2) return l1;
    
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    
    while (l1 && l2) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }
    tail->next = l1 ? l1 : l2;
    return dummy.next;
}

// éžæ­¸åˆ†æ²»
struct ListNode* helper(struct ListNode** lists, int left, int right) {
    if (left == right) return lists[left];
    if (left > right) return NULL;
    
    int mid = left + (right - left) / 2;
    struct ListNode* l1 = helper(lists, left, mid);
    struct ListNode* l2 = helper(lists, mid + 1, right);
    
    return mergeTwoLists(l1, l2);
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;
    return helper(lists, 0, listsSize - 1);
}
