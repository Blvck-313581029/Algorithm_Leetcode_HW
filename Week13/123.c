// 123. Best Time to Buy and Sell Stock III
// Time Best  = O(n)
// Time Worst = O(n)
// Space      = O(1)
int maxProfit(int* prices, int pricesSize) {
    if (pricesSize == 0) {
        return 0;
    }

    // buy1：第一次買完後，手上的最大利益
    // sell1：第一次賣完後，手上的最大利益
    // buy2：第二次買完後，手上的最大利益
    // sell2：第二次賣完後，手上的最大利益

    int buy1 = -prices[0];
    int sell1 = 0;
    int buy2 = -prices[0];
    int sell2 = 0;

    for (int i = 1; i < pricesSize; i++) {
        int price = prices[i];

        // 第一次買：花掉 price
        if (-price > buy1) {
            buy1 = -price;
        }

        // 第一次賣：之前買的 buy1 + 今天賣掉 price
        if (buy1 + price > sell1) {
            sell1 = buy1 + price;
        }

        // 第二次買：用第一次賣完的錢，再買一次
        if (sell1 - price > buy2) {
            buy2 = sell1 - price;
        }

        // 第二次賣：第二次買完後，今天賣掉
        if (buy2 + price > sell2) {
            sell2 = buy2 + price;
        }
    }

    return sell2;
}
