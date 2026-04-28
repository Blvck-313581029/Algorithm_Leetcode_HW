// 2139. Minimum Moves to Reach Target Score
int minMoves(int target, int maxDoubles) {
    int moves = 0;

    while (target > 1 && maxDoubles > 0) {
        if (target % 2 == 0) {
            // 反向：偶數可以除以 2
            target /= 2;
            maxDoubles--;
        } else {
            // 反向：奇數只能先減 1
            target--;
        }
        moves++;
    }

    // 沒有 double 次數後，只能一直 -1 回到 1
    moves += target - 1;

    return moves;
}