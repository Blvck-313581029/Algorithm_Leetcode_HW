// 458. Poor Pigs
// Time Best  = O(1)
// Time Worst = O(log buckets)
// Space      = O(1)
int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
    int rounds = minutesToTest / minutesToDie;

    // –唉睫篈计
    // 材 1 近材 2 近...材 rounds 近常⊿
    int states = rounds + 1;

    int pigs = 0;
    int canCheck = 1;

    // т程ぶ pigsㄏ眔 states^pigs >= buckets
    while (canCheck < buckets) {
        pigs++;
        canCheck *= states;
    }

    return pigs;
}
