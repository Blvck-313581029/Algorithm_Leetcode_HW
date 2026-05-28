// 639. Decode Ways II
// Base case / s 長度 = 0：O(1)
// Best case：O(n)
// Worst case：O(n)
// Space：O(1)

#define MOD 1000000007

long long singleWays(char c) {
    if (c == '*') {
        return 9;   // '*' 可以是 1~9
    }

    if (c == '0') {
        return 0;   // '0' 不能單獨解碼
    }

    return 1;       // '1'~'9'
}

long long doubleWays(char a, char b) {
    // case 1: "**"
    if (a == '*' && b == '*') {
        /*
            11~19 => 9 種
            21~26 => 6 種
            總共 15 種
        */
        return 15;
    }

    // case 2: 第一個是 '*'
    if (a == '*') {
        if (b >= '0' && b <= '6') {
            /*
                b = 0~6
                可以是 1b 或 2b
                例如 *6 => 16, 26
            */
            return 2;
        } else {
            /*
                b = 7~9
                只能是 17~19
                不能是 27~29
            */
            return 1;
        }
    }

    // case 3: 第二個是 '*'
    if (b == '*') {
        if (a == '1') {
            /*
                1* => 11~19
                9 種
            */
            return 9;
        }

        if (a == '2') {
            /*
                2* => 21~26
                6 種
            */
            return 6;
        }

        return 0;
    }

    // case 4: 兩個都是普通數字
    int num = (a - '0') * 10 + (b - '0');

    if (num >= 10 && num <= 26) {
        return 1;
    }

    return 0;
}

int numDecodings(char* s) {
    if (s == NULL || s[0] == '\0') {
        return 0;
    }

    long long prev2 = 1;                 // dp[0]，空字串有 1 種解法
    long long prev1 = singleWays(s[0]);  // dp[1]

    for (int i = 1; s[i] != '\0'; i++) {
        long long one = singleWays(s[i]);
        long long two = doubleWays(s[i - 1], s[i]);

        long long curr = (prev1 * one + prev2 * two) % MOD;

        prev2 = prev1;
        prev1 = curr;
    }

    return (int)prev1;
}
