//135. Candy
//Base case / 最小輸入：O(1)
//Best case：O(n)
//Worst case：O(n)
//Space：O(n)
int candy(int* ratings, int ratingsSize) {
    // 建立糖果陣列，每人先給 1 顆
    int* candies = (int*)malloc(ratingsSize * sizeof(int));
    for (int i = 0; i < ratingsSize; i++) {
        candies[i] = 1;
    }

    // 第 1 步：從左往右
    // 如果我的分數比左邊鄰居高，就比他多拿 1 顆
    for (int i = 1; i < ratingsSize; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    // 第 2 步：從右往左
    // 如果我的分數比右邊鄰居高，確保我比他多；取兩次結果的最大值
    for (int i = ratingsSize - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            if (candies[i] < candies[i + 1] + 1) {
                candies[i] = candies[i + 1] + 1;
            }
        }
    }

    // 加總所有糖果
    int total = 0;
    for (int i = 0; i < ratingsSize; i++) {
        total += candies[i];
    }

    free(candies);
    return total;
}
