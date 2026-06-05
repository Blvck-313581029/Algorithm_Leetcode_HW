// 5. Longest Palindromic Substring
// Time Best  = O(n)
// Time Worst = O(n^2)
// Space      = O(1) extra, O(n) including returned string
#include <stdlib.h>
#include <string.h>

char* longestPalindrome(char* s) {
    int n = strlen(s);

    int start = 0;
    int maxLen = 1;

    for (int i = 0; i < n; i++) {

        // case 1：奇數長度 palindrome
        // 例如 "babad" 裡面的 "bab"
        int left = i;
        int right = i;

        while (left >= 0 && right < n && s[left] == s[right]) {
            int len = right - left + 1;

            if (len > maxLen) {
                maxLen = len;
                start = left;
            }

            left--;
            right++;
        }

        // case 2：偶數長度 palindrome
        // 例如 "cbbd" 裡面的 "bb"
        left = i;
        right = i + 1;

        while (left >= 0 && right < n && s[left] == s[right]) {
            int len = right - left + 1;

            if (len > maxLen) {
                maxLen = len;
                start = left;
            }

            left--;
            right++;
        }
    }

    // 建立答案字串
    char* ans = (char*)malloc(sizeof(char) * (maxLen + 1));

    for (int i = 0; i < maxLen; i++) {
        ans[i] = s[start + i];
    }

    ans[maxLen] = '\0';

    return ans;
}
