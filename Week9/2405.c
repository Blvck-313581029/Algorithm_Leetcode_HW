// 2405. Optimal Partition of String
int partitionString(char* s) {
    int ans = 1;      // 至少會有一段
    int mask = 0;     // 記錄目前這段出現過哪些字母

    for (int i = 0; s[i] != '\0'; i++) {
        int bit = 1 << (s[i] - 'a');

        // 如果這個字母已經在目前這段出現過
        if (mask & bit) {
            ans++;        // 必須切一段新的
            mask = 0;     // 新段重新開始
        }

        // 把目前字母放進這段
        mask |= bit;
    }

    return ans;
}