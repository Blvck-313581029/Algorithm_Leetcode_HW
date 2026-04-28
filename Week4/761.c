//761. Special Binary String
//Base case O(1)
//Bestcase O(n log n)
//Worst Case: O(n2)  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cmp_desc(const void *a, const void *b) {
    char *sa = *(char **)a;
    char *sb = *(char **)b;
    return strcmp(sb, sa);   // 由大到小排
}

char* makeLargestSpecial(char* s) {
    int n = strlen(s);

    // 長度 <= 2 不可能再拆，直接回傳複製字串
    if (n <= 2) {
        char *res = (char *)malloc((n + 1) * sizeof(char));
        strcpy(res, s);
        return res;
    }

    // 最多切成 n/2 段，開大一點即可
    char **parts = (char **)malloc((n + 1) * sizeof(char *));
    int partCount = 0;

    int count = 0;
    int start = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '1') count++;
        else count--;

        // 找到一段最外層 special substring
        if (count == 0) {
            // 這段是 s[start ... i]
            // 最外層一定是 1 ... 0
            // 取中間 inner = s[start+1 ... i-1]
            int innerLen = i - start - 1;

            char *inner = (char *)malloc((innerLen + 1) * sizeof(char));
            strncpy(inner, s + start + 1, innerLen);
            inner[innerLen] = '\0';

            // 遞迴處理內部
            char *processedInner = makeLargestSpecial(inner);
            free(inner);

            // 組回 "1" + processedInner + "0"
            int newLen = strlen(processedInner) + 2;
            char *block = (char *)malloc((newLen + 1) * sizeof(char));
            block[0] = '1';
            strcpy(block + 1, processedInner);
            block[newLen - 1] = '0';
            block[newLen] = '\0';

            free(processedInner);

            parts[partCount++] = block;
            start = i + 1;
        }
    }

    // 把所有 block 由大到小排序
    qsort(parts, partCount, sizeof(char *), cmp_desc);

    // 計算總長度
    int totalLen = 0;
    for (int i = 0; i < partCount; i++) {
        totalLen += strlen(parts[i]);
    }

    // 拼接答案
    char *res = (char *)malloc((totalLen + 1) * sizeof(char));
    res[0] = '\0';

    for (int i = 0; i < partCount; i++) {
        strcat(res, parts[i]);
        free(parts[i]);
    }

    free(parts);
    return res;
}
