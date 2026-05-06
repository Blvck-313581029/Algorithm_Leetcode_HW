// 765. Couples Holding Hands

int minSwapsCouples(int* row, int rowSize) {
    int pos[100];  // rowSize <= 60，所以開 100 夠用
    int ans = 0;

    // pos[person] = 這個人目前坐在哪個位置
    for (int i = 0; i < rowSize; i++) {
        pos[row[i]] = i;
    }

    // 每次看一對座位：0-1, 2-3, 4-5 ...
    for (int i = 0; i < rowSize; i += 2) {
        int first = row[i];
        int partner = first ^ 1;  // first 的另一半

        // 如果右邊已經是伴侶，就不用換
        if (row[i + 1] == partner) {
            continue;
        }

        // 否則，把 partner 換到 i+1 的位置
        int partner_pos = pos[partner];

        int wrong_person = row[i + 1];

        // swap row[i + 1] 和 row[partner_pos]
        row[partner_pos] = wrong_person;
        row[i + 1] = partner;

        // 更新位置表
        pos[wrong_person] = partner_pos;
        pos[partner] = i + 1;

        ans++;
    }

    return ans;
}