//79. Word Search
#include <stdbool.h>
#include <string.h>

bool dfs(char** board, int boardSize, int* boardColSize,
         int r, int c, char* word, int idx) {
    // word 已經全部比對完
    if (word[idx] == '\0') {
        return true;
    }

    // 越界
    if (r < 0 || r >= boardSize || c < 0 || c >= boardColSize[r]) {
        return false;
    }

    // 字母不對
    if (board[r][c] != word[idx]) {
        return false;
    }

    // 先把這格標記成已使用
    char temp = board[r][c];
    board[r][c] = '#';

    // 往四個方向找下一個字母
    bool found = dfs(board, boardSize, boardColSize, r + 1, c, word, idx + 1) ||
                 dfs(board, boardSize, boardColSize, r - 1, c, word, idx + 1) ||
                 dfs(board, boardSize, boardColSize, r, c + 1, word, idx + 1) ||
                 dfs(board, boardSize, boardColSize, r, c - 1, word, idx + 1);

    // 回溯：還原
    board[r][c] = temp;

    return found;
}

bool exist(char** board, int boardSize, int* boardColSize, char* word) {
    int rows = boardSize;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < boardColSize[i]; j++) {
            if (dfs(board, boardSize, boardColSize, i, j, word, 0)) {
                return true;
            }
        }
    }

    return false;
}
